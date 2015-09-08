char Name[ ] = "Gentry";
int potentiometer;
int incomingPotValue;
int fadeValue;
boolean button;
int RedLED;
int GreenLED;
int brightness;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  brightness = 0;
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  potentiometer = analogRead(A0);
  Serial.println(potentiometer);
  
}
