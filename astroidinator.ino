/**
 * A template for using serial stuff with arduino
 *
 * @date 2019-02-11
 * @author duncte123
 * @version 1
 */

#include <Arduino.h>

#define SERIAL_RATE 115200
#define ENABLE_DEBUG true

LiquidCrystal_I2C astroidinatorLcd(0x27, 20, 4)

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

}

void writeToLcd(int a_x, int a_y, String a_text, bool a_clear) {
    int m_length = a_text.length();
    String m_singleLetter;

    if (a_clear) {
        astroidinatorLcd.clear();
    }

    astroidinatorLcd.setCursor(a_x, a_y);

    for (int m_index = 0; m_index < m_length; m_index++) {
        astroidinatorLcd.print(a_text[m_index]);
    }
}

void writeToLcd(int a_x, int a_y, String a_text) {
    writeToLcd(a_x, a_y, a_text, false);
}

void loop() {

}