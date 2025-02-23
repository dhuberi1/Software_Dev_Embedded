import serial
import serial.tools.list_ports
import time
import pandas as pd
import matplotlib.pyplot as plt
import os 

# Adjust port and baud rate based on your setup
baud_rate = 9600
filename = "rpm_data.csv"
arduino_port = "/dev/cu.usbmodemF412FA6E8AC02"

ports = serial.tools.list_ports.comports()
for port, desc, hwid in sorted(ports):
    print("{}: {} [{}]".format(port, desc, hwid))
try: 
    ser = serial.Serial(arduino_port, baud_rate, timeout=1)
    time.sleep(2)  # Wait for connection to establish

    with open(filename, "w", newline="") as file:
        while True:
            line = ser.readline().decode().strip()
            if line:
                print(line)  # Print to console
                file.write(line + "\n")  # Actually write it to file 
except KeyboardInterrupt as e: 
    print(f"\nLogging stopped. {e}")
finally: 
    if 'ser' in locals() and ser.is_open: 
        ser.close()

if os.path.exists(filename) and os.stat(filename).st_size > 0:  
    df = pd.read_csv(filename)
    df['Timestamp'] = pd.to_numeric(df['Timestamp'], errors='coerce').astype('Int64')
    df["Timestamp"] = df["Timestamp"].div(1000)

    # Plot RPM over time
    plt.plot(df["Timestamp"], df["RPM"], marker="o", linestyle="-", color="b")
    plt.xlabel("Time in seconds")
    plt.ylabel("RPM - rotations per minute")
    plt.title("RPM vs Time")
    plt.grid()
    plt.show()
