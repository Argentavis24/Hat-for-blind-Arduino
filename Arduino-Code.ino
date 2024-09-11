const int Trig = 2;
const int Echo = 3;
const int Buzzer = 8;
const int minThreshold = 10;
const int maxThreshold = 150;

void setup() {
  Serial.begin(9600);

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop() {

  long duration, distance;

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
  
  if (distance>minThreshold){
    /tone(Buzzer, 100, 200);     //format=tone(Buzzer, frequency, duration(in ms))
    delay(100);
    digitalWrite(Buzzer,LOW);
    delay(100);
  }
  if (distance<maxThreshold){
    tone(Buzzer, 100, 200);
    delay(100);
    tone(Buzzer, 100, 200);
    delay(100);
    
  }

  delay(250);
}
