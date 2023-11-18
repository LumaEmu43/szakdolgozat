/*
Papp Lukács Lóránt
WOW6MU
ESP-32c3 based light meter for analog cameras

GND         GND
LIGHT       3.3V
VCC         3.3V
CLK         6
DIN/MOSI    7
DC          2
CE          10
RST         3

SCLK : SCK, CLK.
MOSI : SIMO, SDO, DO, DOUT, SO, MTSR.
MISO : SOMI, SDI, DI, DIN, SI, MRST.
SS : nCS, CS, CSB, CSN, nSS, STE, SYNC. 

Available options in most cameras:

Full and half stops:
1.4, 1.7, 2, 2.4, 2.8, 3.3, 4, 4.8, 5.6, 6.7, 8, 9.5, 11, 13, 16, 19, 22, 27, 32, 38, 45, 54, 64

Most common film speeds (ASA/ISO):
12, 16, 20, 25, 32, 40, 50, 64, 80, 100, 125, 160, 200, 250, 320, 400, 500, 640, 800, 1000, 1250, 1600, 2000, 2500, 3200, 6400

Shutter speeds in seconds:
1, 1/2, 1/4, 1/8, 1/15, 1/30, 1/60, 1/125, 1/250, 1/500, 1/1000, 1/2000, 1/4000, 1/8000

EV = log10(lux * iso / INCIDENT_CALIBRATION) / log10(2);

double shutterspeed = (pow(2, EV) / pow(aperature, 2));
https://learn.adafruit.com/adafruit-veml7700/adjusting-for-different-light-levels
*/

//Defining constants
//#define APERTURE_N 23     //Number of full and half F-stops
//#define ISO_N 26        //Number of most common ISO/ASA values
//#define SHUTTER_N 19    //Number of possible shutter speeds
//#define INCIDENT_CALIBRATION 330    //330 Calibration constant (C) for incident light meters, see https://en.wikipedia.org/wiki/Light_meter#Calibration_constants
//#define BTN_MEASURE 4


//Defining objects
//BH1750 lightMeter;      //Light meter sensor using the BH1750 library (might change later)
//Adafruit_PCD8544 display = Adafruit_PCD8544(6,7,2,5,3);    //LCD initialization (might change later due to I2C)
//Adafruit_VEML7700 veml = Adafruit_VEML7700();
//Adafruit_PCD8544 display = Adafruit_PCD8544(6,7,2,10,3);

//Defining variables
//long lux = 0.0;    //Measured LUX value
//int8_t ev = 0;
//uint64_t wait = 0;
//int16_t shutter_calc = 0;
//int rotate = 1;
//
//double aperture_array[APERTURE_N] = {1.4, 1.7, 2, 2.4, 2.8, 3.3, 4, 4.8, 5.6, 6.7, 8, 9.5, 11, 13, 16, 19, 22, 27, 32, 38, 45, 54, 64};
//double shutter_array[SHUTTER_N] = {-60, -30, -15, -8, -4, -2, -1, 2, 4, 8, 15, 30, 60, 125, 250, 500, 1000, 2000, 4000};
//int iso_array[ISO_N] = {12, 16, 20, 25, 32, 40, 50, 64, 80, 100, 125, 160, 200, 250, 320, 400, 500, 640, 800, 1000, 1250, 1600, 2000, 2500, 3200, 6400};

//void init()
//{
//    //Wire.setPins(0, 1);
//    //Wire.begin();
//
//    //lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2);
//
//    //lcd.begin(16, 2);
//    //lcd.print("Shutter:");
//
//    //esp_deep_sleep_enable_gpio_wakeup(1 << BTN_MEASURE, ESP_GPIO_WAKEUP_GPIO_HIGH);
//
//    //pinMode(BTN_MEASURE, INPUT);
//}

//void make_measurement(bool init)
//{
//    if(digitalRead(BTN_MEASURE) | init)
//        {
//            //lux = lightMeter.readLightLevel();
//            ev = log10(lux * iso_array[25] / INCIDENT_CALIBRATION) / log10(2);
//            shutter_calc = (pow(2, ev) / pow(aperture_array[4], 2));
//
//            for (int i = 0; i < (sizeof(shutter_array) / sizeof(double)) - 1; i++) {
//                if (shutter_calc >= shutter_array[i] && shutter_calc <= shutter_array[i + 1]) {
//                if (abs(shutter_calc - shutter_array[i]) <= abs(shutter_calc) - shutter_array[i + 1]) {
//                    shutter_calc = shutter_array[i];
//                } else {
//                    shutter_calc = shutter_array[i + 1];
//                }
//                break;
//                }
//            }
//
//            printf("LUX: %ld; ", lux);
//            printf("Speed: %d; ", iso_array[25]);
//            printf("F: %f; ", aperture_array[4]);
//            printf("Shutter: 1/%d; ", shutter_calc);
//            printf("EV: %d\n", ev);
//
//            wait = 0;
//
//            delay(100);
//
//            //lcd.setCursor(0, 1);
//            //lcd.print("1/" + String(shutter_calc));
//
//            delay(500);
//        }
//}
//
//void go_to_sleep(uint16_t sleep)
//{
//    wait++;
//    if(wait >= sleep)
//    {
//        printf("Going to sleep...\n");
//        delay(50);
//        esp_deep_sleep_start();
//    }
//}

