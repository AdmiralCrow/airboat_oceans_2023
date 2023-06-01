import serial
import pynmea2

# Open a serial connection to the GPS module
gps = serial.Serial('/dev/serial0', 9600)

while True:
    line = gps.readline()
    if line[0:6] == b'$GPGGA':  # GGA sentences contain time, coordinates, and fix status
        msg = pynmea2.parse(line.decode('utf-8'))
        print('Time: ', msg.timestamp)
        print('Lat: ', msg.lat)
        print('Lon: ', msg.lon)
        print('Altitude: ', msg.altitude)
