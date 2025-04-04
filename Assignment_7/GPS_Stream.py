#! /usr/bin/env python3

import gpsd

IP = "172.20.10.3" # Replace with the IP of the Raspberry Pi
PORT = 2947 # Replace with the desired port

gpsd.connect(host=IP, port=PORT)

# Get GPS position and altitude
while True:
    try:
        packet = gpsd.get_current()
        #print(packet.position())
        print("Lat:", packet.lat, " Lon:", packet.lon, " Alt:", packet.alt)
    except KeyboardInterrupt as e: 
        print("Exiting...")
        break
    except:
        pass