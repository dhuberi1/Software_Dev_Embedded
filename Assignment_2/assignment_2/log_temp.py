import serial
import serial.tools.list_ports
import time

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
        file.write("Time (s), Temperature (F)\n")

        print(f"Logging data to {FN}")

        start_time = time.time()

        # Actually read the serial data 
        while True: 
            data = ser.readline().decode().strip() 
            if data: 
                elapsed_time = round(time.time() - start_time, 2)
                formatted_data = f"{elapsed_time}, {data}" # make sure its in csv format
                formatted_data = data
                print(formatted_data)
                file.write(formatted_data + "\n")
except KeyboardInterrupt as e: 
    print(f"\nLogging stopped. File saved - {e}")
finally: 
    # Close serial port 
    ser.close() 