//void app_main(void)
//{
//    //init();
//    //make_measurement(true);
//    Wire.setPins(0, 1);
//    Wire.begin();
//
//    Serial.begin(115200);
//    display.begin();
//    display.setContrast(50);
//    display.clearDisplay();
//
//    if (!veml.begin()) {
//        printf("Failed to communicate with VEML7700 sensor, check wiring?\n");
//    while (1)
//    {
//        delay(1000);
//    };
//  }
//  
//  veml.setGain(VEML7700_GAIN_1_8); // Adjust gain if needed
//  veml.setIntegrationTime(VEML7700_IT_25MS); // Adjust integration time if needed

    
//    while(1)
//    {
//        int lux = veml.readLux();
//        int lux_corr = 6.0135e-13*pow(lux,4)-9.3924e-9*pow(lux,3)+8.1488e-5*pow(lux,2)+1.0023*lux;
//        printf("Lux_corr: "); 
//        printf("%d\n", lux_corr);
//        printf("Lux: ");
//        printf("%d\n", lux);
//        delay(1000); // Change delay as needed
//
//        display.setTextSize(1);
//        delay(100);
//        display.setTextColor(BLACK);
//        delay(100);
//        display.setCursor(10,10);
//        delay(100);
//        display.println("Welcome!");
//        printf("Welcome xd\n");
//        delay(100);
//        display.display();
//        delay(100);
//    }
//}

/*
Formulas to calculate values:
https://www.hackster.io/alankrantas/ardumeter-arduino-incident-light-meter-606f63
NOTE* Need to switch to I2C communication between ESP32 and LCD!!
NOTE* Hardware upgrade for better measurement: BH1745
NOTE* Potential display Grafikus LCD kijelző 84x48 - Nokia 5110
NOTE* Mikrokapcsolok hestorebol - kis sapkákkal kitben pcb-vel stb...
*/

#include "Arduino.h"
#include "Print.h"
#include "esp32-hal-gpio.h"
#include "esp_attr.h"
#include "esp_err.h"
#include "hal/gpio_types.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <sys/_stdint.h>
#include <SPI.h>
#include <Adafruit_VEML7700.h>
#include <pins_arduino.h>
#include <Adafruit_SSD1306.h>

extern "C"
{
    #include <math.h>
    #include <stdio.h>
    #include <freertos/FreeRTOS.h>
    #include <freertos/task.h>
    #include "freertos/portmacro.h"
    #include "esp_wifi.h"
    #include "esp_sleep.h"
}

extern "C"
{
    void app_main(void);
}

//Defining values
#define BTN_MEASURE 4
#define BTN_PLUS    2
#define BTN_MINUS   3
#define SDA 1
#define SCL 0
#define APERTURE_N 23
#define SHUTTER_N 19
#define ISO_N 26
#define INCIDENT_CALIBRATION 330
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

//Variables
Adafruit_VEML7700 veml = Adafruit_VEML7700();
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

long lux = 0U;
uint8_t g_btn_measure_state = 0U;
uint8_t g_btn_plus_state = 0U;
uint8_t g_btn_minus_state = 0U;
int16_t ev = 0U;
double shutter_calc = 0U;
RTC_DATA_ATTR uint8_t aperture_index = 6U;
RTC_DATA_ATTR uint8_t iso_index = 9U;
uint64_t sleep_counter = 0U;

double aperture_array[APERTURE_N] = {1.4, 1.7, 2, 2.4, 2.8, 3.3, 4, 4.8, 5.6, 6.7, 8, 9.5, 11, 13, 16, 19, 22, 27, 32, 38, 45, 54, 64};
double shutter_array[SHUTTER_N] = {-60, -30, -15, -8, -4, -2, -1, 2, 4, 8, 15, 30, 60, 125, 250, 500, 1000, 2000, 4000};
uint16_t iso_array[ISO_N] = {12, 16, 20, 25, 32, 40, 50, 64, 80, 100, 125, 160, 200, 250, 320, 400, 500, 640, 800, 1000, 1250, 1600, 2000, 2500, 3200, 6400};

