#!/usr/bin/env python3

import socket

### Bluetooth ###
#BT_ADDR = "3C:95:09:9A:00:B2" # Host
BT_ADDR = "D8:3A:DD:EE:EE:E2" # RPi
BT_PORT = 8 # Arbitrary non-reserved port

def main():
    connected = False

    while True:
        while connected == False:
            try:
                bt_sock = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
                bt_sock.connect((BT_ADDR, BT_PORT))
                connected = True
                print("Connected!")

            except Exception as e:
                print(e)
                
        data = bt_sock.recv(1024)
        data = data.decode()

        if data != "":
            print(f"Received: {data}")
        else:
            connected = False

if __name__ == "__main__":
    main()