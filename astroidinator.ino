/**
 * A template for using serial stuff with arduino
 *
 * @date 2019-02-11
 * @author duncte123
 * @version 1
 */

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define SERIAL_RATE 115200
#define ENABLE_DEBUG true

LiquidCrystal_I2C astroidinatorLcd(0x3F, 20, 4); // 0x27 or 0x3F

// Globals

void printLn(String a_inputString) {
#if ENABLE_DEBUG
    Serial.println(a_inputString);
#endif
}

void initSerial() {
    Serial.begin(SERIAL_RATE);
    printLn("READY: Serial initialized");
}

void showCreator() {
    printLn("Created by: Duncan \"duncte123\" Sterken");
}

void setup() {

    initSerial();
    showCreator();

    astroidinatorLcd.init();

    astroidinatorLcd.setBacklight(0);

    delay(1000);

    astroidinatorLcd.setBacklight(1);

    delay(1000);

    writeToLcd(0, 0, "Hello");
    writeToLcd(0, 1, "World");

}

void writeToLcd(int a_x, int a_y, String a_text, bool a_clear) {
    int m_length = a_text.length();

    if (a_clear) {
        astroidinatorLcd.clear();
    }

    astroidinatorLcd.setCursor(a_x, a_y);

    for (int m_index = 0; m_index < m_length; m_index++) {
        astroidinatorLcd.print(a_text[m_index]);
    }

    printLn(a_text);
}

void writeToLcd(int a_x, int a_y, String a_text) {
    writeToLcd(a_x, a_y, a_text, false);
}

void loop() {

}
