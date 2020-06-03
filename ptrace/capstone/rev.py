import sys
import binascii
from pwn import *
r = remote('aup.zoolab.org', 2530)
while True:
    r.recvuntil('>>> ')
    quiz = r.recvline()
    
    quiz = quiz.decode()
    quiz = quiz.strip('\n')

    quiz= quiz.encode()

    answer = binascii.a2b_hex(quiz)

    payload = disasm(answer, byte=0, offset=0, arch='amd64').replace('   ',' ')
    payload = payload.replace('  ',' ')
    payload +='\n'

    payload = binascii.b2a_hex(payload.encode())
    r.recvuntil('Your answer:')
    r.sendline(payload)
    r.recvline()
    line = r.recvline()
    if b'ASM' in line:
        print(line.decode())
        break
r.interactive()
