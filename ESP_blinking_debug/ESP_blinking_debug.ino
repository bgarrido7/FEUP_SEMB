// defines pins numbers

const int led0 = D10;
//const int led1 = D1;
//const int led2 = D2;
//const int led3 = D3;
//const int led4 = D4;
//const int led5 = D5;
//const int led6 = D6;
//const int led7 = D7;
//const int led8 = D8;



void setup()
{
 pinMode(led0, OUTPUT);
//  pinMode(led1, OUTPUT);
// pinMode(led2, OUTPUT);
// pinMode(led3, OUTPUT);
// pinMode(led4, OUTPUT);
// pinMode(led5, OUTPUT);
// pinMode(led6, OUTPUT);
// pinMode(led7, OUTPUT);
// pinMode(led8, OUTPUT);

  
}

void loop()
{
  digitalWrite(led0, LOW);
//    digitalWrite(led1, LOW);
//  digitalWrite(led2, LOW);
//  digitalWrite(led3, LOW);
//  digitalWrite(led4, LOW);
//  digitalWrite(led5, LOW);
//  digitalWrite(led6, LOW);
//  digitalWrite(led7, LOW);
//  digitalWrite(led8, LOW);

  
  delay(500);
  
    digitalWrite(led0, HIGH);
//    digitalWrite(led1, HIGH);
//    digitalWrite(led2, HIGH);
//  digitalWrite(led3, HIGH);
//  digitalWrite(led4, HIGH);
//  digitalWrite(led5, HIGH);
//  digitalWrite(led6, HIGH);
//  digitalWrite(led7, HIGH);
//    digitalWrite(led8, HIGH);
    
  delay(500);
}
