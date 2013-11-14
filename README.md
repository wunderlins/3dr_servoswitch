# 3DR Servoswitch 

## Synopsis
This is an alternative software for the 3DR servo switch. It is intended to pass a servo signal to canon camera (running CHDK). The signal sent from the r/c channel is used to trigger the shutter or turn off the camera. 

## Hardware
The 3DR servoswitch is using a PPM signal as input, sending a pules to the USB connector on the canon camera. The pulse is then measured by CHDK and according to its length a method called.

## Documentation
### CHDK usb trigger
http://chdk.wikia.com/wiki/USB_Remote_Cable
http://chdk.wikia.com/wiki/USB_Remote_V2#Scripting_Interface

### 3DR servo switch
Product:
http://store.3drobotics.com/products/servoswitch-v10-kit

Stock Firmware:
http://api.ning.com/files/0e88uzDl6VLSEe7ElgdWSAI3uf-4rS4IZtvEagUt8OkHRZiklbQI7zHbS2fJ7htODmkjRQD7e8VwBJe-O1pQkFZQUB6qiK*2/Servoswitch_firmware.zip%22%3EServoswitch_firmware.zip

Diagram:
http://api.ning.com/files/0e88uzDl6VL-JRwm5GtqnevinFv8CPxzpHkm05yYamcW2lNmRD88HMtkC4avYaAVVqHMhRVGKzUBx2qigoAd6sKhYPsniNnz/Servo_Switch_v10.pdf%22%3EServo_Switch_v10.pdf

Board layout:
http://stuff.storediydrones.com/ServoSwitch_v10_listing.rar
