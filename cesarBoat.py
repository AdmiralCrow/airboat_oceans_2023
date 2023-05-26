from RPLCD.i2c import CharLCD
import os
import glob
import time

import RPi.GPIO as GPIO

# Initialize display. Note: Make sure the I2C address matches the address of your module.
lcd = CharLCD(i2c_expander='PCF8574', address=0x27, port=1, cols=16, rows=2, dotsize=8,
              charmap='A02',
              auto_linebreaks=True,
              backlight_enabled=True)

os.system('modprobe w1-gpio')
os.system('modprobe w1-therm')

base_dir = '/sys/bus/w1/devices/'
device_folder = glob.glob(base_dir + '28*')[0]
device_file = device_folder + '/w1_slave'


# Write a string on first line
lcd.write_string('HydroBoat')


# Pin Definitions
in1_pin = 17
in2_pin = 27
in3_pin = 22
in4_pin = 23
# Pin Definitions
ena_pin = 18  # replace with the pin you connected ENA to
enb_pin = 19  # replace with the pin you connected ENB to

# Set up GPIO pins
GPIO.setmode(GPIO.BCM)
GPIO.setup(in1_pin, GPIO.OUT)
GPIO.setup(in2_pin, GPIO.OUT)
GPIO.setup(in3_pin, GPIO.OUT)
GPIO.setup(in4_pin, GPIO.OUT)
GPIO.setup(ena_pin, GPIO.OUT)
GPIO.setup(enb_pin, GPIO.OUT)
ena_pwm = GPIO.PWM(ena_pin, 100)  # 100 Hz frequency
enb_pwm = GPIO.PWM(enb_pin, 100)  # 100 Hz frequency

# Start PWM
#ena_pwm.start(50)  # 50% duty cycle
#enb_pwm.start(50)  # 50% duty cycle

#time.sleep(5)  # let the motors run for 5 seconds


def read_temp_raw():
    f = open(device_file, 'r')
    lines = f.readlines()
    f.close()
    return lines

def read_temp():
    lines = read_temp_raw()
    while lines[0].strip()[-3:] != 'YES':
        time.sleep(0.2)
        lines = read_temp_raw()
    equals_pos = lines[1].find('t=')
    if equals_pos != -1:
        temp_string = lines[1][equals_pos+2:]
        temp_c = float(temp_string) / 1000.0
        temp_f = temp_c * 1.8 + 32  # Convert the temperature to Fahrenheit
        return temp_f
    
def main():
    while True:
        #lcd.clear()
        tempF = str(read_temp())[:6]
        lcd.cursor_pos = (1, 0)
        lcd.write_string("Temp:"+tempF+"F")
        print(tempF)
        time.sleep(1)
        
print("Moving backward")
GPIO.output(in1_pin, False)
GPIO.output(in2_pin, True)
GPIO.output(in3_pin, False)
GPIO.output(in4_pin, True)
time.sleep(2)

ena_pwm.start(0)  # 50% duty cycle
enb_pwm.start(0) 
while True:
    user_input = input()
    if user_input == "w":
        print("Moving forward")
        GPIO.output(in1_pin, True)
        GPIO.output(in2_pin, False)
        GPIO.output(in3_pin, True)
        GPIO.output(in4_pin, False)
        time.sleep(2) # delay for 2 seconds
    elif user_input == "s":
        print("Moving backward")
        GPIO.output(in1_pin, False)
        GPIO.output(in2_pin, True)
        GPIO.output(in3_pin, False)
        GPIO.output(in4_pin, True)
        time.sleep(2)