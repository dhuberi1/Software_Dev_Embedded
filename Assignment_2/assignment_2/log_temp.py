import serial
import serial.tools.list_ports
import time
import os 
import matplotlib.pyplot as plt
import pandas as pd

# Set our  variables
#SERIAL_PORT = "/dev/cu.usbmodemF412FA6E8AC02"
SERIAL_PORT = "COM3"
BAUD_RATE = 9600 
FN = "temperature_log.csv"

ports = serial.tools.list_ports.comports()
for port, desc, hwid in sorted(ports):
    print("{}: {} [{}]".format(port, desc, hwid))

try: 
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2) # just incase it takes time to establish a connection 

    # Open file to export csv
    with open(FN, "w") as file: 
        # Write header 
        file.write("Time (s),Temperature (F)\n")

        print(f"Logging data to {FN}")

        start_time = time.time()

        # Actually read the serial data 
        while True: 
            data = ser.readline().decode().strip()
            if data: 
                print(data)
                file.write(data + "\n")
except KeyboardInterrupt as e: 
    print(f"\nLogging stopped. File saved - {e}")
finally: 
    # Close serial port if its been opened 
    if 'ser' in locals() and ser.is_open:
        ser.close() 

# Section to plot data (TODO : could make it another script that is called when this is complete?)
if os.path.exists(FN) and os.stat(FN).st_size > 0:
    df = pd.read_csv(FN)

    if "Time (s)" in df.columns and "Temperature (F)" in df.columns:
        plt.figure(figsize=(8, 5))
        plt.plot(df["Time (s)"].div(10000), df["Temperature (F)"], marker="o", linestyle="-", color="b")
        plt.xlabel("Time (s)")
        plt.ylabel("Temperature (F)")
        plt.title("Temperature vs Time")
        plt.grid()
        plt.show()
    else:
        print("Error: CSV file format is incorrect.")