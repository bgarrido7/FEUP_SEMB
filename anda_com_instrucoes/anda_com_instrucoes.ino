/*
 * IN4-D8
 * IN3-D7
 * IN2-D6
 * IN1-D5
 * 
 * LED-D1
 * TRIGGER-D3
 * ECHO-D2
 */

/*Motor B*/
int motorPin4 = D2;  /* IN4 - direita, frente*/ //D8 - GPIO15 - 16
int motorPin3 = D7; /* IN3 - direita, tras*/ //D7 - GPIO13 - 7

/*Motor A*/
int motorPin2 = D6; /* IN2 - esquerda, frente*/ //D6 - GPIO12 - 6 
int motorPin1 = D5; /* IN1 - esquerda, tras*/ //D5 - GPIO14 - 5

/*Proximity Sensor*/
int led = D3; //D4 - GPIO2 - 17
int trigPin = D8; //D2 GPIO4 - 19
int echoPin = D4; //D3 - GPIO0 -18

int duration=0;
int distance=0;


int checkObstacle(){
   // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
  delay(100);
  
  return distance;
}


void setup(){
  
  pinMode (led, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

  /*Set pins as outputs*/
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

}

void loop(){

  digitalWrite(led, LOW);
  
  if(checkObstacle() < 10){
      digitalWrite(led, HIGH);

        //Stop all motors
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);

      delay(500);
  }

  else{
  //CARRO ANDA PARA A FRENTE
  //Motor da esquerda frente
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, HIGH);
  //digitalWrite(motorPin4, LOW);
  //delay(1000);

  //Motor da direita frente
  digitalWrite(motorPin4, 255);
  //digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin1, LOW);
  delay(1000);

  //CARRO ANDA PARA TRAS
  //Motor da esquerda tras
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin2, LOW);
  //digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin1, HIGH);
  //delay(1000);

  //Motor da direita tras
  //digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin4, LOW);
  delay(1000);

  //RODAR SÓ NUMA DIREÇAO
  //Motor da direita frente
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin1, LOW);
  delay(1000);

  //Motor da direita tras
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin4, LOW);
  delay(1000);

  //Stop all motors
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(1000);

  }
}
