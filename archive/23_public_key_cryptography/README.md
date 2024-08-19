# RSA Encryption and Signatures

### Generating RSA Keys & Extracting Looking Inside the Private Key

```bash
$ openssl genrsa -aes128 -out private.pem 1024 # passphrase csci476
$ more private.pem
```

```bash
$ openssl rsa -in private.pem -noout -text
```

### Extracting the Public Key

```bash
$ openssl rsa -in private.pem -pubout > public.pem
$ more public.pem
```
```bash
$ openssl rsa -in public.pem -pubin -text -noout
```

###

```bash
$ echo "This is a secret." > msg.txt
```

### PKCS Padding

```bash
$ openssl rsautl -encrypt -inkey public.pem -pubin -in msg.txt -out msg.enc -pkcs

$ openssl rsautl -decrypt -inkey private.pem -in msg.enc -out newmsg_pkcs.txt -raw
Enter pass phrase for private.pem: csci476
```
```
$ xxd newmsg_pkcs.txt
00000000: 0002 a6dc c092 9a2e 4a8e 3849 c14f cf0b  ........J.8I.O..
00000010: b036 de51 b222 28ab 1b98 6018 5e04 b084  .6.Q."(...`.^...
00000020: 31fc c2ef 680f a4f7 07c9 2b04 8d84 089d  1...h.....+.....
00000030: a2f3 5bbc 2f82 2969 18a1 6c09 2762 82a6  ..[./.)i..l.'b..
00000040: 7d26 b7e0 1a41 077b 86a8 4459 9a0d 6b61  }&...A.{..DY..ka
00000050: af55 a61d 0101 8f26 1ed1 cc3b 33c9 74db  .U.....&...;3.t.
00000060: bad1 38a4 dd0e 59b5 8097 4d93 a400 5468  ..8...Y...M...Th
00000070: 6973 2069 7320 6120 7365 6372 6574 2e0a  is is a secret..
```

### OAEP Padding

```bash
$ openssl rsautl -encrypt -inkey public.pem -pubin -in msg.txt -out msg.enc -oaep

$ openssl rsautl -decrypt -inkey private.pem -in msg.enc -out newmsg_oaep.txt -raw
Enter pass phrase for private.pem: csci476
```
```
$ xxd newmsg_oaep.txt
00000000: 00cd 119c 1376 6ea4 bb17 cd2e 5462 52a1  .....vn.....TbR.
00000010: 4dd1 2031 f446 c3ea f000 55b2 785d 86ba  M. 1.F....U.x]..
00000020: 97af dba7 4ee1 cd02 5fa3 4752 488d f523  ....N..._.GRH..#
00000030: 9d7c c69b f1a8 dba2 c4d1 9c14 f0f1 4abe  .|............J.
00000040: 3c1c e904 711d 0944 2f0b 8b72 7f82 06dc  <...q..D/..r....
00000050: 50af bf94 cac1 b402 7522 7d17 6fc8 699d  P.......u"}.o.i.
00000060: e4ab fff9 952a fb47 673e 7bf5 729f 96bb  .....*.Gg>{.r...
00000070: c282 b678 15c5 2a22 5ae6 bcf1 51be 1a2e  ...x..*"Z...Q...
```

### Digital Signatures

```bash
# Generate a sha256 hash of the secret message
$ openssl sha256 -binary msg.txt > msg.sha256
$ xxd msg.sha256
```
```
00000000: 8272 61ce 5ddc 974b 1b36 75a3 ed37 48cd  .ra.]..K.6u..7H.
00000010: 83cd de93 85f0 6aab bd94 f50c db5a b460  ......j......Z.`
```

