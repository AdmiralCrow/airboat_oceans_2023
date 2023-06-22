import RPi.GPIO as GPIO
import time

# Pin Definitions
in1_pin = 23
in2_pin = 24
in3_pin = 6
in4_pin = 25
ena_pin = 13  # replace with the pin you connected ENA to
enb_pin = 12  # replace with the pin you connected ENB to

# Set up GPIO pins
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(in1_pin, GPIO.OUT)
GPIO.setup(in2_pin, GPIO.OUT)
GPIO.setup(in3_pin, GPIO.OUT)
GPIO.setup(in4_pin, GPIO.OUT)

GPIO.setup(ena_pin, GPIO.OUT)
GPIO.setup(enb_pin, GPIO.OUT)



ena_pwm = GPIO.PWM(ena_pin, 100)  # 100 Hz frequency
enb_pwm = GPIO.PWM(enb_pin, 100)

ena_pwm.start(50)  # 50% duty cycle
enb_pwm.start(50)


# Forward
print("Moving forward")
GPIO.output(in1_pin, GPIO.LOW)
GPIO.output(in2_pin, GPIO.HIGH)
GPIO.output(in3_pin, GPIO.HIGH)
GPIO.output(in4_pin, GPIO.LOW)
time.sleep(5) # delay for 2econds

# Backward
print("Moving backward")
GPIO.output(in1_pin, GPIO.HIGH)
GPIO.output(in2_pin, GPIO.LOW)
GPIO.output(in3_pin, GPIO.LOW)
GPIO.output(in4_pin, GPIO.HIGH)
time.sleep(5)


# Clean up
print("Cleaning up")
GPIO.cleanup()
