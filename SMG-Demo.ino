//CuiYao

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_NeoPixel.h>
#include <Adafruit_ssd1306syp.h>
 
#define LED_PIN 12 //LED LED需要接GPIO 数字
#define SDA_PIN 2
#define SCL_PIN 14
const int TrigPin = 4;     //设置发射脚位，对应ESP8266 D2
const int EchoPin = 5;    //设置接收脚位，对应ESP8266 D1
#define NUMPIXELS 29*3 // LED个数


Adafruit_ssd1306syp display(SDA_PIN,SCL_PIN);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

float cm;                 //浮点型数据类型（加小数点，提高精准度）

const uint8_t LED_0[10][29] = { 
  {255,255,255,255,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,},         //9
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,},   //8
  {0,0,0,0,0,0,0,0,0,0,255,255,255,255,255,255,255,255,0,0,255,255,255,255,0,0,0,0,0,},                                     //7
  {255,255,255,255,255,255,255,255,255,255,255,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,},         //6
  {255,255,255,255,0,0,0,255,255,255,255,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,},               //5
  {255,255,255,255,0,0,0,0,0,0,0,255,255,255,255,255,255,255,0,0,0,0,0,0,255,255,255,255,255,},                             //4
  {0,0,0,0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,},                 //3
  {0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,0,0,0,255,255,255,255,255,255,255,255,255,255,255,},               //2
  {0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,0,0,0,},                                               //1
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,},             //0
};

int i = 0;

int g=0;
int s=9;

void setup() {
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  display.initialize();
  
  pixels.begin();//WS2812初始化
  pixels.show();
}

void loop() {
  digitalWrite(TrigPin, LOW);       //用低高低电平发送脉冲给Trigpin引脚
  delayMicroseconds(2);             //微秒级延时
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  cm = pulseIn(EchoPin, HIGH) / 58.0; //读取脉冲宽度，换算成厘米
  Serial.print(cm);                   //显示距离
  Serial.print("cm");                   //显示单位
  Serial.println();                   //回车
  //*******OLED**********
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Distance: ");
  display.print(cm);
  display.println("  cm");
  display.update();
  display.clear();

  if(cm<15){
    shuowLED();
  }
  delay(1000);
}

void shuowLED(){
  if (i>9){
    i=0;
    s++;
   }
   if(s>9){
      s=0;
      g++;
   }
   if (g>9){
       g=0;
   }
   
   pixels.clear();
     //********LED*************
  for (uint8_t j = 0; j < NUMPIXELS/3; j++) {
   
    pixels.setPixelColor(j, LED_0[g][j],LED_0[g][j],LED_0[g][j]);
    pixels.setPixelColor(j+29, LED_0[s][j],LED_0[s][j],LED_0[s][j]);
    pixels.setPixelColor(j+29*2, LED_0[i][j],LED_0[i][j],LED_0[i][j]);
    pixels.show();

   }
   
    
    i++;
}