```bash
# Sign the hash
$ openssl rsautl -sign -inkey private.pem -in msg.sha256 -out msg.sig
Enter pass phrase for private.pem: csci476
$ xxd msg.sig
```
```
00000000: 4bef 0ab3 b0e4 d1b7 0689 0ee3 2337 8156  K...........#7.V
00000010: e1e4 063e 1bad 46af 8059 4280 d42e 08f9  ...>..F..YB.....
00000020: cd1a cdfd 39d6 8897 6e94 24f1 f7d6 6c90  ....9...n.$...l.
00000030: b222 f99a a784 e6b5 c2b4 4ab7 7176 2dc9  ."........J.qv-.
00000040: 65d3 4639 81be ae72 8282 2f2e 43df 5af3  e.F9...r../.C.Z.
00000050: 2a02 3206 5065 b7eb 49ec 7631 a11d e665  *.2.Pe..I.v1...e
00000060: bb8a d3fe fe22 f7ea 0563 a88f 8cf5 0c56  ....."...c.....V
00000070: 7f67 45ab 8606 1cc6 d2b5 7cd9 4c8e 0c9b  .gE.......|.L...
```
```bash
# Verify the signature
$ openssl rsautl -verify -inkey public.pem -in msg.sig -pubin -raw | xxd
```
```
00000000: 0001 ffff ffff ffff ffff ffff ffff ffff  ................
00000010: ffff ffff ffff ffff ffff ffff ffff ffff  ................
00000020: ffff ffff ffff ffff ffff ffff ffff ffff  ................
00000030: ffff ffff ffff ffff ffff ffff ffff ffff  ................
00000040: ffff ffff ffff ffff ffff ffff ffff ffff  ................
00000050: ffff ffff ffff ffff ffff ffff ffff ff00  ................
00000060: 8272 61ce 5ddc 974b 1b36 75a3 ed37 48cd  .ra.]..K.6u..7H.
00000070: 83cd de93 85f0 6aab bd94 f50c db5a b460  ......j......Z.`
```

##### Experiment: (Attempted) Attack on Digital Signatures

Modify 1 bit in the `msg.sig` file, then attempt to verify the signature again:
```bash
$ xxd msg.sig
```
```
00000000: 4bef 0ab3 b0e4 bf06 890e e323 3781 56e1  K..........#7.V.
00000010: e406 3e1b ad46 af80 5942 80d4 2e08 f9cd  ..>..F..YB......
00000020: 1acd fd39 bf97 6e94 24f1 f7d6 6c90 b222  ...9..n.$...l.."
00000030: f99a a784 e6b5 b44a b771 762d c965 d346  .......J.qv-.e.F
00000040: 3981 beae 7282 822f 2e43 df5a f32a 0232  9...r../.C.Z.*.2
00000050: 0650 65b7 eb49 ec76 31a1 1de6 65bb 8ad3  .Pe..I.v1...e...
00000060: fefe 22f7 ea05 63a8 8f8c f50c 567f 6745  .."...c.....V.gE
00000070: ab86 061c c6bf 7cd9 4c8e 0c9a            ......|.L...
```

```bash
$ openssl rsautl -verify -inkey public.pem -in msg.sig -pubin -raw | xxd
```
```
00000000: 07a4 8d1c cfb8 b36c 17af e821 a9ea 8c80  .......l...!....
00000010: c654 74b0 afb1 c1d8 616c 9dca 5138 3b9d  .Tt.....al..Q8;.
00000020: 8111 234e d20f 033f 07f2 7f7c a88e 4fb1  ..#N...?...|..O.
00000030: 14e0 8132 6b6e ae1e 2a4c be54 ff61 f2e6  ...2kn..*L.T.a..
00000040: 965e 492c 428a 2cd3 8c07 7764 480d 2697  .^I,B.,...wdH.&.
00000050: db36 f2a4 7916 27aa 8a07 17c4 d94a 1f06  .6..y.'......J..
00000060: 2632 cf4b fb2c e98f fb68 cbe1 b084 3bb1  &2.K.,...h....;.
00000070: bb98 651c 0469 14f5 2f92 0e91 93d7 2d09  ..e..i../.....-.
```

**NOTE:**
I use vim via the commandline, but you may find it easier to use a hex editor such as `bless`.
To view the content of a binary file in a hex view, open the file, switch on binary mode,
and filter the buffer through the `xxd` command:
```
:set binary
:%!xxd
```
You can make changes in the left area (edit the hex numbers),
and when ready, filter through `xxd -r`, and finally save the file:
```
:%!xxd -r
:w
```
