#include <Wire.h>
#include <Adafruit_PN532.h>
#include <ESP32Servo.h>

// PIN DEFINITIONS
#define SDA_PIN 21  // pins for the pn532
#define SCL_PIN 22

#define PHOTO_PIN 15      // photoresistor analog input
#define SERVO_PIN 18      // servo control input

// CONSTANTS
const int POLL_EVERY = 2500;  // how often to poll the pn532
// lower = less energy but longer response time

Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

Servo lockServo;
const int SERVO_LOCKED = 20;     // adjust
const int SERVO_UNLOCKED = 90;  // adjust

const unsigned long DRAWER_CLOSE_TIME = 10000; // 10 seconds of dark before it closes

const int LIGHT_THRESHOLD = 1800;  // adjust too
// Above this = drawer open
// Below this = drawer closed

// AUTHORIZED UID
// Replace with your card UID
uint8_t allowedUID[] = {0xDE, 0xAD, 0xBE, 0xEF};
const uint8_t allowedUIDLength = 4;

// VARIABLES
bool drawerOpen = false;
unsigned long lightLowStart = 0;
bool lightTiming = false;


void setup() {
  Serial.begin(115200);

  // I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // Servo
  lockServo.attach(SERVO_PIN);
  lock();

  // NFC init
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.println("PN532 not found");
    while (1) delay(1000);
  }

  nfc.setPassiveActivationRetries(0x00);  // try only once to read the card
  nfc.SAMConfig(); // configure to read rfid tags
  Serial.println("PN532 ready.");

  analogReadResolution(12);
}

void loop() {
  if (!drawerOpen) {
    wakePN532();
    checkNFC();
    sleepPN532();
    delay(POLL_EVERY);  // slow polling to reduce power
  } else {
    waitForDrawerClose();
  }
}

/* ================= FUNCTIONS ================= */

void sleepPN532() {
  // PN532 power‑down command
  uint8_t cmd[] = {0x16, 0x01};  
  if (nfc.sendCommandCheckAck(cmd, sizeof(cmd))) {
    Serial.println("PN532 powered down");
  } else {
    Serial.println("PowerDown failed");
  }
}

void wakePN532() {
  // simple wake by re‑begin
  nfc.begin();
  delay(10);  
  nfc.SAMConfig(); 
}

void checkNFC() {
  uint8_t uid[7];
  uint8_t uidLength;

  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
    if (isAuthorized(uid, uidLength)) {
      Serial.println("Authorized card found!");
      unlock();
    } else {
      Serial.println("Unauthorized card.");
    }
  }
}

bool isAuthorized(uint8_t *uid, uint8_t uidLength) {
  if (uidLength != allowedUIDLength) return false;

  for (uint8_t i = 0; i < uidLength; i++) {
    if (uid[i] != allowedUID[i]) return false;
  }
  return true;
}

void waitForDrawerClose() {
  int lightValue = analogRead(PHOTO_PIN);

  if (lightValue < LIGHT_THRESHOLD) {
    if (!lightTiming) {
      lightTiming = true;
      lightLowStart = millis();
    }

    if (millis() - lightLowStart >= DRAWER_CLOSE_TIME) {
      Serial.println("Drawer confirmed closed. Locking.");
      lock();
      lightTiming = false;
    }
  } else {
    lightTiming = false;  // light came back, reset timer
  }

  delay(250);
}

void unlock() {
  lockServo.write(SERVO_UNLOCKED);
  drawerOpen = true;
}

void lock() {
  lockServo.write(SERVO_LOCKED);
  drawerOpen = false;
}
