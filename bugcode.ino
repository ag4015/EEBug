#include <avr/sleep.h>

#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)

int rmotor = 1;

int lmotor = 0;

int rsensor = A2;

int lsensor = A3;

int mosfet = 2;

int normalspeed = 70; // defines motor speed when following the line

int light = 50; // defines the boundary between black and white surfaces

int time = 0;

boolean on_white, rmotor_white, lmotor_white;

boolean first_time = true;

int initial_threshold = 400; // threshold for sensors to switch on mosfet

void setup() {

pinMode(rmotor, OUTPUT);

pinMode(lmotor, OUTPUT);

pinMode(rsensor, INPUT);

pinMode(lsensor, INPUT);

pinMode(mosfet, OUTPUT);
digitalWrite(mosfet,LOW);

set_sleep_mode(SLEEP_MODE_PWR_DOWN);

}

void loop() {

// if it's the beginning

if (first_time) {

// if any of the phototransistors detects IR light

if (analogRead(A2) > initial_threshold ||

analogRead(A3) > initial_threshold) {

// turn on the mosfet

first_time = false;

}

}

// line-following

else if (!first_time) {

rmotor_white = false;

lmotor_white = false;

int rvalue = analogRead(rsensor); // Read analog voltage on pin 4 (A2)

int lvalue = analogRead(lsensor); // Read analog voltage on pin 3 (A3)



/* The ATTiny has a 10-bit A-to-D converter

Yet, the PWM has an 8-bit resolution

Thus, read values have to be converted from 0-1023 to 0-255

*/

rvalue = map (rvalue, 0, 1023, 0, 255);

lvalue = map (lvalue, 0, 1023, 0, 255);

if (rvalue < light) { // If on black...

analogWrite (rmotor, 0); // Stop motor

}

else if (rvalue >= light) { // If on white...

analogWrite (rmotor, normalspeed); // Start motor

rmotor_white = true;

}

if (lvalue < light) { // If on black...

analogWrite (lmotor, 0); // Stop motor

}

else if (lvalue >= light) { // If on white...

analogWrite (lmotor, normalspeed); // Start motor

lmotor_white = true;

}

// check if both phototransistors are on a white surface

on_white = rmotor_white && lmotor_white;

/* counter to check if it's time for spiral

It increases when both phototransistors are on a white surface

And goes back to 0 if any of them is on a black surface

After following the line, there will be only white surface and counter

increases

*/

if (on_white) {

time++;

}

else {

time = 0;

}

// start spiral

if (time > 2100) {

analogWrite (rmotor, 150); // both motors are ON

analogWrite (lmotor, 150);

delay(1200); // continue for 10 cm (varies with speed)

analogWrite (rmotor, 0); // make bug turn right

delay (2700);

analogWrite (rmotor, 150); // both motors are ON

// spirals of decreasing radius by decreasing left motor speed

analogWrite(lmotor, 110);

delay(10000);

analogWrite(lmotor, 100);

delay(9000);

analogWrite(lmotor, 90);

delay(8000);

analogWrite(lmotor, 80);

delay(7000);

analogWrite(rmotor, 0); // power OFF both motors

analogWrite(lmotor, 0);

enterSleep(); // go to sleep

}

}

delay (1);

}

void enterSleep(void)

{

adc_disable(); // ADC uses ~320uA

sleep_enable();

sleep_cpu();

while(1);

}
