#include<SPI.h>
#include<MFRC522.h>
#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>
#define UID "5d6b6889" // 取得した識別子を記述
int NUMBER=0;

constexpr uint8_t RST_PIN = 9;//RSTピンの指定
constexpr uint8_t SS_PIN = 10;//SSピンの指定
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

Adafruit_SSD1306 display(-1);// ディスプレイ変数の宣言




void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);// ディスプレイの初期化
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));


  display.clearDisplay();//一度初期化
  display.setTextSize(2);// 出力する文字の大きさ
  display.setTextColor(WHITE);//出力する文字の色
  display.setCursor(0, 0);//カーソル位置の指定
  display.println("Nocard");// ディスプレイへ表示する文字列
  display.display();//ディスプレイ情報の更新

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, OUTPUT);
  pinMode(A3,INPUT);
  digitalWrite(A1, HIGH);
}

void loop() {
  digitalWrite(3, HIGH); //初期設定
  digitalWrite(4, LOW); //初期設定
  noTone(6);//初期設定
  if ( ! mfrc522.PICC_IsNewCardPresent()) return;// Mifareカードの確認（新しいカードが無ければ終了し、loop関数を繰り返す）
  if ( ! mfrc522.PICC_ReadCardSerial()) return;// Mifareカードのデータ読み込み（読み取れなければ終了し、loop関数を繰り返す）



  String strBuf[mfrc522.uid.size];
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    strBuf[i] =  String(mfrc522.uid.uidByte[i], HEX);
    if (strBuf[i].length() == 1) {
      strBuf[i] = "0" + strBuf[i];
    }
  }
  String strUID = strBuf[0] + strBuf[1] + strBuf[2] + strBuf[3];
  Serial.println(strUID);



  if ( strUID == UID ) {
    display.clearDisplay();//一度初期化
    display.setCursor(0, 0);//一度初期化
    display.println("collect");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print("cardUID = ");
    display.println(strUID);
    display.display();

    tone(6, 1700);
    delay(30);
    noTone(6);
    delay(30);
    tone(6, 1700, 90);
    delay(500);

    blank(strUID);
    }

  if ( !(strUID == UID) ) {
    display.clearDisplay();//一度初期化
    display.setCursor(0, 0);//一度初期化
    display.println("error!");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print("cardUID = ");
    display.println(strUID);
    display.display();

    Serial.println("else");
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    tone(6, 500);
    delay(1000);

    display.clearDisplay();//一度初期化
    display.setTextSize(2);// 出力する文字の大きさ
    display.setTextColor(WHITE);//出力する文字の色
    display.setCursor(0, 0);//カーソル位置の指定
    display.println("Nocard");// ディスプレイへ表示する文字列
    display.display();//ディスプレイ情報の更新
  }
}

void blank(String strUID) {
    digitalWrite(A1, HIGH);
    int submit =0;
    int button =1;
    Serial.println(submit);
    
    display.clearDisplay();//一度初期化
    display.setTextSize(1);// 出力する文字の大きさ
    display.setTextColor(WHITE);//出力する文字の色
    display.setCursor(0, 0);//カーソル位置の指定
    display.println("select mode and pt");// ディスプレイへ表示する文字
    display.print("cardUID = ");
    display.println(strUID);
    display.display();//ディスプレイ情報の更新
    
 while (submit==0) {
    submit = digitalRead(A0);
    button = digitalRead(A3);
    Serial.println(button);

    
    if (button == 0) {
    NUMBER=NUMBER+10;
    display.clearDisplay();//一度初期化
    display.setTextSize(1);// 出力する文字の大きさ
    display.setCursor(0, 0);//カーソル位置の指定
    display.println("select mode and pt");// ディスプレイへ表示する文字
    display.print("cardUID = ");
    display.println(strUID);
    display.print("NUMBER = ");
    display.setTextSize(2);
    display.println(NUMBER);
    display.display();//ディスプレイ情報の更新
    delay(300);
    }

    
    if (submit == 1) {
      break;
    }
    
    delay(300);
    
}

}

int ESPserial(String strUID,int NUMBER) {
delay(1000);
}
