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

LiquidCrystal_I2C astroidinatorLcd(0x3F, 20, 4); // 0x27 or 0x3F
SimpleTimer timer;

// Globals

typedef struct {
    int xPos = 0;
    int yPos = 1;
    String type = "}";
} Player;

typedef struct {
    int xPos = random(20, 80);
    int yPos = random(0, 3);
    String type;
} UFO;

UFO asteroids[10];
UFO spaceShips[10];
Player player;

void printLn(const String& a_inputString) {
#if ENABLE_DEBUG
    Serial.println(a_inputString);
#endif
}

void writeToLcd(int a_x, int a_y, String a_text, bool a_clear) {
    if (a_clear) {
        astroidinatorLcd.clear();
    }

    if (a_x > 20 || a_y > 4 || a_x < 0 || a_y < 0) {
        return;
    }

    astroidinatorLcd.setCursor(a_x, a_y);

    int m_length = a_text.length();

    for (int m_index = 0; m_index < m_length; m_index++) {
        astroidinatorLcd.print(a_text[m_index]);
    }
}

void writeToLcd(int a_x, int a_y, const String &a_text) {
    writeToLcd(a_x, a_y, a_text, false);
}

void initSerial() {
#if ENABLE_DEBUG
    Serial.begin(SERIAL_RATE);
    printLn("READY: Serial initialized");
#endif
}

void showCreator() {
    writeToLcd(0, 0, "Created by:");
    writeToLcd(0, 1, "duncte123");
    delay(2000);
}

void clearLcd() {
    writeToLcd(0, 0, "", true);
}

void initPins() {
    pinMode(JOY_KEY, INPUT_PULLUP);
}

void createObjects() {
    for (auto &asteroid : asteroids) {
        asteroid.type = "a";
    }

    for (auto &spaceShip : spaceShips) {
        spaceShip.type = "s";
    }
}

bool collisionDetected(const Player &player, const UFO &item) {

    if (player.xPos == item.xPos && player.yPos == item.yPos) {
        printLn("Collision with " + item.type);

        return true;
    }

    return false;
}

void checkController() {
    int joy = analogRead(JOY_MOVE);
    int mapped = map(joy, 0, 1023, 0, 255);

    if (mapped > 150) {
        player.yPos++;
    } else if (mapped < 100) {
        player.yPos--;
    }

    if (player.yPos > 3) {
        player.yPos = 3;
    }

    if (player.yPos < 0) {
        player.yPos = 0;
    }
}

void moveObjects() {
    clearLcd();

    for (auto &asteroid : asteroids) {
        asteroid.xPos--;
        writeToLcd(asteroid.xPos, asteroid.yPos, asteroid.type);

        if (collisionDetected(player, asteroid)) {
            //
        }
    }

    for (auto &spaceShip : spaceShips) {
        spaceShip.xPos--;
        writeToLcd(spaceShip.xPos, spaceShip.yPos, spaceShip.type);

        if (collisionDetected(player, spaceShip)) {
            //
        }
    }

    writeToLcd(player.xPos, player.yPos, player.type);
}

void updateScores() {
    //
}

void tick() {
    checkController();
    moveObjects();
}

void initTimer() {
    timer.setInterval(250, tick);
}

void setup() {

    astroidinatorLcd.init();
    astroidinatorLcd.setBacklight(1);

    initPins();
    initSerial();
    showCreator();
    clearLcd();
    createObjects();
    moveObjects();
    initTimer();
}

void loop() {
//    int joy = analogRead(JOY_MOVE);
//    int key = digitalRead(JOY_KEY);
//    checkController();
    timer.run();
}
