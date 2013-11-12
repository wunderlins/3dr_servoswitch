/**
 * 3DRobotics servoswitch software
 * 
 * Alternative firmware for the 3D Robotics servoswitch:
 * http://store.3drobotics.com/products/servoswitch-v10-kit
 *
 * This firmware makes it possible to use a 3 position switch on the transmitter.
 * depending on the position of the r/c channel, pulses are sent over a USB 
 * cable to a canon camera. 
 *    pos 0 (< 1300 ns): no action
 *    pos 1 (> 1300 && < 1700ns): camera shutter, 100ms pulse
 *    pos 2 (> 1700ns): camera off, 1000ms pulse
 *
 * This program is made to be used with ATtiny45/85
 *
 * $Id$
 */

// pin setup
#define PIN_PPM 2
#define PIN_CAM 1
#define PIN_LED 3

unsigned long duration, lastgood = 0;
int ppm_in = 0;

void setup() {
	pinMode(PIN_CAM, OUTPUT);
	digitalWrite(PIN_CAM, LOW);
	delay(5000); // make sure the pin is low
	
	pinMode(PIN_PPM, INPUT);
	pinMode(PIN_CAM, OUTPUT);
	
}

void loop() {
  
	/**
	 * check ppm signal
	 * the length of the pulse (in microseconds) or 0 if no pulse 
	 * started before the timeout (unsigned long)
	 *
	 * ppm_in == 0 means the camera should be off or turned off
	 * ppm_in == 1 means the camera should be on or turned on
	 */
	duration = pulseIn(PIN_PPM, HIGH, 20000); 
	if (duration == 0)
		duration = lastgood;
	else
		lastgood = duration;
	ppm_in = map(lastgood, 1000, 2000, 0, 1);
	
	/*
	// if ppm_in is high and cam_state is low, turn the camera on
	if (ppm_in && !cam_state) {
		digitalWrite(PIN_CAM_PWR_BTN, HIGH);
		delay(500);
		digitalWrite(PIN_CAM_PWR_BTN, LOW);
		delay(500);
	}
	*/
	
}

