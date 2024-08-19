# TCP Attacks

In the following demos:
- **Server == 10.0.2.8**
- **User == 10.0.2.9**
- **Attacker == 10.0.2.10**


### TCP Reset Attack - Telnet

1. Attacker (runs `tcpdump`):
```bash
sudo tcpdump 'tcp and (src host 10.0.2.9 or src host 10.0.2.8)' -vvXXn --absolute-tcp-sequence-numbers
```

2. User (runs `telnet`):
```bash
$ telnet 10.0.2.8
```

3. Attacker updates `reset.py` with source ip/port, destination ip/port, and (next) sequence number.
The next sequence number can be obtained from tools such as `wireshark` or `tcpdump`.

**HINT:** In `tcpdump`, you can use the `ack` value in the most recent packet from the **USER** to the **SERVER** to determine the sequence number to use. Alternatively, `wireshark` will calculate it for you (see textbook for details).

After the RST packet has been sent you should see:
```bash
seed@server(10.0.2.8):~$ Connection closed by foreign host.
seed@user(10.0.2.9):~$
```

### TCP Reset Attack - SSH

The attack is nearly identical for SSH, but you need to use ssh port (22) instead of telnet port (23).
```bash
seed@user(10.0.2.9):~/.ssh$ ssh server
seed@10.0.2.8 password:
...
seed@server(10.0.2.8):~$
```

After the RST packet has been sent you should see:
```bash
seed@server(10.0.2.8):~$ packet_write_wait: Connection to 10.0.2.8 port 22: Broken pipe
seed@user(10.0.2.9):~$
```

### TCP Reset Attack - Video Streaming Connection

A similar approach works for reseting a video-streaming connection,
but the sequence numbers change far too quickly to track them manually.
Thus, we use the `reset_auto.py` script.

```bash
sudo python reset_auto.py
```
It seems the python version, however, is too slow... so we can try with a C version,
which is already built into the `netwox 78` tool.
```bash
sudo netwox 78 --filter 'src host 10.0.2.9'
```

For simplicity, we _can_ use `reset_auto.py` to show how quickly we can reset telnet and ssh connections.
