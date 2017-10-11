import threading
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

    def reciever(self):
        while self.active:
            try:
                data = self.sock.recv(1024)
                print("recv: {}".format(data))
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
                data = self.sendQueue.get()
                self.sock.send(data)
            except:
                self.sock.close()
                self.active = False
