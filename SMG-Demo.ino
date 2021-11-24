//CuiYao

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_NeoPixel.h>
#include <Adafruit_ssd1306syp.h>
#include "LED.h"

#define LED_PIN 0
#define SDA_PIN 2
#define SCL_PIN 14
const int TrigPin = 4;     //设置发射脚位，对应ESP8266 D2
const int EchoPin = 5;    //设置接收脚位，对应ESP8266 D1

Adafruit_ssd1306syp display(SDA_PIN,SCL_PIN);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(29, LED_PIN, NEO_GRB + NEO_KHZ800);

float cm;                 //浮点型数据类型（加小数点，提高精准度）

const uint8_t LED_0[29][3] = { 
{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},
{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},
{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},
{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255}, 
{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},{255, 255, 255},};

void setup() {
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  display.initialize();
  
  strip.begin();

  strip.setBrightness(50);
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

  //********LED*************
  for (uint8_t j = 0; j < 16; j++) {

    for (uint8_t k = 0; k < 16; k++)

    strip.setPixelColor(k, 0);

    for (int8_t i = 0; i <= j; i++)

    strip.setPixelColor(i, strip.Color(LED_0[(j-i) % 7][0], LED_0[(j-i) % 7][1], LED_0[(j-i) % 7][2]));

    strip.show();

    delay(20);

}


  

  delay(1000);
}
