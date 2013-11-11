# 3DR Servoswitch 

## Synopsis
This is an alternative software for the 3DR servo switch. It is intended to pass a servo signal to canon camera (running CHDK). The signal sent from the r/c channel is used to trigger the shutter or turn off the camera. 

## Hardware
The 3DR servoswitch is using a PPM signal as input, sending a pules to the USB connector on the canon camera. The pulse is then measured by CHDK and according to its length a method called.

