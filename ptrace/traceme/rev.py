import sys
from pwn import *
for i in range(1, 6):
    value = int(sys.argv[i], 16)
    print(p64(value).decode().strip('\x00'), end='')
print()
