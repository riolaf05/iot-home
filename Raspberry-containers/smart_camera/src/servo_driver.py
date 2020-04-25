import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.OUT)
p = GPIO.PWM(17, 50)
p.start(7.5)

def get_pwm(angle):
    return (angle/18.0) + 2.5

def move_servo(angle):
	try:
		while True:
			p.ChangeDutyCycle(get_pwm(angle))  # turn towards 90 degree (7.5 duty cycle), 0 degree (2.5 duty cycle), 180 degree (12.5 duty cycle)
			time.sleep(1) # sleep 1 second
			break
	except KeyboardInterrupt:
		p.stop()
		GPIO.cleanup()