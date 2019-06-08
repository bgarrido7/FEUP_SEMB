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

unsigned long previousMillis = 0; //microsecond at which the pin was last writen
int trigState = LOW; //state of trigPin

//////////////////////receber dados///////////////////////
void moveForward(){
  
}

void moveBack(){
  
}

void moveRight(){
  
}

void moveLeft(){
  
}

////////////////////////mover carro////////////////////////
void motorParado(){
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
}


void motorFrente(){
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
}

void motorTras(){
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
}
void motorDireita(){
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
}

void motorEsquerda(){
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
}

//distancia a obstaculo
void  proximity(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    digitalWrite(trigPin,trigState);

    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;

    if(distance<10)
     tooClose=1;
    else
     tooClose=0;

}


void setup() {

    Serial.begin(1200); //serial at 9600 baud
    
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT);

    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
}

void loop() {

   proximity();

    if(tooClose && !moveBack()){
      motorParado();
    }

    else{
    //frente
        if(moveForward())
          motorFrente();
    
    //tras
        else if(moveBack())
        motorTras();
        
    //direita
        else if(moveRight())
          motorDireita();
    
    //esquerda
        else if(moveLeft())
          motorEsquerda();
        
    //parado
        else
          motorParado();
   }
}
