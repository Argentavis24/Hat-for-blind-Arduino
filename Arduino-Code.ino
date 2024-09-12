const int Trig = 2;
const int Echo = 3;
const int Buzzer = 8;
const int minThreshold = 15;
const int maxThreshold = 25;

void setup() {
  Serial.begin(9600);

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop() {

  long duration;
  int distance;

  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  duration = pulseIn(Echo, HIGH);

  distance = (duration*0.017);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance<maxThreshold)and(distance>minThreshold){
    digitalWrite(Buzzer, HIGH);
    delay(100);
    digitalWrite(Buzzer, LOW);
    delay(100);

  }
  else  {
    digitalWrite(Buzzer, HIGH);
    delay(250);
    digitalWrite(Buzzer, LOW);
    delay(250);

  }
  delay(250);
}
