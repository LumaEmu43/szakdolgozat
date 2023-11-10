/*
Papp Lukács Lóránt
WOW6MU
ESP-32c3 based light meter for analog cameras

Parallel wiring of LCD:

LCD PORT            GPIO

RS          ->      2
E           ->      3
D4          ->      8
D5          ->      5
D6          ->      6
D7          ->      7

BH1750 I2C wiring:

BH1750 PORT         GPIO

SDA         ->      0
SCL         ->      1

Available options in most cameras:

Full and half stops:
1.4, 1.7, 2, 2.4, 2.8, 3.3, 4, 4.8, 5.6, 6.7, 8, 9.5, 11, 13, 16, 19, 22, 27, 32, 38, 45, 54, 64

Most common film speeds (ASA/ISO):
12, 16, 20, 25, 32, 40, 50, 64, 80, 100, 125, 160, 200, 250, 320, 400, 500, 640, 800, 1000, 1250, 1600, 2000, 2500, 3200, 6400

Shutter speeds in seconds:
1, 1/2, 1/4, 1/8, 1/15, 1/30, 1/60, 1/125, 1/250, 1/500, 1/1000, 1/2000, 1/4000, 1/8000

EV = log10(lux * iso / INCIDENT_CALIBRATION) / log10(2);

double shutterspeed = (pow(2, EV) / pow(aperature, 2));
*/

#include "esp32-hal-gpio.h"
#include "esp_err.h"
#include "hal/gpio_types.h"
#include <LiquidCrystal.h>
#include <Wire.h>
#include <BH1750.h>
#include <sys/_stdint.h>

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


//Defining constants
#define APERTURE_N 23     //Number of full and half F-stops
#define ISO_N 26        //Number of most common ISO/ASA values
#define SHUTTER_N 19    //Number of possible shutter speeds
#define INCIDENT_CALIBRATION 330    //330 Calibration constant (C) for incident light meters, see https://en.wikipedia.org/wiki/Light_meter#Calibration_constants
#define BTN_MEASURE 4


//Defining objects
BH1750 lightMeter;      //Light meter sensor using the BH1750 library (might change later)
LiquidCrystal lcd(2, 3, 8, 5, 6, 7);    //LCD initialization (might change later due to I2C)

//Defining variables
long lux = 0.0;    //Measured LUX value
int8_t exposure_value = 0;
uint64_t wait = 0;
int16_t shutter_speed_calculated = 0;

double aperture_array[APERTURE_N] = {1.4, 1.7, 2, 2.4, 2.8, 3.3, 4, 4.8, 5.6, 6.7, 8, 9.5, 11, 13, 16, 19, 22, 27, 32, 38, 45, 54, 64};
double shutter_speed_array[SHUTTER_N] = {-60, -30, -15, -8, -4, -2, -1, 2, 4, 8, 15, 30, 60, 125, 250, 500, 1000, 2000, 4000};
int iso_array[ISO_N] = {12, 16, 20, 25, 32, 40, 50, 64, 80, 100, 125, 160, 200, 250, 320, 400, 500, 640, 800, 1000, 1250, 1600, 2000, 2500, 3200, 6400};

void init()
{
    esp_wifi_stop();

    Wire.setPins(0, 1);
    Wire.begin();
    lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2);

    lcd.begin(16, 2);
    lcd.print("Shutter:");

    esp_deep_sleep_enable_gpio_wakeup(1 << BTN_MEASURE, ESP_GPIO_WAKEUP_GPIO_HIGH);

    pinMode(BTN_MEASURE, INPUT);
}

void make_measurement(bool init)
{
    if(digitalRead(BTN_MEASURE) | init)
        {
            lux = lightMeter.readLightLevel();
            exposure_value = log10(lux * iso_array[25] / INCIDENT_CALIBRATION) / log10(2);
            shutter_speed_calculated = (pow(2, exposure_value) / pow(aperture_array[4], 2));

            for (int i = 0; i < (sizeof(shutter_speed_array) / sizeof(double)) - 1; i++) {
                if (shutter_speed_calculated >= shutter_speed_array[i] && shutter_speed_calculated <= shutter_speed_array[i + 1]) {
                if (abs(shutter_speed_calculated - shutter_speed_array[i]) <= abs(shutter_speed_calculated) - shutter_speed_array[i + 1]) {
                    shutter_speed_calculated = shutter_speed_array[i];
                } else {
                    shutter_speed_calculated = shutter_speed_array[i + 1];
                }
                break;
                }
            }

            printf("Current LUX value: %ld; ", lux);
            printf("Current film speed: %d; ", iso_array[25]);
            printf("Current f-stop: %f; ", aperture_array[4]);
            printf("Calculated shutter speed is: 1/%d; ", shutter_speed_calculated);
            printf("Exposure Value is: %d\n", exposure_value);

            wait = 0;

            delay(100);

            lcd.setCursor(0, 1);
            lcd.print("1/" + String(shutter_speed_calculated));

            delay(500);
        }
}

void go_to_sleep(uint16_t sleep)
{
    wait++;
    if(wait >= sleep)
    {
        printf("Going to sleep...\n");
        delay(50);
        esp_deep_sleep_start();
    }
}

void app_main(void)
{
    
    init();
    make_measurement(true);
    
    while(1)
    {
        make_measurement(false);
        delay(100);
        go_to_sleep(600);
    }
}

/*
Formulas to calculate values:
https://www.hackster.io/alankrantas/ardumeter-arduino-incident-light-meter-606f63
NOTE* Need to switch to I2C communication between ESP32 and LCD!!
NOTE* Hardware upgrade for better measurement: BH1745
NOTE* Potential display Grafikus LCD kijelző 84x48 - Nokia 5110
NOTE* Mikrokapcsolok hestorebol - kis sapkákkal kitben pcb-vel stb...
*/