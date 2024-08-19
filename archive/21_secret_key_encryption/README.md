# Secret-Key Encryption

Notes and demos below.

### Padding

```bash
echo -n "123456789" > plain.txt

openssl enc -aes-128-cbc -e -in plain.txt -out cipher.bin \
    -K  00112233445566778899AABBCCDDEEFF \
    -iv 000102030405060708090A0B0C0D0E0F

openssl enc -aes-128-cbc -d -in cipher.bin -out plain2.txt \
    -K  00112233445566778899AABBCCDDEEFF \
    -iv 000102030405060708090A0B0C0D0E0F

openssl enc -aes-128-cbc -d -in cipher.bin -out plain3.txt \
    -K  00112233445566778899AABBCCDDEEFF \
    -iv 000102030405060708090A0B0C0D0E0F -nopad

xxd -g 1 plain.txt
xxd -g 1 plain3.txt
```

```bash
echo -n $'\x31\x32\x33\x34\x35\x36\x37\x38\x39\x07\x07\x07\x07\x07\x07\x07' > plain3.txt

openssl enc -aes-128-cbc -e -in plain3.txt -out cipher3.bin \
    -K  00112233445566778899AABBCCDDEEFF \
    -iv 000102030405060708090A0B0C0D0E0F

openssl enc -aes-128-cbc -d -in cipher3.bin -out plain3_new.txt \
    -K  00112233445566778899AABBCCDDEEFF \
    -iv 000102030405060708090A0B0C0D0E0F -nopad

ls -ld plain3.txt
ls -ld cipher3.bin
ls -ld plain3_new.txt
xxd -g 1 plain3_new.txt
```

### Initialization Vectors

```bash
# Store bob's IV in a file to make it easy to use later...
$ echo -n "4ae71336e44bf9bf79d2752e234818a5" > iv_bob
$ cat iv_bob
4ae71336e44bf9bf79d2752e234818a5

# Encrypt Bob's vote
$ echo -n "John Smith......" > p1
$ openssl enc -aes-128-cbc -e -in p1 -out c1 \
    -K  00112233445566778899AABBCCDDEEFF \
    -iv `cat iv_bob`

# Calculate iv_next from iv_bob
$ cat iv_bob | xxd -r -p | md5sum > iv_next
$ cat iv_next
398d01fdf7934d1292c263d374778e1a
```

```bash
$ mkdir init_vectors && cd init_vectors
$ cp ../xor.py .
$ echo -n "John Smith......" > p1_guessed

# Convert the ascii string to a hex string
$ xxd -p p1_guessed
4a6f686e20536d6974682e2e2e2e2e2e

# XOR p1_guessed with iv_bob
$ xor.py `xxd -p init_vectors/p1_guessed` `cat init_vectors/iv_bob`
00887b58c41894d60dba5b000d66368b

# XOR the above result with iv_next
$ xor.py 00887b58c41894d60dba5b000d66368b `cat init_vectors/iv_next`
39057aa5338bd9c49f7838d37911b891

# Convert the above hex string to binary and save to p2
$ echo -n "39057aa5338bd9c49f7838d37911b891" | xxd -r -p > p2
```

```bash
openssl enc -aes-128-cbc -e -in p2 -out c2 \
    -K  00112233445566778899AABBCCDDEEFF \
    -iv `cat iv_next`

# Compare c1 and c2
$ xxd -c 32 -p c1
7380ee1c0f9eb7dae28c1ba6a1a74310114288f771139da8ec99dfb0036e38ce
$ xxd -c 32 -p c2
7380ee1c0f9eb7dae28c1ba6a1a74310114288f771139da8ec99dfb0036e38ce
```
