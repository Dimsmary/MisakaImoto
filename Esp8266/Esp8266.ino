#include <Adafruit_NeoPixel.h>


// 设定WS2812数据传输脚和灯珠数量
#define LED_PIN 13
#define LED_NUM 8

// 设定ADC引脚
#define ADC_PIN A0

#define SIGNAL_PIN 2
#define SDA_PIN 14
#define SCL_PIN 12

// ADC 数值矫正
#define BIAS -1
//#define BIAS 0.25

// ADC 各个位数存放
int L1 = 0;
int R1 = 0;
int R2 = 0;

// 


// WS2812传输对象
Adafruit_NeoPixel pixels(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);

// ADC数值
float batVoltage = 0;
int sensorValue = 0;  // value read from the pot


// WS2812测试函数
void light_up(){
     pixels.clear();
    for(int i=0; i<LED_NUM; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(15, 15, 15));
    pixels.show();   // Send the updated pixel colors to the hardware.
    }
}

void light_down(){
    pixels.clear();
    for(int i=0; i<LED_NUM; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();   // Send the updated pixel colors to the hardware.
    }
}


// 创建一个下降沿
void clock_pulse(){
  delay(10);
  digitalWrite(SCL_PIN, HIGH);
  digitalWrite(SCL_PIN, LOW);
  delay(10);
  digitalWrite(SCL_PIN, HIGH);
  delay(10);
}

// 负责数据传输
void data_transfer(int data){
  for(int i = 3; i > -1; i--){
    int load = 0;
    load = (data >> i) & 1;
    if(load){
      digitalWrite(SDA_PIN, HIGH);
    }
    else{
      digitalWrite(SDA_PIN, LOW);
    }
    clock_pulse();
  }
}

// 电压数据传输
void voltage_transfer(){

  // 传输开始的头码
  for(int i = 0; i < 12; i ++){
    digitalWrite(SDA_PIN, LOW);
    clock_pulse();
  }
  Serial.println("12 HEAD OVER");
  // 开始传输数据
  data_transfer(L1);
  data_transfer(R1);
  data_transfer(R2);
}

void update_voltage(){
  // 电压检测
  sensorValue = analogRead(ADC_PIN);
  batVoltage = (sensorValue / 1024.0) * 11 -BIAS;

  L1 = batVoltage;
  R1 = (batVoltage - L1) * 10;
  R2 = ((batVoltage - L1) - R1 / 10.0) * 100;
  
  Serial.println(batVoltage);
  
}

void setup() {
  // 初始化WS2812库
  pixels.begin();

  // 初始化串口
  Serial.begin(115200);

  // 初始化IO
  pinMode(SIGNAL_PIN, INPUT);
  pinMode(SDA_PIN, OUTPUT);
  pinMode(SCL_PIN, OUTPUT);
  digitalWrite(SDA_PIN, HIGH);
  digitalWrite(SCL_PIN, HIGH);


}

void loop() {
  delay(1000);

  // 如果树莓派仍然未启动
  if(digitalRead(SIGNAL_PIN)){
    light_up();
  }
  else{
    update_voltage();
    if(batVoltage > 1){
    voltage_transfer();
    }
    light_down();
  }

}
