// =====================================================
// BLIND ASSISTIVE HAT - VERSION 2
// Datathon'26 - SRM
// =====================================================

// Pin definitions
const int Trig = 2;
const int Echo = 3;
const int Buzzer = 8;

// Distance limits in centimetres
const int SAFE_DISTANCE = 100;
const int WARNING_DISTANCE = 60;
const int DANGER_DISTANCE = 30;
const int CRITICAL_DISTANCE = 15;
const int MIN_DISTANCE = 5;


// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(9600);

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Buzzer, OUTPUT);

  // Startup indication
  tone(Buzzer, 2000);
  delay(150);
  noTone(Buzzer);

  delay(100);

  tone(Buzzer, 2500);
  delay(150);
  noTone(Buzzer);

  delay(500);
}


// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

  int distance = getAverageDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check for invalid sensor reading
  if (distance == -1) {

    noTone(Buzzer);

    Serial.println("Sensor error / no echo");

    delay(100);
    return;
  }

  // Give warning according to distance
  alertUser(distance);
}


// =====================================================
// GET DISTANCE
// =====================================================

int getDistance() {

  unsigned long duration;

  // Send trigger pulse
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);

  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(Trig, LOW);

  // Measure echo
  duration = pulseIn(Echo, HIGH, 30000);

  // No echo received
  if (duration == 0) {
    return -1;
  }

  // Convert time into distance
  int distance = (duration * 0.0343) / 2;

  return distance;
}


// =====================================================
// AVERAGE MULTIPLE READINGS
// =====================================================

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


// =====================================================
// BUZZER ALERT SYSTEM
// =====================================================

void alertUser(int distance) {

  // -----------------------------------------
  // SAFE ZONE
  // More than 100 cm
  // -----------------------------------------

  if (distance > SAFE_DISTANCE) {

    noTone(Buzzer);

    delay(100);
  }


  // -----------------------------------------
  // WARNING ZONE
  // 60 - 100 cm
  // -----------------------------------------

  else if (distance > WARNING_DISTANCE) {

    tone(Buzzer, 1800);

    delay(60);

    noTone(Buzzer);

    delay(600);
  }


  // -----------------------------------------
  // DANGER ZONE
  // 30 - 60 cm
  // -----------------------------------------

  else if (distance > DANGER_DISTANCE) {

    tone(Buzzer, 2000);

    delay(70);

    noTone(Buzzer);

    delay(300);
  }


  // -----------------------------------------
  // CRITICAL ZONE
  // 15 - 30 cm
  // -----------------------------------------

  else if (distance > CRITICAL_DISTANCE) {

    tone(Buzzer, 2500);

    delay(80);

    noTone(Buzzer);

    delay(120);
  }


  // -----------------------------------------
  // VERY CLOSE
  // 5 - 15 cm
  // -----------------------------------------

  else if (distance >= MIN_DISTANCE) {

    tone(Buzzer, 3000);

    delay(100);

    noTone(Buzzer);

    delay(40);
  }


  // -----------------------------------------
  // TOO CLOSE / INVALID RANGE
  // Less than 5 cm
  // -----------------------------------------

  else {

    tone(Buzzer, 3000);

    delay(150);

    noTone(Buzzer);

    delay(20);
  }
}
