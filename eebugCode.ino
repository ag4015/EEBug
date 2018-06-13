int rmotor = 1;

int lmotor = 0;
int rsensor = A2;
int lsensor = A3;
int buzzer = 2;
int normalspeed = 60; // defines motor speed when following the line
int light = 700; // defines the boundary between black and white surfaces
int counter = 0;

void setup() {
pinMode(rmotor, OUTPUT);
pinMode(lmotor, OUTPUT);
pinMode(rsensor, INPUT);
pinMode(lsensor, INPUT);
pinMode(buzzer, OUTPUT);
}

void loop() {
int rvalue = analogRead(rsensor); // Read analog voltage on pin 4 (A2)
int lvalue = analogRead(lsensor); // Read analog voltage on pin 3 (A3)
analogWrite(buzzer, 127);
/* The ATTiny has a 10-bit A-to-D converter

Yet, the PWM has an 8-bit resolution

Thus, read values have to be converted from 0-1023 to 0-255

*/


/*if (rvalue < light) { // If on black...

analogWrite (rmotor, 0); // Stop motor

}else if (rvalue >= light) { // If on white...

analogWrite (rmotor, normalspeed); // Start motor

rmotor_white = true;

}

if (lvalue < light) { // If on black...

analogWrite (lmotor, 0); // Stop motor

}else if (lvalue >= light) { // If on white...

analogWrite (lmotor, normalspeed); // Start motor

lmotor_white = true;

if(rmotor_white&&lmotor_white == false){
  analogWrite (rmotor, normalspeed);
  analogWrite (lmotor, normalspeed);
}
*/

if(rvalue < lvalue){
  analogWrite(rmotor, 0);
  analogWrite(lmotor, normalspeed);
}else if(rvalue > lvalue){
  analogWrite(lmotor, 0);
  analogWrite(rmotor, normalspeed);
}else if(rvalue = lvalue){
  counter++;
}
delay(50);
analogWrite (rmotor, 0);
analogWrite (lmotor, 0);
delay(25);

if((rvalue > light) && (lvalue > light)){
  counter++;
}else{
  counter = 0;
}

if(counter > 15){
  analogWrite(rmotor, normalspeed);
  analogWrite(lmotor, normalspeed);
  delay(2000);
  analogWrite(lmotor, 0);
  delay(5000);
}
}
 



