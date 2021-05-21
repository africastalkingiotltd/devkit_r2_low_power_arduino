#include "STM32LowPower.h"

#define ENABLE_CLOCK_WAKEUP  0  // Wake up via RTC
#define ENABLE_SERIAL_WAKEUP 1 // Wake up device via Serial

#define LED_PIN PC13

volatile int wakeup_counter = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);

    LowPower.begin();

    if (ENABLE_SERIAL_WAKEUP)
    {
        LowPower.enableWakeupFrom(&Serial, WakeUpCallback); // What to do when you wake up
        Serial.println("Start deep sleep wakeup from Serial");
    }
}

void loop()
{
    if (ENABLE_SERIAL_WAKEUP)
    {
        Serial.print(wakeup_counter);
        Serial.println(" wake up");
        LowPower.deepSleep();
    }
    else if (ENABLE_CLOCK_WAKEUP)
    {
        Serial.println("LED on about to sleep");
        digitalWrite(LED_PIN, HIGH);
        LowPower.deepSleep(5000);
        digitalWrite(LED_PIN, LOW);
        Serial.println("Done sleeping");
        delay(1000);
    }
    while (Serial.available())
    {
        char c = Serial.read();
        Serial.print(c);
    }
}

void WakeUpCallback()
{
    wakeup_counter++;
}