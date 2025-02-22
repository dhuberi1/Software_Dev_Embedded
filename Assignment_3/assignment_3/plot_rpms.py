import serial
import csv
import time
import pandas as pd
import matplotlib.pyplot as plt

# Adjust port and baud rate based on your setup
arduino_port = "COM3"  
baud_rate = 9600
filename = "rpm_data.csv"

ser = serial.Serial(arduino_port, baud_rate, timeout=1)
time.sleep(2)  # Wait for connection to establish

with open(filename, "w", newline="") as csvfile:
    csv_writer = csv.writer(csvfile)
    while True:
        line = ser.readline().decode().strip()
        if line:
            print(line)  # Print to console
            csv_writer.writerow(line.split(", "))  # Actually write it to file 

# Plot with pandas - Assumes file is correctly written 
df = pd.read_csv("rpm_data.csv")

# Convert timestamps to seconds
df["Timestamp"] = (df["Timestamp"] - df["Timestamp"][0]) / 1000

# Plot RPM over time
plt.plot(df["Timestamp"], df["RPM"], marker="o", linestyle="-", color="b")
plt.xlabel("Time in seconds")
plt.ylabel("RPM - rotations per minute")
plt.title("RPM vs Time")
plt.grid()
plt.show()
