from datetime import datetime
import csv
import os
from picamera2 import Picamera2, Preview
import time

from inputs import devices, get_gamepad
import serial

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)  # Raspberry Pi
    # ser = serial.Serial('/dev/tty.usbmodem14601', 9600, timeout=1)  # Linux/macOS
    ser.flush()

    csv_filename = 'temperature_data.csv'  # Name of the CSV file

    # Check if the CSV file exists
    file_exists = os.path.isfile(csv_filename)
    
    picam2 = Picamera2()
    camera_config = picam2.create_still_configuration(main={"size": (1920, 1080)}, lores={"size": (640, 480)}, display="lores")
    picam2.configure(camera_config)
    picam2.start()
    time.sleep(2)

    while True:
        # Handle controller input
        for device in devices.gamepads:
            events = get_gamepad()
            for event in events:
                if event.ev_type == 'Key' and event.state == 1:
                    command = event.code
                    print(command)
                    # Execute command based on the button pressed
                    if command == 'BTN_SOUTH':  # Replace 'BTN_SOUTH' with the actual button code
                        ser.write(b'backward\n')
                    elif command == 'BTN_WEST':  # Replace 'BTN_WEST' with the actual button code
                        ser.write(b'left\n')
                    elif command == 'BTN_NORTH':  # Replace 'BTN_NORTH' with the actual button code
                        ser.write(b'forward\n')
                    elif command == 'BTN_EAST':  # Replace 'BTN_EAST' with the actual button code
                        ser.write(b'right\n')
                    elif command == 'BTN_TL':
                        ser.write(b'stop\n')
                    elif command == 'BTN_TR':
                         # Read sensor data
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
                    elif command == 'BTN_START':
                                timestamp = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
                                picam2.capture_file(timestamp+'.jpg')
