import struct


class BaseMessage():
    def __init__(self):
        self.type = 0
        self.id = None
        self.recieved_sec = 0
        self.recieved_usec = 0
        self.sent_sec = 0
        self.sent_usec = 0
        self.size = 0

    def unpack(self, stream):
        (
            self.type,
            self.id,
            self.recieved_sec,
            self.recieved_usec,
            self.sent_sec,
            self.sent_usec,
            self.size
        ) = struct.unpack_from("<BBIIIII", stream, offset=0)

    def pack(self):
        pass
