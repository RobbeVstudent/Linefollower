//Sensoren (links naar rechts):
const int sen1 = A7;
const int sen2 = A6;
const int sen3 = A5;
const int sen4 = A4;
const int sen5 = A3;
const int sen6 = A2;
const int sen7 = A1;
const int sen8 = A0;
int vals1,vals2,vals3,vals4,vals5,vals6,vals7,vals8;

void setup() {
  Serial.begin(9600);

  //pinnen:
  pinMode(sen1,INPUT);
  pinMode(sen2,INPUT);
  pinMode(sen3,INPUT);
  pinMode(sen4,INPUT);
  pinMode(sen5,INPUT);
  pinMode(sen6,INPUT);
  pinMode(sen7,INPUT);
  pinMode(sen8,INPUT);

}

void loop() {
  
  vals1 = analogRead(sen1);
  vals2 = analogRead(sen2);
  vals3 = analogRead(sen3);
  vals4 = analogRead(sen4);
  vals5 = analogRead(sen5);
  vals6 = analogRead(sen6);
  vals7 = analogRead(sen7);
  vals8 = analogRead(sen8);
  
  Serial.print(vals1);
  Serial.print("  ");
  Serial.print(vals2);
  Serial.print("  ");
  Serial.print(vals3);
  Serial.print("  ");
  Serial.print(vals4);
  Serial.print("  ");
  Serial.print(vals5);
  Serial.print("  ");
  Serial.print(vals6);
  Serial.print("  ");
  Serial.print(vals7);
  Serial.print("  ");
  Serial.print(vals8);
  Serial.print("  ");
  Serial.println();
  delay(1500);
}
