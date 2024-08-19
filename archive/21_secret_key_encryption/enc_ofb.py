#!/usr/bin/python3

from Crypto.Cipher import AES

key_hex_string = '00112233445566778899AABBCCDDEEFF'
iv_hex_string  = '000102030405060708090A0B0C0D0E0F'
key = bytes.fromhex(key_hex_string)
iv  = bytes.fromhex(iv_hex_string)
data = b'The quick brown fox jumps over the lazy dog'

# Encrypt the entire data
cipher = AES.new(key, AES.MODE_OFB, iv)                      
ciphertext = bytearray(cipher.encrypt(data)) 

# Change the 10th byte of the ciphertext
ciphertext[10] = 0xE9

# Decrypt the ciphertext
cipher = AES.new(key, AES.MODE_OFB, iv)                 
plaintext = cipher.decrypt(ciphertext)                 

print(" Original Plaintext: {0}".format(data))
print("Decrypted Plaintext: {0}".format(plaintext))
