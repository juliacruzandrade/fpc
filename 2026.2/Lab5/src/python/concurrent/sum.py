import os
import sys
import time
import threading

def do_sum(path):
    time.sleep(1) # emulating adittional delay of 1 second
    _sum = 0
    with open(path, 'rb',buffering=0) as f:
        byte = f.read(1)
        while byte:
            _sum += int.from_bytes(byte, byteorder='big', signed=False)
            byte = f.read(1)
        print(path + " : " + str(_sum))
        return _sum

if __name__ == "__main__":
    paths = sys.argv[1:]
    threads = []

    for path in paths:
    #many error could be raised error. we don't care
        t = threading.Thread(target=do_sum, args=[path])
        t.start()
        threads.append(t)

    for t in threads:
        t.join()