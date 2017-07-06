import time
from socket import *
from threading import Thread


def monitor():
    global n
    while True:
        time.sleep(1)
        print(n, 'reqs/sec')
        n = 0


if __name__ == '__main__':
    n = 0
    Thread(target=monitor).start()

    sock = socket(AF_INET, SOCK_STREAM)
    sock.connect(('localhost', 25000))

    while True:
        n += 1
        sock.send(b'1')
        resp = sock.recv(100)
