#include <Wire.h>
#include <RTClib.h>

// initialize the RTC
RTC_DS3231 rtc; // might have to change this to the correct RTC module

// delcare the pinouts
const int LEDS = 12
const int hourPins[LEDS] = {} // declare hour pins here
const int minPins[LEDS] = {} // declare min pins here

// track the time
int currentHour = 0;
int currentMin = 0;

void setup() {
  Serial.begin(9600);

  if(!rtc.begin()) {
    Serial.println("Can't find the RTC");
    while (1);
  }

  // sets the RTC to the date and time the skectch is compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // loop for each hour pinout
  for (int i = 0; i < LEDS; i++) {
    pinMode(hourPins[i], OUTPUT)
    pinMode(minPins[i], OUTPUT)
  }

  turnOffAllLEDs();

}

void loop() {
  DateTime now = rtc.now();

  // convert to 12 hr and make midnight and noon 12
  int hour12 = now.hour() % 12;
  if (hour12 == 0) hour12 = 12;

  int minTime = now.minute() / 5;

  if (hour12 != currentHour || minTime != currentMin) {
    currentHour = hour12;
    currentMin = minTime;
    updateLEDs(currentHour, currentMin);

    Serial.print("Time: ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    if (now.minute() < 10) {
      Serial.print('0');
    }
    Serial.print(now.minute(), DEC);
    Serial.println();
  }
  
  delay(100);

}

void updateLEDs(int hour, int minTime) {
  // turn off all LEDs first
  turnOffAllLEDs();
  // turn on LED for current hour; subract 1 from 0 index array
  digitalWrite(ledPins[hour - 1], HIGH);

  for (int i = 0; i <= minTime; i++) {
    digitalWrite(minPins[i], HIGH)
  }
}

void LEDsoff() {
  for (int i = 0; i < hour_LEDS; i++) {
    digitalWrite(hourPins[i], LOW);
    digitalWrite(minPins[i], LOW);
  }
}
