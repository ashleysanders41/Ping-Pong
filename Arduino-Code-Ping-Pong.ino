/*
 Arduino Processing Pong
 Analog input 0 and 1 control the paddles

 Based on Esplora Pong by Tom Igoe

 This example is in the public domain.
 */

void setup() {
  Serial.begin(9600);     // my serial port
}

void loop() {
  // read the inputs

  int leftPaddle = analogRead(A0); //left paddle is connected to Analog 0
  int rightPaddle = analogRead(A1); // right paddle is connected to Analog 1

  Serial.print(leftPaddle);    //show left paddle            
  Serial.print(",");                   
  Serial.println(rightPaddle); //show right paddle               
  delay(10);                   // delay before startingt the next game
}
