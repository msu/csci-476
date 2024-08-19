#!/usr/bin/python3

import random
s = 'abcdefghijklmnopqrstuvwxyz'
list = random.sample(s, len(s))
k = ''.join(list)

print(s)
print(k)

