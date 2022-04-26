import RPi.GPIO as GPIO
import time
import synscan
import sys
import os
smc=synscan.motors()
zero_switch = 0
azimuth_increment = 10
curr_position = 0
result = 1

GPIO.setmode (GPIO.BCM ) # Broadcom pin-numbering scheme
//GPIO.setup(26, GPIO.IN, pull_up_down=GPIO.PUD_UP) #pin set as input w/ pull-up

n = len(sys.argv)

print("Total arguments passed:", n)
if n < 3 :
	print( "enter from command line python gpiopinonoff.py pin_number initial_state ,current_state" );
	os._exit (0)

GPIO.setmode (GPIO.BCM ) # Broadcom pin-numbering scheme
#calculate position
#//1/65536 * 360 * 60 * 60
#//19.8 arcseconds per unit // arcsec is 1/60 of degree
	position_to_set = float (sys.argv[2]);
        az_position = position_to_set * (360 *60 *60 )/65535

try:
    while GPIO.input(26) != 0 :
        result = GPIO.input(26)
        smc.goto( 0, az_position,syncronous=True)
        
        print ( "current position ")
        print ( curr_position )
        
        
except  KeyboardInterrupt: 
    GPIO.cleanup() # cleanup all GPIO
    
    GPIO.cleanup() # cleanup all GPIO
