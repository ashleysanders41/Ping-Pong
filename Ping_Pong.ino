import org.firmata.*;
import cc.arduino.*;

import processing.serial.*;              
import java.awt.Rectangle;              

Serial myPort;    


Rectangle leftPaddle, rightPaddle;        

int paddleHeight = 85;            
int paddleWidth = 10;             
int ballSize = 10;     
int xDirection = 5;   
int yDirection = 5;    
int xPos, yPos;  
int rectSize = 25;
int leftScore = 0;     
int rightScore = 0;     
int fontSize = 20;          
int topLeftx = 350;
int topLefty = 100;
int middleLeftx = 200;
int middleLefty = 250;
int bottomLeftx = 350;
int bottomLefty = 400;

void setup() {

 size(1000, 500);      

 
 leftPaddle = new Rectangle(50, height/2, paddleWidth, paddleHeight);
 rightPaddle = new Rectangle(width-50, height/2, paddleWidth, paddleHeight);

 noStroke(); 
 fill(600);  

 resetBall();

 PFont myFont = createFont(PFont.list()[2], fontSize);
 textFont(myFont);
   
 
 println(Serial.list());
 myPort = new Serial(this, Serial.list()[5], 9600);
 
 myPort.bufferUntil('\n');
}

void draw() {
 
 background(300);
 fill(250,0,0);
 //rect(405,0,10,500);
 fill(250,250,250);
 //rect(1000,25,0,0)

 
 rect(leftPaddle.x, leftPaddle.y, leftPaddle.width, leftPaddle.height);
 rect(rightPaddle.x, rightPaddle.y, rightPaddle.width, rightPaddle.height);
 //rect(topLeftx, topLefty, 25, 25);
 //rect(middleLeftx, middleLefty, 25, 25);
 //rect(bottomLeftx, bottomLefty, 25, 25);
 
 animateBall();

 
 text(leftScore, fontSize, fontSize);
 text(rightScore, width-fontSize, fontSize);
}


void serialEvent(Serial thisPort) {

 
 String inputString = thisPort.readStringUntil('\n');

 if (inputString != null)
 {
  
   inputString = trim(inputString);

   
   int sensors[] = int(split(inputString, ','));
  // xDirection++;
  // yDirection++;
   
   if (sensors.length == 2) {
     leftPaddle.y = int(map(sensors[0], 0, 425, 0, height - leftPaddle.height));
     rightPaddle.y = int(map(sensors[1], 0,425 , 0, height - rightPaddle.height));
   }
 }
}

void animateBall() {
 if (leftPaddle.contains(xPos, yPos) ||    
 rightPaddle.contains(xPos, yPos)) {       
   xDirection = -xDirection;   
                
 }

 
 if (xPos < 0) 
 {     
   rightScore++;     
   resetBall();   
 }  
 if (xPos > width) 
 {
   leftScore++;
   resetBall();
 }
 
 if ((yPos <= 0) || (yPos >=height)) {
   yDirection = -yDirection;
 }
 

 
 xPos = xPos + xDirection;
 yPos = yPos + yDirection;

 
 ellipse(xPos, yPos, ballSize, ballSize);
}

void resetBall()
{
 
 xPos = width/2;
 yPos = height/2;
}