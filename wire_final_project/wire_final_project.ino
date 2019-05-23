#define MAXT 10

/*Motor B*/
int motorPin4  = 9;  /* IN4 - direita, frente*/
int motorPin3  = 10;  /* IN3 - direita, tras*/

/*Motor A*/
int motorPin2  = 6; /* IN2 - esquerda, frente*/
int motorPin1  = 5;  /* IN1 - esquerda, tras*/


//sensor proximidade
int echoPin = 11;
int trigPin = 3;

int xVal; //X values from joystick
int yVal; //Y values from joystick

byte tooClose=0;//para sensor proximidade

/* 3 Tasks:
 *     T1 -> period = 80, ler dados enviados do ESP
 *     T2 -> period = 100, mexer rodas do carro conforme input dado
 *     T3 -> period = 65, parar carro se sensor proximidade detetar obstáculo
 */

//*************** tasks code ******************
void T1(){ //ler recetor de dados

  xVal = analogRead(A0); //sets the X value
  yVal = analogRead(A2); //sets the Y value

 }

 void T2(){ //mexer rodas
  
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

 int T3(){//ler sensor proximidade

/***********ver melhor maneira de fazer isto sem usar delays************/
    int distance=0, duration=0; 

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
/***********************************************************************/

    if(distance<10 ||distance >40)
       tooClose=1;

    else 
      tooClose=0;
 }

//*************** Multi-tasking kernel ******************
typedef struct {
  int period;
  int offset;
  void (*func)(void);
  int exec;

} Sched_Task_t;

Sched_Task_t Tasks[MAXT];

// kernel initialization routine
int Sched_Init(void){

  // Initialise data structures

  byte x;
  for(x=0; x<MAXT; x++)
    Tasks[x].func = 0;

  //Configure interrupt that periodically calls Sched_Schedule()
    
}

// adding a task to the kernel
int Sched_AddT( void (*f)(void), int d, int p){

    byte x;
    for(x=0; x<MAXT; x++)
      if (!Tasks[x].func) {
        // finds the first free TCB
        Tasks[x].period = p;
        Tasks[x].offset = d;  //first activation is "d" after kernel start
        Tasks[x].exec = 0;
        Tasks[x].func = f;
        return x;
      }
    return -1;  // if no free TCB --> return error
}


// Kernel scheduler, just activates periodic tasks
// "offset" is always counting down, activate task when 0
// then reset to "period"
// --> 1st activation at "offset" and then on every "period"
void Sched_Schedule(void){

  byte x;
  for(x=0; x<20; x++) {
    if((Tasks[x].func)&&(Tasks[x].offset)){
      // for all existing tasks (func!=0) and not at 0, yet
      Tasks[x].offset--;  //decrement counter
      if(!Tasks[x].offset){
        /* offset = 0 --> Schedule Task --> set the "exec" flag/counter */
        // Tasks[x].exec++;  // accummulates activations if overrun
        Tasks[x].exec=1;    // if overrun, following activation is lost
        Tasks[x].offset = Tasks[x].period;  // reset counter
      }
    }
  }
}


// Kernel dispatcher, taskes highest priority ready task and runs it
// the distacher can only be called again upon task termination
//  (task is called within the dispatcher)
//  --> non-preemption    
void Sched_Dispatch(void){

  // index of currently running task (MAXT to force searching all TCBs initially)
  byte cur_task = MAXT;
  byte x;

  for(x=0; x<cur_task; x++) {
  // x searches from 0 (highest priority) up to x (current task)
    if((Tasks[x].func)&&(Tasks[x].exec)) {
      // if a TCB has a task (func!=0) and there is a pending activation
      Tasks[x].exec--;  // decrement (reset) "exec" flag/counter

      Tasks[x].func();  // Execute the task

      // Delete task if one-shot, i.e., only runs once (period=0 && offset!0)
      if(!Tasks[x].period)
        Tasks[x].func = 0;
      return;
    }
  }
}

void setup() {

    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT);

    pinMode(A0, INPUT); 
    pinMode(A2, INPUT);

    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);

    // run the kernel initialization routine
    Sched_Init();

  // add all periodic tasks  (code, offset, period) in ticks
  Sched_AddT(T1, 1, 80);
  Sched_AddT(T2, 1, 100);
  Sched_AddT(T3, 1, 65);


  //disable all interrupts
  noInterrupts(); 

  // timer 1 control registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
 
  // register for the frequency of timer 1  
  OCR1A = 625; // compare match register 16MHz/256/100Hz -- tick = 10ms
  //OCR1A = 6250; // compare match register 16MHz/256/10Hz
  //OCR1A = 31250; // compare match register 16MHz/256/2Hz
  //OCR1A = 31;    // compare match register 16MHz/256/2kHz
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= (1 << CS12); // 256 prescaler
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt

  interrupts(); // enable all interrupts 
}

ISR(TIMER1_COMPA_vect){
  Sched_Schedule();  // invokes the scheduler to update tasks activations
}

void loop() {

  Sched_Dispatch();  

/*
  //debug do joystick
    Serial.print("x = ");
    Serial.println(xVal);
    Serial.print("y = ");
    Serial.println(yVal);
*/
//debug do sensor ultrasonico
 //  Serial.println(distance);
     
    
} 
