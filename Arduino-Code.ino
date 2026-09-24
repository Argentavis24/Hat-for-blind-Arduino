const int Trig = 2;
const int Echo = 3;
const int Buzzer = 8;
const int MIN_DISTANCE = 5;
const int MAX_DISTANCE = 100;



void setup() 
{
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop() 
{
  long duration;
  int distance;

  digitalWrite(Trig, LOW);
  delayMicroseconds(2);

  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(Trig, LOW);

  duration = pulseIn(Echo, HIGH);

  distance = duration * 0.017;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance >= MIN_DISTANCE && distance <= MAX_DISTANCE) 
  {

    int beepDelay = map(distance, MIN_DISTANCE, MAX_DISTANCE, 50, 600);

    digitalWrite(Buzzer, HIGH);
    delay(50);

    digitalWrite(Buzzer, LOW);
    delay(beepDelay);

  }
  else 
  {
    digitalWrite(Buzzer, LOW);
    delay(100);
  }
}
