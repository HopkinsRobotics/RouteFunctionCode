//Welcome

#define frontecho 14
#define fronttrig 15
#define backecho 20
#define backtrig 21
#define leftbackecho 16
#define leftbacktrig 17
#define rightfrontecho 7
#define rightfronttrig 6
#define leftfrontecho 18
#define leftfronttrig 19
#define rightbackecho 4
#define rightbacktrig 3 

#define rightmotor 11
#define leftmotor 12

#define firePin A0

#define fanPin 9

#define led 2

#include <Servo.h>

float threshold=400;
float light=10000;

Servo Han;


//Operation 0 is less than, 1 is greater than

byte startingwallthreshold = 5;
//SPEEDS GIVEN FOR RIGHT MOTOR
int fsf =140; 
int hsf =160; 
int qsf =178;
int ssf =191; 
int qsb =203;
int hsb =221; 
int fsb =243; 

int readfront =1;
int readback =1;
int readfright =1;
int readbright =1;
int readfleft =1;
int readbleft =1;

int flamefind; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode(frontecho, INPUT);
  pinMode(fronttrig, OUTPUT);
  pinMode(backecho, INPUT);
  pinMode(backtrig, OUTPUT);
  pinMode(leftfrontecho, INPUT);
  pinMode(leftfronttrig, OUTPUT);
  pinMode(leftbackecho, INPUT);
  pinMode(leftbacktrig, OUTPUT);
  pinMode(rightfrontecho, INPUT);
  pinMode(rightfronttrig, OUTPUT);
  pinMode(rightbackecho, INPUT);
  pinMode(rightbacktrig, OUTPUT);
  pinMode(firePin, INPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(rightmotor, OUTPUT);
  pinMode(leftmotor, INPUT);
  Han.attach(10);
}

void loop() {
  //ultradiagnostic();
  
  //delay(10000);
  //driveuuback(0,40);
  //alignright();
  //driveuubright(0,12);
  //rwrt(8);
  //driveuufront(1,7);
  //rightpivotback(7);
  delay(5000);
  lookForFLame();
  //rwrt(8);
  //driveuuback(0,25);
  //delay(1000);
//soundstart();
//turnuntilultrasonic(1,3,startingwallthreshold);
//align(0);
}

void alignright()
{
    readultra(2);
    delay(25);
    readultra(3);
    delay(25);
    while (readfright>=readbright)
      {
        readultra(2);
        delay(25);
        readultra(3);
        analogWrite(leftmotor,hsf);
      }
      STOP();
    while (readfright<readbright)
      {
        readultra(2);
        delay(25);
        readultra(3);
        analogWrite(rightmotor,hsb);
      }
      STOP();
}
void alignleft()
{
    readultra(5);
    delay(25);
    readultra(6);
    delay(25);
    while (readfleft>=readbleft)
      {
        readultra(5);
        delay(25);
        readultra(6);
        analogWrite(rightmotor,hsb);
      }
      STOP();
    while (readfleft<readbleft)
      {
        readultra(5);
        delay(25);
        readultra(6);
        analogWrite(leftmotor,hsf);
      }
      STOP();
}
    

void drivetime(int timer)
{
  analogWrite(rightmotor,fsb);
  analogWrite(leftmotor,fsf);
  delay(timer);
  STOP();
}
//0 == away, 1 == approach
void driveuuback(int operation, int value)
{
  readultra(4);
  switch (operation)
  {
    case (0):
    while (readback<value)
    {
      analogWrite(rightmotor,hsb);
      analogWrite(leftmotor,hsf);
      readultra(4);
    }
    STOP();
    break;
    case (1):
    while (readback>value)
    {
      analogWrite(rightmotor,hsb);
      analogWrite(leftmotor,hsf);
      readultra(4);
    }
    STOP();
  }
}
void driveuufront(int operation, int value)
{
  readultra(1);
  switch (operation)
  {
    case (0):
    while (readfront<value)
    {
      analogWrite(rightmotor,hsb);
      analogWrite(leftmotor,hsf);
      readultra(1);
    }
    STOP();
    break;
    case (1):
    while (readfront>value)
    {
      analogWrite(rightmotor,hsb);
      analogWrite(leftmotor,hsf);
      readultra(1);
      delay(10);
    }
    STOP();
  }
}

void driveuubright(int operation, int value)
{
  readultra(3);
  switch (operation)
  {
    case (0):
    while (readbright<value)
    {
      analogWrite(rightmotor,hsb);
      analogWrite(leftmotor,hsf);
      readultra(3);
    }
    STOP();
    break;
    case (1):
    while (readbright>value)
    {
      analogWrite(rightmotor,hsb);
      analogWrite(leftmotor,hsf);
      readultra(3);
    }
    STOP();
  }
}

