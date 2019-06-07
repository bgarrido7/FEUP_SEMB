/*Motor B*/
int motorPin4  = 9;  /* IN4 - direita, frente*/
int motorPin3  = 10;  /* IN3 - direita, tras*/

/*Motor A*/
#define motorPin2 6 /* IN2 - esquerda, frente*/
#define motorPin1 5  /* IN1 - esquerda, tras*/

#define enA 2
#define enB 3

int velA = 0; //velocidade dos mototres
int velB = 0; //controlado por PWM

/*sensor proximidade*/
#define echoPin 11
#define trigPin 3
int distance=0, duration=0;

bit tooClose=0;

bit moveForward = 0;
bit moveBack = 0;
bit moveRight = 0;
bit moveLeft = 0;

unsigned long previousMillis = 0; //microsecond at which the pin was last writen
int trigState = LOW; //state of trigPin

//////////////////////receber dados///////////////////////
if(){
    byte moveForward = 1;
    byte moveBack = 0;
    byte moveRight = 0;
    byte moveLeft = 0;

    velA = ;
    velB = ;
}

else if(){    
    byte moveBack = 1;
    byte moveForward = 0;
    byte moveRight = 0;
    byte moveLeft = 0;

    velA = ;
    velB = ;
}

else if(){
    byte moveRight = 1;
    byte moveForward = 0;
    byte moveBack = 0;
    byte moveLeft = 0;

    velA = ;
    velB = ;
}

else if(){
    byte moveLeft = 1;
    byte moveForward = 0;
    byte moveBack = 0;
    byte moveRight = 0;

    velA = ;
    velB = ;
}

else(){
    byte moveLeft = 0;
    byte moveForward = 0;
    byte moveBack = 0;
    byte moveRight = 0;
}

////////////////////////mover carro////////////////////////
void motorParado(){
    analogWrite(enA, 0);
    analogWrite(enB, 0);

    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
}


void motorFrente(){
    analogWrite(enA, velA);
    analogWrite(enB, velB);

    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
}

void motorTras(){
    analogWrite(enA, velA);
    analogWrite(enB, velB);

    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
}
void motorDireita(){
    analogWrite(enA, velA);
    analogWrite(enB, velB);

    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
}

void motorEsquerda(){
    analogWrite(enA, velA);
    analogWrite(enB, velB);

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

    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
}

void loop() {

   proximity();

    //pode mover para tras se tiver obstaculo à frente
    if(tooClose && !moveBack) 
      motorParado();
    
    else{

    //frente
        if(moveForward)
          motorFrente();
    
    //tras
        else if(moveBack)
        motorTras();
        
    //direita
        else if(moveRight)
          motorDireita();
    
    //esquerda
        else if(moveLeft)
          motorEsquerda();
        
    //parado
        else
            motorParado();
   }
}
