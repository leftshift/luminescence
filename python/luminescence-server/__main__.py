import socket
from .client import Client


class LuminescenceServer():
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind((self.host, self.port))

        self.clients = []

    def listen(self):
        self.sock.listen(5)
        while True:
            client, address = self.sock.accept()
            print("got client with address {}".format(address))
            client.settimeout(60)
            self.clients.append(Client(client))


if __name__ == "__main__":
    print("opening luminescence server on 8080")
    LuminescenceServer('', 8080).listen()
