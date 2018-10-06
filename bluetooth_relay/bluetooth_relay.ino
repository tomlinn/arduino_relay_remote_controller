#include <SoftwareSerial.h>   // 引用程式庫
char ledOn = "1";
char ledOFF = "0";
int ledPin = 2;
int v;
char t;
// 定義連接藍牙模組的序列埠
SoftwareSerial BT(9, 8); // 接收腳, 傳送腳
char val;  // 儲存接收資料的變數

void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");
  pinMode(ledPin, OUTPUT);
  pinMode(12, INPUT);
  // 設定藍牙模組的連線速率
  // 如果是HC-05，請改成38400
  BT.begin(9600);
  v=0;
}

void loop() {
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }

  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
  }
  
  int contact = digitalRead(12);
  if (contact == LOW) {
    if (v == 0) {
      digitalWrite(ledPin, HIGH);
      Serial.println("High");
      v=1;
    } else if (v == 1) {
      digitalWrite(ledPin, LOW);
      Serial.println("Low");
      v=0;
    }
    delay(1000);
  }

  if (val == '0') {

    // Setting LED To ON.
    Serial.println("OFF");
    digitalWrite(ledPin, HIGH);
    BT.print("H");
  }
  else if (val == '1') {
    // Setting LED To OFF.
    Serial.println("ON");
    digitalWrite(ledPin, LOW);
    BT.print("L");
  }
  else if (val == '2') {
    // Setting LED To OFF.
    Serial.println("Time:");
    if (BT.available()) {
          t = BT.read();
        }
    digitalWrite(ledPin, LOW);
    Serial.println("delay");
    Serial.println(t);
    
    Serial.println("FINal");
    delay((t-'0')*1000*60);
    digitalWrite(ledPin, HIGH);
    BT.print("H");
    
  }
  val = 3;
}
