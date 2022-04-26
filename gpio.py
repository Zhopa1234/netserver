# External module imports
import RPi.GPIO as GPIO
import time

# Pin Definitons:
#pwmPin = 5 # Broadcom pin 5  (P1 pin 29)
ledPin = 24 # Broadcom pin 26 (P1 pin 31)
#butPin = 13 # Broadcom pin 13 (P1 pin 33)
#inppin = 35 # Broadcom pin 35 (P1 pin 35)


dc = 95 # duty cycle (0-100) for PWM pin

# Pin Setup:
GPIO.setmode (GPIO.BCM ) # Broadcom pin-numbering scheme
GPIO.setup(24, GPIO.OUT) # LED pin set as output
GPIO.setup(26, GPIO.OUT) # PWM pin set as output
GPIO.setup(19, GPIO.OUT)
GPIO.setup(13, GPIO.OUT) 
GPIO.setup(6 , GPIO.OUT) 
GPIO.setup(5, GPIO.OUT)

#pwm = GPIO.PWM(pwmPin, 50)  # Initialize PWM on pwmPin 100Hz frequency
#GPIO.setup(butPin, GPIO.IN, pull_up_down=GPIO.PUD_UP) # Button pin set as input w/ pull-up
#GPIO.setup ( inppin, GPIO.IN , pull_up_down=GPIO.PUD_UP) # Button pin set as input w/ pull-up

# Initial state for LEDs:
GPIO.output(24, GPIO.LOW)
GPIO.output(26, GPIO.LOW)
GPIO.output(19, GPIO.LOW)
GPIO.output(13, GPIO.LOW)
GPIO.output(6, GPIO.LOW)
GPIO.output(5, GPIO.LOW)

#pwm.start(dc)

print("Here we go! Press CTRL+C to exit")
try:
    while 1:
         GPIO.output(24, GPIO.LOW)
         GPIO.output(26, GPIO.LOW)
         GPIO.output(19, GPIO.LOW)
         GPIO.output(13, GPIO.LOW)
         GPIO.output(6, GPIO.LOW)
         GPIO.output(5, GPIO.LOW)
         time.sleep(0.075)
         GPIO.output(24, GPIO.HIGH)
         GPIO.output(26, GPIO.HIGH)
         GPIO.output(19, GPIO.HIGH)
         GPIO.output(13, GPIO.HIGH)
         GPIO.output(6, GPIO.HIGH)
         GPIO.output(5, GPIO.HIGH)         
         time.sleep(0.075)
         GPIO.output(24, GPIO.LOW)
         GPIO.output(26, GPIO.LOW)
         GPIO.output(19, GPIO.LOW)
         GPIO.output(13, GPIO.LOW)
         GPIO.output(6, GPIO.LOW)
         GPIO.output(5, GPIO.LOW)
         time.sleep(0.075)
         GPIO.output(24, GPIO.HIGH)
         GPIO.output(26, GPIO.HIGH)
         GPIO.output(19, GPIO.HIGH)
         GPIO.output(13, GPIO.HIGH)
         GPIO.output(6, GPIO.HIGH)
         GPIO.output(5, GPIO.HIGH)
         time.sleep(0.075)
         GPIO.output(24, GPIO.LOW)
         GPIO.output(26, GPIO.LOW)
         GPIO.output(19, GPIO.LOW)
         GPIO.output(13, GPIO.LOW)
         GPIO.output(6, GPIO.LOW)
         GPIO.output(5, GPIO.LOW)
         time.sleep(0.075)
         GPIO.output(24, GPIO.HIGH)
         GPIO.output(26, GPIO.HIGH)
         GPIO.output(19, GPIO.HIGH)
         GPIO.output(13, GPIO.HIGH)
         GPIO.output(6, GPIO.HIGH)
         GPIO.output(5, GPIO.HIGH)
         time.sleep(0.075)
         GPIO.cleanup() 
         
        
    #while 1:
    #    if GPIO.input(butPin): # button is released
    #        pwm.ChangeDutyCycle(dc)
    #        GPIO.output(ledPin, GPIO.LOW)
    #    else: # button is pressed:
    #        pwm.ChangeDutyCycle(100-dc)
    #        GPIO.output(ledPin, GPIO.HIGH)
    #        time.sleep(0.075)
    #        GPIO.output(ledPin, GPIO.LOW)
    #        time.sleep(0.075)
except KeyboardInterrupt: # If CTRL+C is pressed, exit cleanly:
    #pwm.stop() # stop PWM
    GPIO.cleanup() # cleanup all GPIO





