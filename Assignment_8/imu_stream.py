#!/usr/bin/env python3
import socket

### UDP Socket ###
UDP_IP = "192.168.1.229" # IP ADDRESS OF HOST DEVICE
UDP_PORT = 9001

imu_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
imu_socket.bind((UDP_IP, UDP_PORT))

while True:
    try:
        data, addr = imu_socket.recvfrom(1024) # buffer size is 1024 bytes
        data = data.decode()
        print(data)

    except KeyboardInterrupt as e: 
        print("Exiting...")
        break