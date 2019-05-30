// defines motor pins
#define motorPin4 9  /* IN4 - direita, frente*/
#define motorPin3 10 /* IN3 - direita, tras*/

#define motorPin2 6 /* IN2 - esquerda, frente*/
#define motorPin1 5 /* IN1 - esquerda, tras*/

#define trigPin D5
#define echoPin D6
#define led D7

// defines variables
long duration;
int distance;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  Serial.begin(9600);       // Starts the serial communication
  
}

void loop()
{
  digitalWrite(led, LOW);

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
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 10)
    digitalWrite(led, HIGH);
  delay(100);
}
