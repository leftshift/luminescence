import threading
import time
from queue import PriorityQueue


class Client():
    def __init__(self, sock):
        print("Add client for {}".format(sock))
        self.active = True
        self.sock = sock
        self.sendQueue = PriorityQueue()

        self.reciever_thread = threading.Thread(target=self.reciever).start()
        self.sender_thread = threading.Thread(target=self.sender).start()

        self.initialized = False
        self.id = None
        self.stat_pack = 0
        self.stat_time = 0

    def reciever(self):
        while self.active:
            try:
                data = self.sock.recv(1024)
                self.stat_pack += 1
                now = time.time()
                if self.stat_time + 1 < now:
                    print("{} packages in {}s".format(self.stat_pack, now - self.stat_time))
                    self.stat_time = now
                    self.stat_pack = 0
                    
                if data:
                    self.sendQueue.put(data)
                else:
                    raise RuntimeError('Client disconnected')
            except:
                self.sock.close()
                self.active = False

    def sender(self):
        while self.active:
            try:
                # data = self.sendQueue.get()
                data = b"ack\n"
                self.sock.send(data)
            except:
                self.sock.close()
                self.active = False
