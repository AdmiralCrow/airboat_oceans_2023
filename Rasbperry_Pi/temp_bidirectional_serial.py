from datetime import datetime
import csv
import os

import serial

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)  # Raspberry Pi
    # ser = serial.Serial('/dev/tty.usbmodem14601', 9600, timeout=1)  # Linux/macOS
    ser.flush()

    csv_filename = 'temperature_data.csv'  # Name of the CSV file
    commands = ['forward', 'backward', 'left', 'right']  # List of commands
    counter = 0  # Counter variable

    # Check if the CSV file exists
    file_exists = os.path.isfile(csv_filename)

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            temp = float(line)

            # Save temp to the CSV file
            with open(csv_filename, 'a', newline='') as csvfile:
                writer = csv.writer(csvfile)

                # Add headers if the file was created for the first time
                if not file_exists:
                    writer.writerow(['Datetime', 'Temperature (C)'])
                    file_exists = True

                # Write the current timestamp and temperature
                timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
                writer.writerow([timestamp, temp])

            # Send command for the first 4 iterations
            if counter < 4:
                command = commands[counter]
                ser.write(command.encode())
                ser.write(b'\n')
                print(f"Sent command: {command}")
                counter += 1
