// Demo for test stepper motor x ,y z
// defines pins numbers

const int stepXPin = 2;
const int dirXPin  = 5;

// Pallet
const int stepYPin = 3;
const int dirYPin  = 6;

const int stepZPin = 4;
const int dirZPin  = 7;

const int enPin = 8;

const int homeSwitchPin = 7;

char receivedChar;
boolean newData = false;


void setup() {


   Serial.begin(9600);


  // Sets the two pins as Outputs

  pinMode(stepXPin,OUTPUT);
  pinMode(dirXPin,OUTPUT);

  pinMode(stepYPin,OUTPUT);
  pinMode(dirYPin,OUTPUT);

  pinMode(stepZPin,OUTPUT);
  pinMode(dirZPin,OUTPUT);
  

  pinMode(homeSwitchPin , INPUT);

  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);


  digitalWrite(dirYPin,LOW); 

  Serial.println("Test with Monitor Serial");
  Serial.println(" 1 = Pallet Slide LEFT");
  Serial.println(" 0 = Pallet Slide center");
  Serial.println(" 2 = Pallet Slide RIGHT");
  Serial.println(" 4 = Move Right");
  Serial.println(" 5 = Move Left");
  Serial.println(" 6 = Move UP");
  Serial.println(" 7 = Move Down");
}
int istep = 2500;
int state = 0;
int numDelay = 500;

void recvOneChar() {
 if (Serial.available() > 0) {
 receivedChar = Serial.read();
 newData = true;
 }
}

int xstep = 1000;
int zstep =  500;
void processNewData() {
  
 if (newData == true) {
 
  Serial.println(receivedChar);
  newData = false;

  if( (receivedChar == '1') && (state != 1) ){
       // left position
       Serial.println("Slide LEFT");
       state = 1;
       istep = 3000; // 3000

        digitalWrite(dirYPin,LOW);
        motorStep(istep);
    
  }
  else if( (receivedChar == '2') && (state != 2) ){
      // right position
       Serial.println("Slide RIGHT");
       state = 2;
       istep = 2500; // 2500

       digitalWrite(dirYPin,HIGH);
       motorStep(istep);
    
  }
  else if( receivedChar == '0' && (state != 0) ){
     // center position
     Serial.println("Center");
     
     digitalWrite(dirYPin,LOW);
     if( state == 1){
       digitalWrite(dirYPin,HIGH);
     }

     motorStep(istep);
     state = 0;

     
    
  }else if( receivedChar == '4' ){
      digitalWrite(dirXPin,LOW);
      motorXStep(xstep);
      delay(1000);
  }else if( receivedChar == '5' ){
      digitalWrite(dirXPin,HIGH);
      motorXStep(xstep);
      delay(1000);
  }else if( receivedChar == '6' ){
      digitalWrite(dirZPin,LOW);
      motorZStep(zstep);
      delay(1000);
  }else if( receivedChar == '7' ){
      digitalWrite(dirZPin,HIGH);
      motorZStep(zstep);
      delay(1000);
  }

 
 }

 
}

void loop() {

   
      recvOneChar();
      processNewData();
/*
       digitalWrite(dirPin,LOW);

        motorStep(istep);

        delay(2000);

        // center

        digitalWrite(dirPin,HIGH);

        motorStep(istep);

        delay(2000);

       
*/
    

 
}

void motorStep( int MAX){


   for(int x = 0; x < MAX; x++) {

        digitalWrite(stepYPin,HIGH);

        delayMicroseconds(numDelay);

        digitalWrite(stepYPin,LOW);

        delayMicroseconds(numDelay);

      }

}

void motorXStep( int MAX){


   for(int x = 0; x < MAX; x++) {

        digitalWrite(stepXPin,HIGH);

        delayMicroseconds(500);

        digitalWrite(stepXPin,LOW);

        delayMicroseconds(500);

      }

}
void motorZStep( int MAX){


   for(int x = 0; x < MAX; x++) {

        digitalWrite(stepZPin,HIGH);

        delayMicroseconds(500);

        digitalWrite(stepZPin,LOW);

        delayMicroseconds(500);

      }

}
