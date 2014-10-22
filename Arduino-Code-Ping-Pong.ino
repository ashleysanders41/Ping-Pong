/*
 Arduino Processing Pong
 Analog input 0 and 1 control the paddles

 Based on Esplora Pong by Tom Igoe

 This example is in the public domain.
 */

void setup() {
  Serial.begin(9600);     // initialize serial communication
}

void loop() {
  // read the inputs

  int leftPaddle = analogRead(A0);
  int rightPaddle = analogRead(A1);

  Serial.print(leftPaddle);                
  Serial.print(",");                   // add a comma
  Serial.println(rightPaddle);                
  delay(10);                           // delay before sending the next set
}