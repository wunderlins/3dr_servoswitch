/**
 * 3DRobotics servoswitch software
 * 
 * Alternative firmware for the 3D Robotics servoswitch:
 * http://store.3drobotics.com/products/servoswitch-v10-kit
 *
 * This firmware makes it possible to use a 3 position switch on an r/c 
 * transmitter (or use a servo output channel on AMP combined with DO_SERVO 
 * or CAM_TRIGG_DIST).
 *
 * depending on the position of the r/c channel, pulses are sent over a USB 
 * cable to a canon camera. 
 *    pos 0 (< 1333 ns):           no action
 *    pos 1 (> 1333 && < 1666ns):  camera shutter, 100ms pulse
 *    pos 2 (> 1666ns):            camera off, 1000ms pulse
 *
 * This program is made to be used with ATtiny45/85. It is programmed by a lazy
 * programmer, sending impulses is blocking. I couldn't be arsed to use 
 * interrupts.
 *
 * (c) 2013, Simon Wunderlin <swunderlin@gmail.com>
 */

// pin layout (attiny45)
#define PIN_CAM 1
#define PIN_PPM 2
#define PIN_LED 3

#define PULSE_TRIGGER   100
#define PULSE_SHUTDOWN 1000
#define MIN_GOOD_FRAMES  15
#define PPM_TIMEOUT   20000 

unsigned long duration, lastgood = 0;
uint8_t switch_pos, good_frames, last_switch_pos = 0;

void setup() {
	pinMode(PIN_CAM, OUTPUT);
	digitalWrite(PIN_CAM, LOW);
	delay(200); // make sure the pin is low
	
	pinMode(PIN_LED, OUTPUT);
	digitalWrite(PIN_LED, LOW);
	
	pinMode(PIN_PPM, INPUT);
}
/**
 * Toggle switch for N milliseconds
 *
 * This method is blocking (uses delay()).
 */
void send_pulse(int duration_ms) {
	digitalWrite(PIN_LED, HIGH);
	digitalWrite(PIN_CAM, HIGH);
	delay(duration_ms);
	digitalWrite(PIN_LED, LOW);
	digitalWrite(PIN_CAM, LOW);
}

void loop() {
  
	/**
	 * check ppm signal
	 * 
	 * the length of the pulse (in microseconds) or 0 if no pulse 
	 * started before the timeout (unsigned long)
	 */
	duration = pulseIn(PIN_PPM, HIGH, PPM_TIMEOUT); 
	if (duration == 0) { // no ppm signal
		duration = lastgood;
		good_frames = 0;
	} else {
		lastgood = duration;
		good_frames++;
	}
	
	// check if we subsequently got 10 good frames, otherwise skip actions.
	// this tries to deal with noisy radios
	if (good_frames < MIN_GOOD_FRAMES)
		return;
	
	// map ppm input values to switch states (0-2)
	//  0: no signal
	//  1: trigger camera
	//  2: shut down cam
	if (lastgood > 1666) switch_pos = 2;
	else if (lastgood > 1333) switch_pos = 1;
	else switch_pos = 0;
	
	// if the position has changed, decide what to do 
	if (switch_pos != last_switch_pos) {
		switch (switch_pos) {
			case 0: // no action / off
				digitalWrite(PIN_LED, LOW); // turn off the lights
				digitalWrite(PIN_CAM, LOW); // no signal or off
				break;
			
			case 1: // middle position, short pulse, trigger
				send_pulse(PULSE_TRIGGER);
				break;
			
			case 2: // max position, long pulse, shut down
				send_pulse(PULSE_SHUTDOWN);
				break;
		}
		
		last_switch_pos = switch_pos; // remeber last position
	}
	
	// reset good frames counter, try to capture MIN_GOOD_FRAMES good frames again
	good_frames = 0;
}

