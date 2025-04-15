#!/usr/bin/env python3
import serial
import serial.tools.list_ports
import time
import socket

# VARIABLES
### Arduino Serial ###
SERIAL_PORT = "/dev/ttyACM0"
BAUD_RATE = 115200

### UDP Socket ###
UDP_IP = "192.168.1.229" # IP ADDRESS OF HOST DEVICE
UDP_PORT = 9001

# Check Device Ports
ports = serial.tools.list_ports.comports()
for port, desc, hwid in sorted(ports):
    print("{}: {} [{}]".format(port, desc, hwid))

# Connect to serial
try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2) # in case it takes time to establish a connection

except Exception as e:
    print(e)

# Connect to UDP socket
try:
    imu_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

except Exception as e:
    print(e)


while True:
    try:
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').rstrip()
            print(data)

            imu_socket.sendto(data.encode('utf-8'), (UDP_IP, UDP_PORT))
        
    except Exception as e:
        print(e)
