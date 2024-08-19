# Sniffing and Spoofing Attacks

**Basic scapy stuff to try....**

```python
IP()
IP().show()

IP()/ICMP()

p = IP()/ICMP()
p.show()
p = IP()/UDP()
p.show()

p = IP()/UDP()/"This is my UDP packet"
p.show()

send ( IP()/UDP()/"This is my UDP packet" )

send ( IP(dst='10.0.2.7')/UDP()/"This is my UDP packet" )
```

### Create a packet and look at it...

```python
a = IP()
a.show()
```

### Sniff packets....

```python
#!/usr/bin/python3
from scapy.all import *

print("SNIFFING PACKETS.........")

def print_pkt(pkt):
  pkt.show()

pkt = sniff(filter='icmp',prn=print_pkt)
```

### Spoof packets...

Spoof ICMP packets

```python
#!/usr/bin/python3
from scapy.all import *

print("SENDING SPOOFED ICMP PACKET.........")

ip = IP(src="1.2.3.4", dst="93.184.216.34")
icmp = ICMP()
pkt = ip/icmp
pkt.show()

send(pkt,verbose=0)
```

Spoof UDP packets

```python
#!/usr/bin/python3
from scapy.all import *

print("SENDING SPOOFED ICMP PACKET.........")

ip = IP(src="1.2.3.4", dst="10.0.2.69") # IP Layer
udp = UDP(sport=8888, dport=9090)       # UDP Layer
data = "Hello UDP!\n"                   # Payload
pkt = ip/udp/data      # Construct the complete packet
pkt.show()

send(pkt,verbose=0)
```
