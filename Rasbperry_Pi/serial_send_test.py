import time

import serial

# Initialize serial connection
ser = serial.Serial('/dev/ttyS0', 9600)  # Replace '/dev/ttyS0' with your serial port

start_time = time.time()


def send_timestamp():
    while True:
        elapsed_time = round(time.time() - start_time)
        ser.write(f"{elapsed_time}\n".encode())
        time.sleep(1)


if __name__ == "__main__":
    try:
        send_timestamp()
    except KeyboardInterrupt:
        print("Serial sending stopped.")
        ser.close()
