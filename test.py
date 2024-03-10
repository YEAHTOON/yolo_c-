import sys
import fcntl
import os


# the_input = sys.stdin.readline()
fcntl.fcntl(sys.stdin, fcntl.F_SETFL, os.O_NONBLOCK)

while True:
    the_input = sys.stdin.buffer.read()
    print(the_input)
