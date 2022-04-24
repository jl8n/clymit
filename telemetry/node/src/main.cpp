#include <Adafruit_BME280.h>   // sensor
#include <Adafruit_GFX.h>      // gfx library for display
#include <Adafruit_SSD1306.h>  // display
#include <SPI.h>
#include <Wire.h>
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_SSD1306 display(-1);
Adafruit_BME280 bme;

String getTemp(char tempScale) {
    float celsius = bme.readTemperature();

    if (tempScale == 'c')
        return (String)celsius + "\176C ";
    else if (tempScale == 'f')
        return (String)((celsius * 9.0 / 5.0) + 32.0) + "\176F ";
    return "temp error";
}

String getHumid() {
    float humidity = bme.readHumidity();
    int humidity_i = (int)humidity;
    return (String)humidity_i + "%  ";
}

String getPressure() {
    float pressure = bme.readPressure();
    int pressure_i = (int)pressure;
    return (String)pressure_i + " Pa";
}

bool initSensor() {
    if (!bme.begin(0x76)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        throw "BME280 sensor was not found";
        return false;
    }
    return true;
}

void initDisplay() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // display uses I2C addr 0x3C
}

void handleError(String error) {
    String line2 = "Error! " + error;

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    display.println();
    display.println(line2);
    display.println();
    display.println();

    display.display();
}

void setup() {
    Serial.begin(9600);

    try {
        initDisplay();
        initSensor();
    } catch (String error) {
        handleError(error);
    }
}

void loop() {
    String line1 = getTemp('f') + getHumid() + getPressure();
    String line2 = getTemp('c');
    String line3 = "";
    String line4 = "";

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    display.println(line1);
    display.println(line2);
    display.println(line3);
    display.println(line4);
    Serial.println(line1);

    display.display();
    delay(2000);
    display.clearDisplay();
}