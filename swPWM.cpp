//A software PWM library by Dustin Hebecker (dustin-hebecker@gmx.de)
//Based on a idea by james@baldengineer.com
// PINCOUNT needs to be defined like:
//#define PINCOUNT 3

#include "swPWM.h" 

// timing variables for software PWM
unsigned long currentMicros = micros();
unsigned long previousMicros = 0;
// this is the frequency of the sw PWM
unsigned long microInterval = MICRO_INTERVAL;
 
// the maximum value for the PWM (PWM==pwmMax=>Always ON)
const uint8_t pwmMax = PWM_MAX;
 
//Please define PINCOUNT in your main representing the total number pins you want to use with swPWM
//it needs to be the same length as the array pins passed to setupSwPWM
const uint8_t pinCount = PINCOUNT

// typedef for properties of each sw pwm pin
typedef struct pwmPins {
  	uint8_t pin;
  	uint8_t pwmValue;
  	bool pinState;
  	uint8_t pwmTickCount;
} pwmPin;
 
// create the sw pwm pins
// these can be any I/O pin
// that can be set to output!
//const int pinCount = 8;
//const byte pins[pinCount] = {2,3,5,6,9,10,11,12};
 
pwmPin myPWMpins[PINCOUNT];
 
// function to "setup" the sw pwm pin states
void setupSwPWM(const byte* pins, uint8_t defaultValue = 0) {
  	for (uint8_t index=0; index < pinCount; index++) {
    	myPWMpins[index].pin = pins[index];
    	//initialise the pins
    	if(defaultValue <= pwmMax)
		    myPWMpins[index].pwmValue = defaultValue;
 		else
		    myPWMpins[index].pwmValue = pwmMax;
 		if(defaultValue==0)
			myPWMpins[index].pinState = OFF;
		else
			myPWMpins[index].pinState = ON;
    	myPWMpins[index].pwmTickCount = 0;
    	pinMode(pins[index], OUTPUT);
  	}
}
 
 
void swPWMupdate() {
  currentMicros = micros();
  // check to see if we need to increment our PWM counters yet
  	uint8_t time_diff = currentMicros - previousMicros;
    if (time_diff >= microInterval) {
    	uint8_t stepps = time_diff/microInterval;
    	// Igo though al pins individually
    	for (uint8_t index=0; index < pinCount; index++) {
    		// each pin has its own tickCounter
    	  	myPWMpins[index].pwmTickCount+=stepps;
    		// determine if we're counting on or off time
    	  	if (myPWMpins[index].pinState == ON) {
    	    	// see if we hit the desired on percentage
    	    	// addjust pwmMax to increase/decrease resolution (keep in mind it is inversely proportional to the frequency)
    	    	if (myPWMpins[index].pwmTickCount >= myPWMpins[index].pwmValue) {
    	      		myPWMpins[index].pinState = OFF;
    	    	}
    	  	} else {
    	    	if (myPWMpins[index].pwmTickCount >= pwmMax) {
    	    		if(myPWMpins[index].pwmValue==0){}
    	    			myPWMpins[index].pinState = OFF;
    	    		}else{
    	      			myPWMpins[index].pinState = ON;
    	      			myPWMpins[index].pwmTickCount = 0;
    	      		}
    	    	}
    	  	}
    	  	// This part costs a lot of time, if you want to run a lot of pins make sure you don't need to run many other tasks
    	  	digitalWrite(myPWMpins[index].pin, myPWMpins[index].pinState);
    	}
    	previousMicros = currentMicros;
  	}
}
 
void swAnalogWrite(uint8_t pin, uint8_t value){
	//ignore invalid values
	if(value > pwmMax ) return;
	//set the new Pulse width, will be activated in the next cycle/call of swPWMupdate
	for (uint8_t index=0; index < pinCount; index++) {
		if(myPWMpins[index].pin == pin{
      		myPWMpins[index].pwmValue = value;
      }
}


