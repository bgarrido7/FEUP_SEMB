
/*Motor B*/
 int motorPin4  = 9;  /* IN4 */
 int motorPin3  = 10;  /* IN3 */

/*Motor A*/
 int motorPin2  = 6; /* IN2 */
 int motorPin1  = 5;  /* IN1 */

void setup(){

    /*Set pins as outputs*/
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);

    /*Motor da esquerda frente*/
    analogWrite(motorPin1, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin2, 180); /*velocdade vai até 255*/
    analogWrite(motorPin4, 0);
    delay(1000);  

    /*Motor da esquerda tras*/
    analogWrite(motorPin4, 0);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin1, 180);
    delay(1000);  

    /*Motor da direita frente*/
    analogWrite(motorPin4, 180);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin1, 0);
    delay(1000);

    /*Motor da direita tras*/
    analogWrite(motorPin1, 0);
    analogWrite(motorPin3, 180);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin4, 0);
    delay(1000);
    
    /*Stop all motors*/
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 0);
}


void loop(){

}
