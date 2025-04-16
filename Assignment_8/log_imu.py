#!/usr/bin/env python3
import serial
import serial.tools.list_ports
import time
import socket
import sys

# VARIABLES
### Arduino Serial ###
SERIAL_PORT = "/dev/ttyACM0"
BAUD_RATE = 115200

### UDP Socket ###
UDP_IP = "172.20.10.2" # IP ADDRESS OF HOST DEVICE
UDP_PORT = 9001

# Check Device Ports
def list_serial_ports():
    print("And our available serial ports are......:")
    for port, desc, hwid in sorted(serial.tools.list_ports.comports()):
        print("{}: {} [{}]".format(port, desc, hwid))

# Function to connect to serial
def init_serial(port: str, baud: int, timeout: int) -> serial.Serial:
    try:
        ser = serial.Serial(port, baud, timeout=timeout)
        time.sleep(2)
        print(f"Connected to serial port: {port} at {baud} baud")
        return ser
    except serial.SerialException as e:
        print(f"Serial connection error: {e}")
        sys.exit(1)

# Functiono to connect to udp 
def init_udp_socket() -> socket.socket:
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        print(f"UDP socket ready to send to {UDP_IP}:{UDP_PORT}")
        return sock
    except socket.error as e:
        print(f"Socket creation error: {e}")
        sys.exit(1)


def main():
    list_serial_ports()
    ser = init_serial(SERIAL_PORT, BAUD_RATE, 1)
    udp_sock = init_udp_socket()

    while True:
        try:
            if ser.in_waiting > 0:
                data = ser.readline().decode('utf-8', errors='ignore').strip()
                if data:
                    print(f"Sending: {data}")
                    udp_sock.sendto(data.encode('utf-8'), (UDP_IP, UDP_PORT))

        except Exception as e:
            print(f"Unexpected error: {e}")

if __name__ == "__main__":
    main()

