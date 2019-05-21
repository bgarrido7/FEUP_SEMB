/*Motor B*/
int motorPin4  = 9;  /* IN4 - */
int motorPin3  = 10;  /* IN3 */

/*Motor A*/
int motorPin2  = 6; /* IN2 */
int motorPin1  = 5;  /* IN1 */

int xVal; //X values from joystick
int yVal; //Y values from joystick

int erro;

void setup() {

    Serial.begin(1200); //serial at 9600 baud

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

  //debug do joystick
    Serial.print("x = ");
    Serial.println(xVal);
    Serial.print("y = ");
    Serial.println(yVal);

      
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
