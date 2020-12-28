#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MPU6050.h"

//Display
#define OLED_DC     A3
#define OLED_CS     A5
#define OLED_RESET  A4
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

double displayMenu;
bool needClear = false;
void menuConstruction();

MPU6050 mpu;
int IMU0, IMU1, IMU2;

void menuConstruction()
{

  if (((displayMenu) == (0))) {
    
    display.setTextColor(WHITE);
    needClear = true;

    display.setCursor(0, 0);
    display.print("pitch:");
    display.setCursor(0, 10);
    display.print(IMU0);
    display.setCursor(0, 20);
    display.print("roll:");
    display.setCursor(0, 30);
    display.print(IMU1);
  }

}

void setup()   {

  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  displayMenu = 0;
  mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G);

}


void loop() {

  menuConstruction();

  if (needClear) {
    display.display();
    display.clearDisplay();
    needClear = false;
  }
  
  Vector normAccel = mpu.readNormalizeAccel();
  IMU0 = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis)) * 180.0) / M_PI;
  IMU1 = (atan2(normAccel.YAxis, normAccel.ZAxis) * 180.0) / M_PI;
  IMU2 = normAccel.ZAxis;
}
