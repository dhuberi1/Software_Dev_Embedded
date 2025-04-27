#!/usr/bin/env python3

import time
import socket
import sys
import pigpio

# VARIABLES
### UDP Socket ###
UDP_IP = "172.20.10.2" # IP ADDRESS OF HOST DEVICE
UDP_PORT = 9001

### I2C ###
SDA = 10
SCL = 11
I2C_ADDR = 9
pi = pigpio.pi()
data = ""

# Function to connect to udp 
def init_udp_socket() -> socket.socket:
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        print(f"UDP socket ready to send to {UDP_IP}:{UDP_PORT}")
        return sock
    except socket.error as e:
        print(f"Socket creation error: {e}")
        sys.exit(1)

# from https://abyz.me.uk/rpi/pigpio/code/bsc_arduino_py.zip
def i2c(id, tick):
    global pi
    global data
    s, b, d = pi.bsc_i2c(I2C_ADDR)

    if b:

        print(d[:-1])
        data = d[:-1]

def init_i2c():
    if not pi.connected:
        exit()

    # Add pull-ups in case external pull-ups haven't been added

    pi.set_pull_up_down(SDA, pigpio.PUD_UP)
    pi.set_pull_up_down(SCL, pigpio.PUD_UP)

    # Respond to BSC slave activity
    e = pi.event_callback(pigpio.EVENT_BSC, i2c)

    pi.bsc_i2c(I2C_ADDR) # Configure BSC as I2C slave

    print("I2C device connected")

def main():
    global data
    
    udp_sock = init_udp_socket()
    init_i2c()

    while True:
        try:
            if data != "":
                print(f"Sending: {data}")
                udp_sock.sendto(data, (UDP_IP, UDP_PORT))

        except Exception as e:
            print(f"Unexpected error: {e}")

if __name__ == "__main__":
    main()