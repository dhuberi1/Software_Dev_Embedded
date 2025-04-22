#!/usr/bin/env python3
import serial
import serial.tools.list_ports
import time
import sys
import socket

# VARIABLES
### Arduino Serial ###
SERIAL_PORT = "/dev/ttyACM0"
BAUD_RATE = 115200

## Bluetooth ##
BT_ADDR = "3C:95:09:9A:00:B2"
UUID = "c7f94713-891e-496a-a0e7-983a0946126e"
BT_PORT = 8

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

def main():
    list_serial_ports()
    ser = init_serial(SERIAL_PORT, BAUD_RATE, 1)
    connected = False

    while connected == False:
        try:
            bt_sock = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
            bt_sock.connect((BT_ADDR, BT_PORT))
            connected = True
        except Exception as e:
            print(e)

    while True:
        try:
            if ser.in_waiting > 0:
                data = ser.readline().decode('utf-8', errors='ignore').strip()
                if data:
                    print(f"Sending: {data}")
                    bt_sock.send(data.encode('utf-8'))

        except Exception as e:
            print(f"Unexpected error: {e}")


if __name__ == "__main__":
    main()