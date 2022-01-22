#include <LiquidCrystal.h>        //مكتبة الlcd 
#include<Keypad.h>               // المكتبة الخاصة ب keypad 

String PASS = "1234";
String text = "";
float temp=0;
                                   //تعريف الارجل المتصله بال lcd
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const byte ROWS = 4; //اربعة صفوف             
const byte COLS = 3; // 3 اعمده              
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {36, 37, 38, 39,}; //تعريف الارجل المتصله بال kayPad
byte colPins[COLS] = {40, 41, 42}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void Gas ();
void PIR();
void FANs_ON();
void print_temp();
void door_open();
void door_close();
void choice();
bool PASWORD();
void door_lock();

void setup() {
  lcd.begin (16,2);
  lcd.print ("Smart Home");
  Serial.begin(9600);
  Serial.println(" Smart Home ");
for (int i=2;i<54;i++)
pinMode(i,OUTPUT);
  pinMode(30,INPUT);
  pinMode(A1,INPUT);
for (int i=2;i<54;i++)
digitalWrite(i,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (!digitalRead(30))
  door_lock();
  choice();
  Gas();
  PIR();
  FANs_ON();

}
//_________________________________________
//_________________________________________
void choice()
{
    if (Serial.available())
  {
    while (Serial.available())
    {
      text = Serial.readString();
    }
    if (text == "led1")
      {digitalWrite(2, HIGH);Serial.println("great");}
    else if (text == "led2")
      digitalWrite(3, HIGH);
    else if (text == "led3")
      digitalWrite(4, HIGH);
    else if (text == "led4")
      digitalWrite(5, HIGH);
    else if (text == "led5")
      digitalWrite(6, HIGH);
    else if (text == "led1off")
      digitalWrite(2, LOW);
    else if (text == "led2off")
      digitalWrite(3, LOW);
    else if (text == "led3off")
      digitalWrite(4, LOW);
    else if (text == "led4off")
      digitalWrite(5, LOW);
    else if (text == "led5off")
      digitalWrite(6, LOW);
      //____________________
    else if (text == "fan1")
      digitalWrite(31, HIGH);
    else if (text == "fan2")
      digitalWrite(32, HIGH);
    else if (text == "fan3")
      digitalWrite(33, HIGH);
    else if (text == "fan4")
      digitalWrite(34, HIGH);
    else if (text == "fans_on")
               FANs_ON();
    else if (text == "fan1off")
      digitalWrite(31, LOW);
    else if (text == "fan2off")
      digitalWrite(32, LOW);
    else if (text == "fan3off")
      digitalWrite(33, LOW);
    else if (text == "fan4off")
      digitalWrite(34, LOW);
      //_____________________
    else if (text == "temp")
      print_temp();
    else if (text == "door1open")
      {digitalWrite(49, HIGH);door_open();digitalWrite(49, LOW);}
    else if (text == "door2open")
      {digitalWrite(48, HIGH);door_open();digitalWrite(48, LOW);}
    else if (text == "door3open")
      {digitalWrite(47, HIGH);door_open();digitalWrite(47, LOW);}
    else if (text == "door1close")
      {digitalWrite(49, HIGH);door_close();digitalWrite(49, LOW);}
    else if (text == "door2close")
      {digitalWrite(48, HIGH);door_close();digitalWrite(48, LOW);}
    else if (text == "door3close")
      {digitalWrite(47, HIGH);door_close();digitalWrite(47, LOW);}
      //_____________________
  
  
    else if (text == "");
    else Serial.println("wrong choice");
  }
  text = "";
  
}
//___________________________________________
//___________________________________________
void FANs_ON()
{
  temp = analogRead(1);
                               //قراءة قيمة الجهد الناتج من الحساس
  temp = temp * 0.48875125;
  //لو درجة الحرارة أعلي من 40 جمبع المراح تعمل                               
    if (temp > 40)   
  {
    for (int i = 31; i < 35; i++)
    {
      digitalWrite(i, HIGH);
    }
  }
  // لو درجة الحرارة أصبحت أقل من 35 يتم ايقاف جميع  المراوح                              
  else if ( temp < 35 )
  {
    for (int i = 31; i < 36; i++)
    {
      digitalWrite(i, LOW);
    }
  }
}
//_____________________________________________
//_____________________________________________
void print_temp()
{
  temp = analogRead(1);
                               //قراءة قيمة الجهد الناتج من الحساس
  temp = temp * 0.48875125;
                              //تحويل الجهد الكهربي لدرجة الحرارة الحقيقية
  lcd.clear();
  lcd.setCursor(1, 1);        //تعريف الlcd اين ستتم الكتابة
  lcd.print("TEMP= ");        //جمله الطباعةLCD
  lcd.print(temp);
  lcd.print("*C");
  //__________________________
  Serial.print("TEMPERATURE = ");  //جمله الطباعه علي terminal
  Serial.print(temp);
  Serial.println("*C");
  //__________________________
  delay(50);                    // تاخير زمني 50 ملي ثانية
}
//____________________________________________________________
//____________________________________________________________

void door_close()                //غلق الباب 
{
  unsigned char k;
  unsigned char i=0;
// Turn One Side
for (int j=0; j<48; j++)
{
  k = (1<<i); 
  PORTB=PORTB | k;
  PORTB=PORTB & (k+240);
  i++;              // Advance to the next output pin
  delay(50);   // StepDelay
  if (i==4)
      i=0;
}
}
//_______________________________________________________________
//_______________________________________________________________
void door_open()                        //فتح الباب
{
unsigned char k=128;
unsigned char i=4;
// Turn One Side
for (int j=0; j<48; j++)
{
  k = (128>>i); 
  PORTB=PORTB | k;
  PORTB=PORTB & (k+240); 
  i++;              // Advance to the next output pin
 delay(100);   // StepDelay
  if (i==8)
      i=4;
}
}
//_______________________________________________________________
//_______________________________________________________________

void Gas ()
{
  if ( digitalRead(45)) 
  {
    digitalWrite(44, HIGH);
    lcd.clear();
     delay(200);
    lcd.setCursor(0, 1);
    lcd.print("Fire !! Fire !!");
     delay(200);
  }
  else  
  {digitalWrite(44, LOW);}
}
//_________________________________________________________________
//_________________________________________________________________
void PIR()
{
  if (digitalRead(46)) {
    lcd.clear();
      delay(200);
    lcd.setCursor(0, 1);
    lcd.print("Welcome Home (:  ");
    delay(200);  
  }
  else {}
}
//________________________________________________________________
//________________________________________________________________
void door_lock()
{
 if(PASWORD())
   {
    digitalWrite(43,HIGH); digitalWrite(44,LOW); 
    Serial.println(); Serial.println("Correct PASS"); 
    lcd.clear();lcd.print("Correct PASS :)");
    delay(1000);
   } 
   else
   {
    digitalWrite(44,HIGH); digitalWrite(43,LOW); 
    Serial.println();Serial.println("Wrong PASS");
    lcd.clear();lcd.print("Wrong PASS :(");
    delay(1000);
   } 
    digitalWrite(43,LOW); digitalWrite(44,LOW);
   
}
//_______________________________________________
//_______________________________________________
bool PASWORD()
{
  Serial.println();
  Serial.println("DOOR_LOCK");  
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("DOOR_LOCK :)");
  delay(1000);
  lcd.clear();
  lcd.print("Enter PASS: ");
  Serial.println("Enter PASS:"); 
  lcd.setCursor(1, 1);
  text = "";
  while (1) {
    char key = keypad.getKey();
    if (key) {
      if (key == '#' && text == PASS)  return true;
      else if (key == '#')             return false;
      else {
        lcd.print('*');
        Serial.print('*');
        text += key;
      }
    }
  }
}
