#!/usr/bin/env python3
import serial
import serial.tools.list_ports
import time

# Set our variables
SERIAL_PORT = "/dev/ttyACM0"
BAUD_RATE = 115200

ports = serial.tools.list_ports.comports()
for port, desc, hwid in sorted(ports):
    print("{}: {} [{}]".format(port, desc, hwid))

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2) # in case it takes time to establish a connection

except Exception as e:
    print(e)

while True:
    try:
         if ser.in_waiting > 0:
              data = ser.readline().decode('utf-8').rstrip()
              print(data)
    except Exception as e:
         print(e)