void init()
{
    printf("Up and running!\n");

    printf("Measure button: %d, Plus button: %d, Minus button: %d\n", BTN_MEASURE, BTN_PLUS, BTN_MINUS);
    pinMode(BTN_MEASURE, INPUT_PULLDOWN);
    pinMode(BTN_PLUS, INPUT_PULLDOWN);
    pinMode(BTN_MINUS, INPUT_PULLDOWN);

    printf("Setting up the SDA: %d, and the SCL: %d pins.\n", SDA, SCL);
    Wire.begin(1, 0);

    printf("Setting up the VEML7700 sensor with 1/8 gain and 25ms integration time.\n");
    veml.begin();
    veml.setGain(VEML7700_GAIN_1_8);
    veml.setIntegrationTime(VEML7700_IT_25MS);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    printf("SSD1306 allocation failed");
    while(1);
    }

    display.clearDisplay();

    printf("All set up and done!\n");

    esp_deep_sleep_enable_gpio_wakeup(1 << BTN_MEASURE, ESP_GPIO_WAKEUP_GPIO_HIGH);

    for (int i = 0; i < SHUTTER_N; i++) {
      if (shutter_array[i] < 0) {
        shutter_array[i] = 1 / abs(shutter_array[i]);
      }
    }

}

void read_btns()
{
    g_btn_measure_state = digitalRead(BTN_MEASURE);
    g_btn_plus_state = digitalRead(BTN_PLUS);
    g_btn_minus_state = digitalRead(BTN_MINUS);
}

void settings()
{
    if(g_btn_plus_state && iso_index < ISO_N - 1)
    {
        iso_index++;
        printf("ISO: %d\n", iso_index);
        sleep_counter = 0U;
        delay(200);
    }

    if(g_btn_minus_state && iso_index > 0)
    {
        iso_index--;
        printf("ISO: %d\n", iso_index);
        sleep_counter = 0U;
        delay(200);
    }
}

void make_measurement(uint8_t iso_setting, uint8_t aperture_setting)
{
    printf("ISO: %d\n", iso_array[iso_setting]);

    printf("Aperture: %f\n", aperture_array[aperture_setting]);

    lux = veml.readLux(VEML_LUX_CORRECTED);
    printf("LUX: %ld\n", lux);

    ev = log10(lux * iso_array[iso_setting] / INCIDENT_CALIBRATION) / log10(2);
    printf("EV: %d\n", ev);

    shutter_calc = (pow(2, ev) / pow(aperture_array[aperture_setting], 2));

    for (int i = 0; i < SHUTTER_N; i++) {
        
        if (shutter_calc >= shutter_array[i] && shutter_calc <= shutter_array[i + 1]) 
        {
        
        if (abs(shutter_calc - shutter_array[i]) <= abs(shutter_calc) - shutter_array[i + 1]) 
        {
            shutter_calc = shutter_array[i];
        } 
        
        else 
        {
            shutter_calc = shutter_array[i + 1];
        }
        
        break;
        
        }
    }
    if(shutter_calc > 1)
    {
        printf("Shutter: 1/%f\n", shutter_calc);
    }
    else 
    {
        printf("Shutter: %f\n",  1 / shutter_calc);
    }
    delay(100);
}

void sample_text()
{
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0,0);
    display.print("I:");
    display.print(iso_array[iso_index]);

    display.setCursor(0,8);
    display.print("F:");
    display.print(aperture_array[aperture_index]);

    display.setCursor(0,16);
    display.print("L:");
    display.print(lux);

    display.setCursor(0,24);
    display.print("E:");
    display.print(ev);

    display.setTextSize(2);
    display.setCursor(43,0);
    display.print("Shutter");
    display.setCursor(43,16);
    if(shutter_calc > 1)
    {
        display.print("1/");
        display.print(static_cast<int>(shutter_calc));
        display.setTextSize(1);
        display.print("s");
    }
    else 
    {
        display.print(static_cast<int>(1 / shutter_calc));
        display.setTextSize(1);
        display.print("s");
    }

    display.display();
    delay(100);  // Pause for 2 seconds
    display.clearDisplay();  // Clear the buffer
}

void sleep()
{
    sleep_counter++;
    delay(10);
    if(sleep_counter >= 200)
    {
        sleep_counter = 0U;
        printf("Going to sleep...\n");
        delay(50);
        display.clearDisplay();
        display.display();
        esp_deep_sleep_start();
    }
}

void app_main(void)
{
    init();
    read_btns();
    make_measurement(iso_index, aperture_index);

    while(1)
    {
        read_btns();
        settings();
        sample_text();
        if(g_btn_measure_state)
        {
            make_measurement(iso_index, aperture_index);
            sleep_counter = 0U;
        }
        sleep();
    }
}

/*
TO DO:
2 nyomógombot berakni h lehessen állítani az iso-t és az aperturet :D
hestore várom a rendelést
iso set overflow fix!!!! a button measure funkcioban
*/