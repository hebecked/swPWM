//A software PWM library by Dustin hebecker (dustin-hebecker@gmx.de)
//Based on a idea by james@baldengineer.com
// please define PINCOUNT according to the amount of PWM pins you pass to setupSwPWM

// macros for LED state
#define ON true
#define OFF false

// this is the frequency of the sw PWM
// sampling frequency = 1/(2 * microInterval)
#define MICRO_INTERVAL 250
 
// the maximum value for the PWM (PWM==PWM_MAX=>Always ON)
#define PWM_MAX 128
 
// function to "setup" the sw pwm pins, ideally use in setup(), pins musst be an array of all sw PWM pins pin number of length PINCOUNT. PINCOUNT needs to be initialised in the main program  
void setupSwPWM(const byte* pins, uint8_t defaultValue = 0);
 

//Call this function periodically to ensure proper functionality e.g. in loop() every 1E-4 seconds
void swPWMupdate();
 

//Change a pins pulse width/on time
void swAnalogWrite(uint8_t pin, uint8_t value);


/*Small programm sample:

#include <swPWM.h> 
#define PINCOUNT 3

const byte pins[PINCOUNT] = {2,3,11};
unit8_t count = 0;

void setup() {
  setupSwPWM(pins, 64);
}
   
void loop() {
  // this is the magic for sw pwm
  // need to call this anytime you
  // have a long operation
  swPWMupdate();
  //Some sample to bring in some change
  if(micros()%100000==0){
    if(count>128){
      count=0;
    }
    swAnalogWrite(2, count);
    count++;
  }
}

*/

