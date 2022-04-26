# External module imports
import RPi.GPIO as GPIO
import time

import sys
import os
output_pin = 24
inital_state = 0
current_state = 1

# Pin Setup:

#GPIO.setup(output_pin, GPIO.OUT) # pin set as output
#GPIO.setup(26, GPIO.OUT) 
#GPIO.setup(19, GPIO.OUT)
#GPIO.setup(13, GPIO.OUT) 
#GPIO.setup(6 , GPIO.OUT) 
#GPIO.setup(5, GPIO.OUT)

#pwm = GPIO.PWM(pwmPin, 50)  # Initialize PWM on pwmPin 100Hz frequency
#GPIO.setup(butPin, GPIO.IN, pull_up_down=GPIO.PUD_UP) # Button pin set as input w/ pull-up
#GPIO.setup ( inppin, GPIO.IN , pull_up_down=GPIO.PUD_UP) # Button pin set as input w/ pull-up
f = open ("/home/pi/netserver/output.txt", "w+")
f.write ( "entering py script\r\n");
f.write ( "this ins num param \r\n")
print( len(sys.argv) )
print ("\r\n")
f.close();

n = len(sys.argv)

print("Total arguments passed:", n)
if n < 4 :
	print( "enter from command line python gpiopinonoff.py pin_number initial_state ,current_state" );
	os._exit (0)
GPIO.setmode (GPIO.BCM ) # Broadcom pin-numbering scheme

print("\nName of Python script:", sys.argv[0])
 
print("\nArguments passed:", end = " ")
for i in range(1, n):
    print(sys.argv[i], end = " ")
print("\n")

output_pin = int (sys.argv[1])
inital_state = int (sys.argv[2])
current_state = int (sys.argv[3])
GPIO.setup(output_pin, GPIO.OUT) # pin set as output

# Initial:
if inital_state == 0 :
	GPIO.output(output_pin, GPIO.LOW)
else:
	GPIO.output(output_pin, GPIO.HIGH)


time.sleep(0.075)
if current_state == 0 :
	GPIO.output(output_pin, GPIO.LOW)
else:
	GPIO.output(output_pin, GPIO.HIGH)
         
	
GPIO.cleanup() 
print ( "script ",sys.argv[0], "Done" )

         
        
    
#GPIO.cleanup() # cleanup all GPIO





