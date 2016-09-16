int inPin = 2;       
int outPin = 13;      

int state = HIGH;
int reading;
int previous = LOW;



long time = 0;
long debounce = 200;
int pinIRLED = 12;
int sleep = 7;
int dirPin = 9;
int stepperPin = 8;
int count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(inPin, INPUT_PULLUP);
  pinMode(outPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, HIGH);
  pinMode(stepperPin, OUTPUT);
  pinMode(pinIRLED, OUTPUT);

  
void pulseON(int pulseTime) {
  unsigned long endPulse = micros() + pulseTime;
  while( micros() < endPulse) {
    digitalWrite(pinIRLED, HIGH);
    delayMicroseconds(13);
    digitalWrite(pinIRLED, LOW);
    delayMicroseconds(13);
  }
}
void pulseOFF(unsigned long startDelay) {
  unsigned long endDelay = micros() + startDelay;
  while(micros() < endDelay);
}

void step() {
digitalWrite(stepperPin, HIGH);
delay(10);
digitalWrite(stepperPin, LOW);
delay(10);
}

void stop() {
digitalWrite(sleep, LOW);
}

void loop() {
  if(count <= 48 && state == HIGH)
  {
    digitalWrite(sleep, HIGH);
    step();
    delay(1100);
    takePicture();
    delay(800);
    count ++;
    Serial.println(count);
  }
  else
  {
    stop();
  }
   reading = digitalRead(inPin);

  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH){
      count = 0;
      state = LOW;}
    else
      state = HIGH;

    time = millis();    
  }

  digitalWrite(outPin, state);

  previous = reading;
}
