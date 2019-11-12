 #include <LiquidCrystal.h>
LiquidCrystal MyLCD(10, 6, 3, 4, 7, 2);

const int LM_35 = A0;
int inputVal = 0;
float temp = 0;
int redPin = 5;
int greenPin = 9;
int bluePin = 11;
 
#define COMMON_ANODE
 
void setup()
{
  Serial.begin(9600);
  MyLCD.begin(16, 2);
  MyLCD.home();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}
 
void loop()
{
  inputVal = analogRead(LM_35);
  temp = (5.0 * inputVal * 100.0) / 1024;
  Serial.print("The temperature is: ");
  Serial.print(temp);
  Serial.println(" degree celsius.");

  for(int i = 1; i <= 16; i++){
      MyLCD.setCursor(i, 0);
      MyLCD.print(" ");
    }
  if(temp <= 15) {
    setColor(0, 0, 55);  // blue
    Serial.println("It's cold!");
    MyLCD.home();
    MyLCD.print("It's Cold!");
  }
  else if(temp <= 28) {
    setColor(0, 55, 0);  // green  
    Serial.println("Ït's room temperature.");
    MyLCD.home();
    MyLCD.print("It's Room Temp!");
  }
  else {
    setColor(55, 0, 0);  // red
    Serial.println("It's hot!");
    MyLCD.home();
    MyLCD.print("It's Hot!");
  }
  delay(1000);
  
}
 
void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
