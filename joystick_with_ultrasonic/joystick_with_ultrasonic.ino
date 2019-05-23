/*Motor B*/
int motorPin4  = 9;  /* IN4 - direita, frente*/
int motorPin3  = 10;  /* IN3 - direita, tras*/

/*Motor A*/
int motorPin2  = 6; /* IN2 - esquerda, frente*/
int motorPin1  = 5;  /* IN1 - esquerda, tras*/

/*sensor proximidade*/
int echoPin = 11;
int trigPin = 3;
int distance=0, duration=0;

int xVal; //X values from joystick
int yVal; //Y values from joystick

void setup() {

    Serial.begin(1200); //serial at 9600 baud
    
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT);

    pinMode(A0, INPUT); 
    pinMode(A2, INPUT);

    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
}

void loop() {

    xVal = analogRead(A0); //sets the X value
    yVal = analogRead(A2); //sets the Y value
    
    
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

/*
  //debug do joystick
    Serial.print("x = ");
    Serial.println(xVal);
    Serial.print("y = ");
    Serial.println(yVal);
*/
   //debug do sensor ultrasonico
   Serial.println(distance);

    if(distance<10 && xVal==0){
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 0);
      analogWrite(motorPin4, 0);
    }

    else{
    //frente
        if(xVal==0){
            analogWrite(motorPin1, 0);
            analogWrite(motorPin3, 0);
            analogWrite(motorPin2, 255);    
            analogWrite(motorPin4, 255);
        }
    
    //tras
        else if(xVal>=1010){
            analogWrite(motorPin4, 0);
            analogWrite(motorPin2, 0);
            analogWrite(motorPin1, 255);
            analogWrite(motorPin3, 255);   
        }
    
    //direita
        else if(yVal>=1010){
            analogWrite(motorPin4, 255);
            analogWrite(motorPin2, 0);
            analogWrite(motorPin3, 0);
            analogWrite(motorPin1, 0);
        }
    
    //esquerda
        else if(yVal==0){
            analogWrite(motorPin4, 0);
            analogWrite(motorPin2, 255);
            analogWrite(motorPin3, 0);
            analogWrite(motorPin1, 0);
        }
        
    //parado
        else{
            analogWrite(motorPin1, 0);
            analogWrite(motorPin2, 0);
            analogWrite(motorPin3, 0);
            analogWrite(motorPin4, 0);
        }
   }
}
