import time

import serial

# Initialize serial connection
ser = serial.Serial('/dev/ttyS0', 9600)  # Replace '/dev/ttyS0' with your serial port


def read_serial():
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(f"Received: {line}")


if __name__ == "__main__":
    try:
        read_serial()
    except KeyboardInterrupt:
        print("Serial reading stopped.")
        ser.close()
