from picamera import PiCamera
from time import sleep

camera = PiCamera()
camera.start_preview()
# camera.start_recording('/home/pi/Desktop/video.h264')
sleep(10)
# camera.stop_recording()7uy
camera.stop_preview()