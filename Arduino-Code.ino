// ARDUINO BLIND ASSISTIVE HAT : VER-3
// Datathon'26 - SRM

// Define all pins
const int Trig = 2;
const int Echo = 3;
const int Buzzer = 8;

// All distance is in cms
const int safe_dist = 100;
const int warn_dist = 60;
const int danger_dist = 30;
const int crit_dist = 15;
const int min_dist = 5;

// Setup

void setup() {

  Serial.begin(9600);

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Buzzer, OUTPUT);

  // Startup init
  tone(Buzzer, 2000);
  delay(150);                                // In milliseconds
  noTone(Buzzer);

  delay(100);                               

  tone(Buzzer, 2500);
  delay(150);
  noTone(Buzzer);

  delay(500);
}


// Main Loop  

void loop() {

  int distance = getAverageDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Error check
  if (distance == -1) {

    noTone(Buzzer);

    Serial.println("Sensor error / no echo");

    delay(100);
    return;
  }

  alertUser(distance);
}


// Get Distance

int getDistance() {

  unsigned long duration;

  // Send Trig out
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);

  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(Trig, LOW);

  // Get Echo
  duration = pulseIn(Echo, HIGH, 30000);

  // If no echo received
  if (duration == 0) {
    return -1;
  }

  // Convert time into distance, 343 metre per second is the speed of sound in air
  int distance = (duration * 0.0343) / 2;

  return distance;
}


// Averaging (Filtering) the mean distance obtained

int getAverageDistance() {

  long total = 0;

  int validReadings = 0;

  for (int i = 0; i < 5; i++) {

    int distance = getDistance();

    if (distance != -1) {

      total += distance;
      validReadings++;

    }

    delay(10);
  }

  // If no valid readings were received
  if (validReadings == 0) {
    return -1;
  }

  return total / validReadings;
}


// Buzzer Alert System

void alertUser(int distance) {

  // Safe zone is more than 100 cms

  if (distance > safe_dist) {

    noTone(Buzzer);

    delay(100);
  }


  // Warning Zone is 60 to 100 cms

  else if (distance > warn_dist) {

    tone(Buzzer, 1800);

    delay(60);

    noTone(Buzzer);

    delay(600);
  }


  // Danger Zone is 30 to 60 cms

  else if (distance > danger_dist) {

    tone(Buzzer, 2000);

    delay(70);

    noTone(Buzzer);

    delay(300);
  }


  // Critical Zone is 15 to 30 cms

  else if (distance > crit_dist) {

    tone(Buzzer, 2500);

    delay(80);

    noTone(Buzzer);

    delay(120);
  }


  // Very Close is 5 to 15 cms

  else if (distance >= min_dist) {

    tone(Buzzer, 3000);

    delay(100);

    noTone(Buzzer);

    delay(40);
  }


  // Invalid Range is less than 5 cms

  else {

    tone(Buzzer, 3000);

    delay(150);

    noTone(Buzzer);

    delay(20);
  }
}
