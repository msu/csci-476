"""
A recursive Python implementation of the 
Extended Euclidean Algorithm

inputs: positive integers a, b
outputs: a tuple s.t. ax + by = g = gcd(a,b)
"""
def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, x, y = egcd(b % a, a)
        return (g, y - (b // a) * x, x)

import sys
print( egcd(int(sys.argv[1]), int(sys.argv[2])) )
