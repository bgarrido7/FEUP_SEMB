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

byte tooClose=0;

int xVal; //X values from joystick
int yVal; //Y values from joystick

unsigned long previousMillis = 0; //microsecond at which the pin was last writen
int trigState = LOW; //state of trigPin

int proximity(){//distancia a obstaculo
  
  /*alternativa a usar delay() mas nao funciona muito bem*/
/*  unsigned long currentMillis = millis(); 
     if (currentMillis-previousMillis >= 1) { 
        previousMillis = currentMillis;
        
        if (trigState == LOW)
          (trigState = HIGH);
        
        else 
          (trigState = LOW);      
    }
  */  
     
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    digitalWrite(trigPin,trigState);


    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;

    if(distance<10 ||distance >40)
      tooClose=1;
     else
      tooClose=0;

    return distance;
  
}


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

//    proximity();
    
    //debug do joystick
    Serial.print("x = ");
    Serial.print(xVal);
    Serial.print("\ty = ");
    Serial.println(yVal);

   //debug do sensor ultrasonico
   Serial.println(proximity());

    if(tooClose && xVal<12){
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 0);
      analogWrite(motorPin4, 0);
    }

    else{
    //frente
        if(xVal<12){
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
        else if(yVal<12){
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
