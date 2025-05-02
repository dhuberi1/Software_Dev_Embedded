#!/usr/bin/env python3

import socket
import gpsd

### GPS Socket ###
GPS_IP = "172.20.10.3" # Replace with the IP of the Raspberry Pi
GPS_PORT = 2947 # Replace with the desired port

gpsd.connect(host=GPS_IP, port=GPS_PORT)

### UDP Socket ###
IMU_IP = "172.20.10.2" # IP ADDRESS OF HOST DEVICE
IMU_PORT = 9001

imu_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
imu_socket.bind((IMU_IP, IMU_PORT))

while True:
    try:
        # GPS
        packet = gpsd.get_current()
        #print(packet.position())
        print("Lat:", packet.lat, " Lon:", packet.lon, " Alt:", packet.alt)

    except KeyboardInterrupt as e: 
        print("Error receiving GPS data!")
        print(e)
        break

    try:
        # IMU
        data, addr = imu_socket.recvfrom(1024) # buffer size is 1024 bytes
        data = data.decode()
        print(data)

    except KeyboardInterrupt as e: 
        print("Error receiving IMU data!")
        print(e)
        break
