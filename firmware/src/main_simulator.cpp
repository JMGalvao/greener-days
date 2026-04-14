#include <Arduino.h>

const int SOIL_HUMIDITY_PIN = 35;
const int WATER_PUMP_PIN = 25;

const uint32_t READ_INTERVAL_MS = 1000;
uint32_t lastReadMs = 0;
bool pumpOn = false;

void setPump(bool state)
{
    if (pumpOn == state)
    {
        return;
    }

    pumpOn = state;
    digitalWrite(WATER_PUMP_PIN, pumpOn ? HIGH : LOW);

    Serial.print("[PUMP] ");
    Serial.println(pumpOn ? "ON" : "OFF");
}

void setup()
{
    Serial.begin(115200);
    delay(300);

    pinMode(WATER_PUMP_PIN, OUTPUT);
    digitalWrite(WATER_PUMP_PIN, LOW);
    analogSetAttenuation(ADC_11db);

    Serial.println();
    Serial.println("GreenerDays simulator baseline");
    Serial.println("humidity pin: GPIO35, pump pin: GPIO25");
    Serial.println("rule: humidity < 40% => pump ON, > 70% => pump OFF");
}

void loop()
{
    uint32_t now = millis();
    if (now - lastReadMs < READ_INTERVAL_MS)
    {
        delay(10);
        return;
    }

    lastReadMs = now;

    int rawHumidity = analogRead(SOIL_HUMIDITY_PIN);
    float humidityPct = (rawHumidity / 4095.0f) * 100.0f;

    Serial.print("[SENSOR] raw=");
    Serial.print(rawHumidity);
    Serial.print(" humidity=");
    Serial.print(humidityPct, 1);
    Serial.print("% pump=");
    Serial.println(pumpOn ? "ON" : "OFF");

    if (humidityPct < 40.0f)
    {
        setPump(true);
    }
    else if (humidityPct > 70.0f)
    {
        setPump(false);
    }
}
