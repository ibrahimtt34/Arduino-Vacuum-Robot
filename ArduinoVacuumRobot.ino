#define echoPin 13 //Ultrasonik sensörün echo pini Arduino'nun 12.pinine
#define trigPin 12 //Ultrasonik sensörün trig pini Arduino'nun 13.pinine tanımlandı.
#define MotorR1 7
#define MotorR2 6
#define Buton 9
#define MotorL1 5
#define MotorL2 4
int sensorValue = analogRead(A0);
long sure, uzaklik, voltage; //süre ve uzaklık diye iki değişken tanımlıyoruz.
void setup() {
  // ultrasonik sensör Trig pininden ses dalgaları gönderdiği için OUTPUT (Çıkış),
  // bu dalgaları Echo pini ile geri aldığı için INPUT (Giriş) olarak tanımlanır.
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(Buton, INPUT);
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);

  Serial.begin(9600);
}
void loop() {
  digitalWrite(trigPin, LOW); //sensör pasif hale getirildi
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); //Sensore ses dalgasının üretmesi için emir verildi
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi
  sure = pulseIn(echoPin, HIGH); //ses dalgasının geri dönmesi için geçen sure ölçülüyor
  uzaklik = sure / 29.1 / 2; //ölçülen süre uzaklığa çevriliyor
  Serial.println(uzaklik);
  voltaj();

  if(( uzaklik < 15 || digitalRead(Buton) == 1 )&& voltage>3.9) // Uzaklık 15'den küçük ise,
  {
    geri();  // 150 ms geri git

    sag();  // 250 ms sağa dön
     Serial.println("donus yapıldı");
  }
  else if (voltage>3.9){  // değil ise,
    ileri(); // ileri git
     Serial.println("ileri gidiliyor");
  }
  else
  { motorlarikapat();
  Serial.println(voltage);
}
}

void ileri(){  // Robotun ileri yönde hareketi için fonksiyon tanımlıyoruz.
  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif

  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif

  
  
}
void sag(){ // Robotun sağa dönme hareketi için fonksiyon tanımlıyoruz.
  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif
 
  digitalWrite(MotorL1, LOW); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif
  delay(1000);
  Serial.println("sag donus yapıldı");
  

  
  
}
void geri(){ // Robotun geri yönde hareketi için fonksiyon tanımlıyoruz.
  digitalWrite(MotorR1, LOW); // Sağ motorun ileri hareketi pasif
  digitalWrite(MotorR2, HIGH); // Sağ motorun geri hareketi aktif
 
  digitalWrite(MotorL1, LOW); // Sol motorun ileri hareketi pasif
  digitalWrite(MotorL2, HIGH); // Sol motorun geri hareketi aktif
    delay(1000);
    Serial.println("geriyapıldı");
}

void motorlarikapat()
{ // Robotu kapatıyoruz.
  digitalWrite(MotorR1, LOW); // Sağ motorun ileri hareketi pasif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif
 
  digitalWrite(MotorL1, LOW); // Sol motorun ileri hareketi pasif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif
  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, LOW);
    Serial.println("sistem kapalı");
}
void voltaj(){ // read the input on analog pin 0:
   // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(voltage);
}



  
