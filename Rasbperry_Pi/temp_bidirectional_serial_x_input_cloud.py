from datetime import datetime
import os
import time

from inputs import devices, get_gamepad
from pymongo import MongoClient
import serial

from picamera2 import Picamera2

if __name__ == '__main__':
    uri = "mongodb+srv://db-user:db-password@cluster0.7tv1lgs.mongodb.net/?retryWrites=true&w=majority"

    # Create a new client and connect to the server
    client = MongoClient(uri)

    # Access the desired database and collection
    db = client['in-situ_data']
    collection = db['gps_temperature']

    # Send a ping to confirm a successful connection
    try:
        client.admin.command('ping')
        print("Pinged your deployment. You successfully connected to MongoDB!")
    except Exception as e:
        print(e)

    # Initialize trajectory_id from the max value in the collection, or set to 0 if not found
    max_doc = collection.find_one(sort=[("trajectory_id", -1)])
    if max_doc and "trajectory_id" in max_doc:
        trajectory_id = max_doc["trajectory_id"] + 1
    else:
        trajectory_id = 0

    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)  # Raspberry Pi
    # ser = serial.Serial('/dev/tty.usbmodem14601', 9600, timeout=1)  # Linux/macOS
    ser.flush()

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
                            temp, lat, lon = map(float, line.split(','))

                            # Write the sensor data to the MongoDB collection
                            data = {
                                'datetime': datetime.now(),
                                'temperature': temp,
                                'latitude': lat,
                                'longitude': lon,
                                'trajectory_id': trajectory_id
                            }
                            collection.insert_one(data)
                    elif command == 'BTN_START':
                        timestamp = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
                        picam2.capture_file(timestamp + '.jpg')
                    elif command == 'BTN_SELECT':
                        # Increment the trajectory id by 1
                        trajectory_id += 1
