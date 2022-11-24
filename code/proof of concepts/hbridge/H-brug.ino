// Startknop
const int Knop = 12;

// Led
const int Led = 2;

// Motor Rechts
const int IN1 = 3;
const int IN2 = 9;

// Motor Links
const int IN3 = 10;
const int IN4 = 11;

// Variabelen
bool StatusKnop;

void setup() {
  Serial.begin(9600);

  // Digitaal
  pinMode(Led, OUTPUT);
  pinMode(Knop, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  StatusKnop = digitalRead(Knop);

  if (StatusKnop == HIGH)
  {
    Serial.write("knop");
    digitalWrite(Led, HIGH);
    delay(500);
    digitalWrite(Led, LOW);
    delay(500);
    digitalWrite(Led, HIGH);
    delay(500);
    digitalWrite(Led, LOW);
    delay(500);
    digitalWrite(Led, HIGH);
    delay(500);
    digitalWrite(Led, LOW);
    delay(500);

    // Voorwaarts
    for (int i = 0; i <= 255; i++)
    {
      analogWrite(IN1, i);
      analogWrite(IN2, 0);
      analogWrite(IN3, 0);
      analogWrite(IN4, i);
      delay(10);
    }
    for (int i = 255; i >= 0; i--)
    {
      analogWrite(IN1, i);
      analogWrite(IN2, 0);
      analogWrite(IN3, 0);
      analogWrite(IN4, i);
      delay(10);
    }

    delay(2000);

    // Achterwaarts
    for (int i = 0; i <= 255; i++)
    {
      analogWrite(IN1, 0);
      analogWrite(IN2, i);
      analogWrite(IN3, i);
      analogWrite(IN4, 0);
      delay(10);
    }
    for (int i = 255; i >= 0; i--)
    {
      analogWrite(IN1, 0);
      analogWrite(IN2, i);
      analogWrite(IN3, i);
      analogWrite(IN4, 0);
      delay(10);
    }

    delay(2000);

    // Links
    for (int i = 0; i <= 255; i++)
    {
      analogWrite(IN1, i);
      analogWrite(IN2, 0);
      analogWrite(IN3, i);
      analogWrite(IN4, 0);
      delay(10);
    }
    for (int i = 255; i >= 0; i--)
    {
      analogWrite(IN1, i);
      analogWrite(IN2, 0);
      analogWrite(IN3, i);
      analogWrite(IN4, 0);
      delay(10);
    }

    delay(2000);

    // Rechts
    for (int i = 0; i <= 255; i++)
    {
      analogWrite(IN1, 0);
      analogWrite(IN2, i);
      analogWrite(IN3, 0);
      analogWrite(IN4, i);
      delay(10);
    }
    for (int i = 255; i >= 0; i--)
    {
      analogWrite(IN1, 0);
      analogWrite(IN2, i);
      analogWrite(IN3, 0);
      analogWrite(IN4, i);
      delay(10);
    }
    //klaar
    digitalWrite(Led, HIGH);
    delay(500);
    digitalWrite(Led, LOW);
  }
}
