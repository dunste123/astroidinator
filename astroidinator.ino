/**
 * A template for using serial stuff with arduino
 *
 * @date 2019-02-11
 * @author duncte123
 * @version 1
 */

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleTimer.h>

#define SERIAL_RATE 115200
#define ENABLE_DEBUG true

#define JOY_MOVE A0
#define JOY_KEY 8

LiquidCrystal_I2C astroidinatorLcdDSte(0x3F, 20, 4); // 0x27 or 0x3F
SimpleTimer timerDSte;

// Globals

typedef struct {
    int xPos = 0;
    int yPos = 1;
    String type = "}";
} PlayerDSte;

typedef struct {
    int xPos = random(20, 80);
    int yPos = random(0, 3);
    String type;
} UFODSte;

UFODSte asteroidsDSte[10];
UFODSte spaceShipsDSte[10];
PlayerDSte playerDSte;

void printLn(const String& a_inputString) {
#if ENABLE_DEBUG
    Serial.println(a_inputString);
#endif
}

void writeToLcdDSte(int a_x, int a_y, String a_text, bool a_clear) {
    if (a_clear) {
        astroidinatorLcdDSte.clear();
    }

    if (a_x > 20 || a_y > 4 || a_x < 0 || a_y < 0) {
        return;
    }

    astroidinatorLcdDSte.setCursor(a_x, a_y);

    int m_length = a_text.length();

    for (int m_index = 0; m_index < m_length; m_index++) {
        astroidinatorLcdDSte.print(a_text[m_index]);
    }
}

void writeToLcdDSte(int a_x, int a_y, const String &a_text) {
    writeToLcdDSte(a_x, a_y, a_text, false);
}

void initSerialDSte() {
#if ENABLE_DEBUG
    Serial.begin(SERIAL_RATE);
    printLn("READY: Serial initialized");
#endif
}

void showCreatorDSte() {
    writeToLcdDSte(0, 0, "Created by:");
    writeToLcdDSte(0, 1, "duncte123");
    delay(2000);
}

void clearLcdDSte() {
    writeToLcdDSte(0, 0, "", true);
}

void initPinsDSte() {
    pinMode(JOY_KEY, INPUT_PULLUP);
}

void createObjectsDSte() {
    for (auto &asteroid : asteroidsDSte) {
        asteroid.type = "a";
    }

    for (auto &spaceShip : spaceShipsDSte) {
        spaceShip.type = "s";
    }
}

bool collisionDetectedDSte(const PlayerDSte &player, const UFODSte &item) {

    if (player.xPos == item.xPos && player.yPos == item.yPos) {
        printLn("Collision with " + item.type);

        return true;
    }

    return false;
}

void checkControllerDSte() {
    int joyDSte = analogRead(JOY_MOVE);
    int mappedDSte = map(joyDSte, 0, 1023, 0, 255);

    if (mappedDSte > 150) {
        playerDSte.yPos++;
    } else if (mappedDSte < 100) {
        playerDSte.yPos--;
    }

    if (playerDSte.yPos > 3) {
        playerDSte.yPos = 3;
    }

    if (playerDSte.yPos < 0) {
        playerDSte.yPos = 0;
    }
}

void moveObjectsDSte() {
    clearLcdDSte();

    for (auto &asteroid : asteroidsDSte) {
        asteroid.xPos--;
        writeToLcdDSte(asteroid.xPos, asteroid.yPos, asteroid.type);

        if (collisionDetectedDSte(playerDSte, asteroid)) {
            //
        }
    }

    for (auto &spaceShip : spaceShipsDSte) {
        spaceShip.xPos--;
        writeToLcdDSte(spaceShip.xPos, spaceShip.yPos, spaceShip.type);

        if (collisionDetectedDSte(playerDSte, spaceShip)) {
            //
        }
    }

    writeToLcdDSte(playerDSte.xPos, playerDSte.yPos, playerDSte.type);
}

void updateScoresDSte() {
    //
}

void tickDSte() {
    checkControllerDSte();
    moveObjectsDSte();
}

void initTimerDSte() {
    timerDSte.setInterval(250, tickDSte);
}

void setup() {

    astroidinatorLcdDSte.init();
    astroidinatorLcdDSte.setBacklight(1);

    initPinsDSte();
    initSerialDSte();
    showCreatorDSte();
    clearLcdDSte();
    createObjectsDSte();
    moveObjectsDSte();
    initTimerDSte();
}

void loop() {
//    int joy = analogRead(JOY_MOVE);
//    int key = digitalRead(JOY_KEY);
//    checkController();
    timerDSte.run();
}
