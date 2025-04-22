#!/usr/bin/env python3

import socket

### Arduino Serial ###
SERIAL_PORT = "COM4"
BAUD_RATE = 115200
BT_ADDR = "3C:95:09:9A:00:B2"

def main():
    ser = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
    port = 8  # Arbitrary non-reserved port
    ser.bind((BT_ADDR, port))
    data = ""

    while True:
        if data == "":
            # Listen for incoming connections
            ser.listen(1)

            # Accept a connection
            client_socket, address = ser.accept()
            print(f"Accepted connection from {address}")
        
        data = client_socket.recv(1024)
        data = data.decode()

        if data != "":
            print(f"Received: {data}")

if __name__ == "__main__":
    main()