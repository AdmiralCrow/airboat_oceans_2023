# Airboats Arduino and Raspberry Pi Scripts

This repository contains the Arduino code and Raspberry Pi scripts used to control the low-cost airboats for collecting in-situ data. The airboats are equipped with various sensors to collect data along their trajectories. The collected data includes water depth measurements, GPS coordinates, and other environmental parameters. This code is part of the accompanying source code for the publication titled "Privacy-Preserving Multi-Agent Marine Data Collection via Differential Privacy" published to the Oceans 2023 Gulfcoast conference proceedings.

## Prerequisites

To run the code in this repository, you will need the following hardware components:

- Arduino board (e.g., Arduino Mega)
- Raspberry Pi board (e.g., Raspberry Pi 4)
- Motor drivers and motors for airboat propulsion
- Ultrasonic sensor for water depth measurements
- GPS module for obtaining GPS coordinates
- Other sensors as required

Arduino Libraries: LinkedList, Gaussian, LiquidCrystal_I2C, OneWire, DallasTemperature, SPI, HCSR04, SD, TinyGPS++, RTClib, DTH_Turbidity

Python pip packages: inputs, pymongo, picamera2 (for 64-bit distros), picamera (for 32-bit distros), RPLCD

## Getting Started

1. Clone this repository to your Raspberry Pi and Arduino boards.

2. Upload the Arduino code to your Arduino board using the Arduino IDE.
   - For Arduino only bluetooth control, upload 'remote_control' or 'remote_control_noisy' if you want to add Gaussian Noise.
   - Bluetooth module must be plugged in to the "Serial 1" rx/tx pins, but bluetooth must be unplugged while uploading sketches using USB.
   - For sending data via serial, run 'temp_bidirectional_serial_gps'

3. Connect the hardware components using the pins written in the source file.

4. Run the Raspberry Pi scripts to control the airboats and collect in-situ data.
    - To read data from arduino running 'temp_bidirectional_serial_gps', run 'temp_bidirectional_serial_x_input.py' with an x-input USB controller.

## TinkerCAD Files
- https://www.tinkercad.com/things/2HkaIUoovXk-hb-board
- https://www.tinkercad.com/things/8cseTstDqRV-hb
- https://www.tinkercad.com/things/ijvlaEuduuK-hb-cover
- https://www.tinkercad.com/things/3tqFxbGQxOx-swanky-fulffy

## Usage

- The Arduino code handles the motor control and sensor readings on the airboat.

- The Raspberry Pi scripts communicate with the Arduino board and gather sensor data.

- The collected data can be stored locally using 'temp_bidirectional_serial_x_input.py' or transmitted to a remote database using 'temp_bidirectional_serial_x_input_cloud.py'.

## Contributors

- Anthony Devesa(https://github.com/AdmiralCrow)
- Cesar Rojas(https://github.com/croja022)
- Gregory Reis(https://github.com/paulodocervo)
- Paulo Padrao(https://github.com/pvpadrao)

## License

This project is licensed under the [MIT License](LICENSE).
