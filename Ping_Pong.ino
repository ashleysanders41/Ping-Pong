import org.firmata.*; //importing standard firmata
import cc.arduino.*; // importing arduino library

import processing.serial.*;  // importing processing serial port           
import java.awt.Rectangle;  // importing java sketch            

Serial myPort;   // my serial port 


Rectangle leftPaddle, rightPaddle; // left and rigth paddles on screen       

int paddleHeight = 85; //height of paddle        
int paddleWidth = 10;  //width of paddle         
int ballSize = 10;  // size of ball   
int xDirection = 5;  //inital direction (horizontal) 
int yDirection = 5;  // initial direction (vertical)  
int xPos, yPos;  // initial horizonal and vertical positions of paddle
int rectSize = 25; // size of paddles
int leftScore = 0; // left side player score 
int rightScore = 0;  // right side player score   
int fontSize = 20;  // font size of score        
int topLeftx = 350; //initial position of score
int topLefty = 100; // initial position of score
int middleLeftx = 200;
int middleLefty = 250;
int bottomLeftx = 350;
int bottomLefty = 400;

void setup() {

 size(1000, 500); // size of screen     

 
 leftPaddle = new Rectangle(50, height/2, paddleWidth, paddleHeight); //initial value of left paddle
 rightPaddle = new Rectangle(width-50, height/2, paddleWidth, paddleHeight); //initial values of right paddle

 noStroke(); 
 fill(600); //color of ball 

 resetBall(); //return ball to middle once someone scores

// font size and text name
 PFont myFont = createFont(PFont.list()[2], fontSize);
 textFont(myFont);
   
 
 println(Serial.list());
 myPort = new Serial(this, Serial.list()[5], 9600); //my serial port connected with arduino
 
 myPort.bufferUntil('\n');
}

void draw() {
 
 background(300); //background color
 fill(250,0,0); //background fill
 //rect(405,0,10,500); //deleted line in the middle of screen
 fill(250,250,250); //background fill
 //rect(1000,25,0,0) //deleted line in middle of screen

 
 rect(leftPaddle.x, leftPaddle.y, leftPaddle.width, leftPaddle.height); //dimensions of left paddle
 rect(rightPaddle.x, rightPaddle.y, rightPaddle.width, rightPaddle.height); //dimensions of right paddle
 //rect(topLeftx, topLefty, 25, 25); // deleted rectangle
 //rect(middleLeftx, middleLefty, 25, 25); //deleted rectangle
 //rect(bottomLeftx, bottomLefty, 25, 25); //deleted rectangle
 
 animateBall(); //animate ball

 
 text(leftScore, fontSize, fontSize); //left score's score, font, and size
 text(rightScore, width-fontSize, fontSize); //right score's score, font, and size
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