void rwrt(int value) 
{
  readultra(2);
  while(readfright>value)
  {
  readultra(2);
  analogWrite(rightmotor,qsb);  
  analogWrite(leftmotor,hsf);
  }
  STOP();
}

void rightpivotback (int value)
{
  readultra(4);
  while (readback>value)
  {
    readultra(4);
    analogWrite(rightmotor,hsf);
    analogWrite(leftmotor,hsf);
  }
  STOP();
  alignleft();
}

void flameputout(){}
void soundstart(){}
void orient()
{
  while(readfleft>startingwallthreshold)
  {
    analogWrite(leftmotor,hsb);
  }
}
void STOP()
{
  analogWrite(rightmotor,ssf);
  analogWrite(leftmotor,ssf);
}
void ultradiagnostic()
{
  Serial.println("BEGIN");
  readultra(1);
  Serial.println(readfront);
  delay(1000);
  readultra(2);
  Serial.println(readfright);
  delay(1000);
  readultra(3);
  Serial.println(readbright);
  delay(1000);
  readultra(4);
  Serial.println(readback);
  delay(1000);
  readultra(5);
  Serial.println(readbleft);
  delay(1000);
  readultra(6);
  Serial.println(readfleft);
  delay(1000);
}
void readultra(int ultranumber) {
  long duration, distance;
  switch (ultranumber)
  {
  case (1):
  digitalWrite(fronttrig, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(fronttrig, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(fronttrig, LOW);
  duration = pulseIn(frontecho, HIGH);
  distance = (duration/2) / 29.1;
  readfront = distance;
  break;
  case (2):
  digitalWrite(rightfronttrig, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(rightfronttrig, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(rightfronttrig, LOW);
  duration = pulseIn(rightfrontecho, HIGH);
  distance = (duration/2) / 29.1;
  readfright = distance;
  break;
  case (3):
  digitalWrite(rightbacktrig, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(rightbacktrig, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(rightbacktrig, LOW);
  duration = pulseIn(rightbackecho, HIGH);
  distance = (duration/2) / 29.1;
  readbright = distance;
  break;
  case (4):
  digitalWrite(backtrig, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(backtrig, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(backtrig, LOW);
  duration = pulseIn(backecho, HIGH);
  distance = (duration/2) / 29.1;
  readback = distance;
  break;
  case (5):
  digitalWrite(leftbacktrig, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(leftbacktrig, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(leftbacktrig, LOW);
  duration = pulseIn(leftbackecho, HIGH);
  distance = (duration/2) / 29.1;
  readbleft = distance;
  break;
  case (6):
  digitalWrite(leftfronttrig, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(leftfronttrig, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(leftfronttrig, LOW);
  duration = pulseIn(leftfrontecho, HIGH);
  distance = (duration/2) / 29.1;
  readfleft = distance;
  break; 
  }
}

void lookForFLame()
{
  float reads[6];
  float lowestRead;
  int lowestReading;
  delay(3000);
  lowestRead = 100000000;
  for(int i = 40 ; i < 100 ; i+=10)
  {
    int p = (i-40)/10.0;
    Han.write(i);
    delay(3000);
    float pie = takeFireRead();
    reads[p] = pie;
    Serial.println(reads[p]);
    if(reads[p] < lowestRead)
    {
      lowestRead = reads[p];
      lowestReading = p;
    }
  }
  if( lowestRead < threshold )
  {
    putItOut();
    return;
  }
  if( lowestRead < light)
  {
  delay(3000);
  Serial.println("Got here");
  Serial.println(lowestRead);
  Han.write(65);
  if((lowestReading*10 + 40) >65)
  {
  analogWrite(leftmotor, hsf);
  while(takeFireRead() > lowestRead+ 100)
  {
    delayMicroseconds(1);
  }
  analogWrite(leftmotor, 191);
  approach();
  }
  else
  {
  analogWrite(rightmotor, hsb);
  while(takeFireRead() > lowestRead + 100)
  {
    delayMicroseconds(1);
  }
  analogWrite(rightmotor, ssf);
  approach();
  }
  }
  
  if(lowestRead > light)
  {
    return;
  }
  lookForFLame();
}

void putItOut()
{
  digitalWrite(9, HIGH);
  delay(2000);
  return;
}
//Later on we may want to try a continuous search, but for
//now navigation will relinquish control to searchForFire()

//returns whether a fire was found
void approach()
{
  //full forward
  //While loop until lower than threshold
  //putitout
  //Return
}
bool fireFight()
{
  
  //Take reading
  delay(500);
}

float takeFireRead()
{
  float reading = analogRead(A0);
  return reading;
}











