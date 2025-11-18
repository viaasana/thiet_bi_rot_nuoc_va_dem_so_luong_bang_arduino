#import "MortorControl.h"

const int motorPin = 6;      // Chân D6 (PWM) nối với Gate của MOSFET 

void MortorSetup() {
  pinMode(motorPin, OUTPUT); // Đặt chân D6 là OUTPUT 
}

void MortorRun(int velocity) {
  

  // 2. Chuyển đổi (Map) giá trị sang dải PWM (0 - 255) 
  int pwmValue = map(velocity, 0, 1023, 0, 255);

  // 3. Gửi giá trị PWM đến chân MOSFET để điều khiển tốc độ 
  analogWrite(motorPin, pwmValue);

  delay(10); // Độ trễ nhỏ
}