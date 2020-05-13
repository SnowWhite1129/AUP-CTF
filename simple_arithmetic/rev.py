from pwn import *

def add(a, b):
    return a+b
def minus(a, b):
    return a-b
def multiple(a, b):
    return a*b
def divide(a, b):
    return a/b
def op(a, operand, b):
    if operand == '+':
        return add(a,  b)
    elif operand == '-':
        return minus(a, b)
    elif operand == '*':
        return multiple(a, b)
    elif operand == '/':
        return divide(a, b)

r = remote('aup.zoolab.org', 38152)

r.recvuntil('========')
r.readline().decode()
for _ in range(100):
    line = r.recvuntil('?').decode().split()
    r.sendline(str(op(int(line[0]), line[1], int(line[2]))).encode())

print(r.recvuntil('}').decode())
