#include <Wire.h>
#include <IMU_MPU9250.h>
 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


#define    MPU9250_ADDRESS            0x68

#define LED_FACE1   2
#define LED_FACE2   3
#define LED_FACE3    4
#define LED_FACE4    5
#define LED_FACE5    6
#define LED_FACE6    7

#define LED_COUNT 4

// Declare our NeoPixel strip object:
Adafruit_NeoPixel face1(LED_COUNT, LED_FACE1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel face2(LED_COUNT, LED_FACE2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel face3(LED_COUNT, LED_FACE3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel face4(LED_COUNT, LED_FACE4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel face5(LED_COUNT, LED_FACE5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel face6(LED_COUNT, LED_FACE6, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel cube[6] = { face1, face2, face3, face4, face5, face6 };

#define GREEN 65280
#define BLUE 255
#define RED 16711680
#define YELLOW 16776960
#define ORANGE 15626001
#define  WHITE 16777215

long colors[6] = { RED, ORANGE, YELLOW, WHITE, BLUE, GREEN };

long debug_duration = 400;

long duration = 300;
long last_time = 0;

long debug_last_time = 0;

long bps = 9600;

float threshold = 1;
int old_face = 1;
int current_face = 1;

MPU9250 imu;
 
void updateIMU(){
 
  if (imu.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01){   
    imu.readAccelData(imu.accelCount);
    imu.getAres();
 
    imu.ax = (float)imu.accelCount[0]*imu.aRes;
    imu.ay = (float)imu.accelCount[1]*imu.aRes;
    imu.az = (float)imu.accelCount[2]*imu.aRes;
    imu.readGyroData(imu.gyroCount);
    imu.getGres();
 
    imu.gx = (float)imu.gyroCount[0]*imu.gRes;
    imu.gy = (float)imu.gyroCount[1]*imu.gRes;
    imu.gz = (float)imu.gyroCount[2]*imu.gRes;
  }
 
  imu.updateTime();
  imu.delt_t = millis() - imu.count;
}


 void AccDebug(){

   if ( millis() - debug_last_time > debug_duration){
     Serial.print("Force \t X: ");
     Serial.print(imu.ax);
     Serial.print(" \t Y: ");
     Serial.print(imu.ay);
     Serial.print(" \t Z: ");
     Serial.println(imu.az);
     Serial.print("Max Value : ");
     Serial.println( max( max ( abs(imu.ax), abs(imu.ay)), abs(imu.az) ));
     debug_last_time = millis();
  }
 };

 void DetectFace(){
   
   if ( millis() - last_time > duration ){
     float maxvalue = max( max ( abs(imu.ax), abs(imu.ay)), abs(imu.az) );
     
     if ( abs(imu.ax) == maxvalue ) {
      if (imu.ax > 0){
        current_face = 1;
      }else{
        current_face = 6;
      } 
    }
      
    if(  abs(imu.ay) == maxvalue ){
      if (imu.ay > 0){
        current_face = 2;
      }else{
        current_face = 5;
      } 
    }
      
    if(  abs(imu.az)  == maxvalue ){
      if (imu.az > 0){
        current_face = 3;
      }else{
        current_face = 4;
      } 
    }
      
      //Detect Face change
      if( current_face != old_face ){
        Serial.print(" New Face ");Serial.print(current_face);
    
        cube[old_face-1].clear();
        cube[old_face-1].show();
        
        cube[current_face-1].fill( colors[ current_face-1 ] );
        cube[current_face-1].show();
        old_face = current_face;
      }
     
     
     last_time = millis();
   }
 };


//Initialize Stripes
void setupStripes(){

  for( int i =0 ; i<6 ; i++){
    cube[i].begin(); 
    cube[i].show();
    cube[i].setBrightness(70);
  }
}

void setup() {
  Wire.begin();
  Serial.begin(bps);
  Serial.println("Dado Colores");

  imu.initMPU9250();

  //Setup cube LED Faces
  setupStripes();
  
  //Initialize Variables
  last_time = millis();
}

void loop() {
    //Debug data from IMU Sensor
   //AccDebug();
   
   DetectFace();
   updateIMU();  
   
}
