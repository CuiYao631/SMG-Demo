const int TrigPin = 4;     //设置发射脚位，对应ESP8266 D2
const int EchoPin = 5;    //设置接收脚位，对应ESP8266 D1
float cm;                 //浮点型数据类型（加小数点，提高精准度）

void setup() {
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void loop() {
  digitalWrite(TrigPin, LOW);       //用低高低电平发送脉冲给Trigpin引脚
  delayMicroseconds(2);             //微秒级延时
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  cm = pulseIn(EchoPin, HIGH) / 58.0; //读取脉冲宽度，换算成厘米
  Serial.print(cm);                   //显示距离
  Serial.print(cm);                   //显示单位
  Serial.println();                   //回车
  delay(1000);
}
