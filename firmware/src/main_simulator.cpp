#include <Arduino.h>

// ============ SIMULATOR MODE ============
#define SIMULATOR_MODE 1 // Set to 0 for real hardware

// ============ PIN DEFINITIONS ============
const int LIGHT_SENSOR_1 = 36; // Analog input for light sensor 1
const int LIGHT_SENSOR_2 = 39; // Analog input for light sensor 2
const int TEMP_SENSOR = 34;    // Analog input for temperature sensor
const int SOIL_HUMIDITY = 35;  // Analog input for soil humidity
const int WATER_LEVEL = 32;    // Analog input for water level
const int WATER_PUMP = 25;     // Digital output for water pump control

// ============ SENSOR DATA STRUCTURE ============
struct SensorData
{
    float light1;
    float light2;
    float temperature;
    float soilHumidity;
    float waterLevel;
    bool pumpStatus;
    uint32_t timestamp;
};

// ============ GLOBAL VARIABLES ============
SensorData currentData;
bool pumpEnabled = false;
uint32_t lastReadTime = 0;
const uint32_t READ_INTERVAL = 2000; // Read sensors every 2 seconds

// ============ FUNCTION DECLARATIONS ============
void readSensors(SensorData &data);
void controlPump(bool state);
void printSensorData(const SensorData &data);
void checkAutoWatering();

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("\n\n╔════════════════════════════════════════╗");
    Serial.println("║  GreenerDays - Plant Monitor Simulator ║");
    Serial.println("║  Heltec WiFi LoRa 32 V2 (ESP32)        ║");
    Serial.println("╚════════════════════════════════════════╝\n");

    // Initialize pins
    pinMode(WATER_PUMP, OUTPUT);
    digitalWrite(WATER_PUMP, LOW);

    // Configure ADC
    analogSetAttenuation(ADC_11db);

    Serial.println("[SETUP] Pins initialized");
    Serial.println("[SETUP] Running in SIMULATOR MODE");
    Serial.println("[SETUP] Use potentiometers to adjust sensor values");
    Serial.println("[SETUP] Monitor will be updated every 2 seconds\n");

    delay(2000);
}

void loop()
{
    uint32_t currentTime = millis();

    // Read sensors at regular intervals
    if (currentTime - lastReadTime >= READ_INTERVAL)
    {
        lastReadTime = currentTime;

        // Read all sensors
        readSensors(currentData);

        // Print data to serial
        printSensorData(currentData);

        // Check water level and auto-control pump
        checkAutoWatering();
    }

    delay(100); // Small delay to prevent overwhelming the serial
}

// ============ IMPLEMENTATION ============

void readSensors(SensorData &data)
{
    // Read analog sensors (0-4095 range for ESP32)
    int raw_light1 = analogRead(LIGHT_SENSOR_1);
    int raw_light2 = analogRead(LIGHT_SENSOR_2);
    int raw_temp = analogRead(TEMP_SENSOR);
    int raw_humidity = analogRead(SOIL_HUMIDITY);
    int raw_water = analogRead(WATER_LEVEL);

    // Convert raw values to meaningful data
    // Mapping: 0-4095 → actual values
    data.light1 = (raw_light1 / 4095.0) * 100.0;          // 0-100% light
    data.light2 = (raw_light2 / 4095.0) * 100.0;          // 0-100% light
    data.temperature = 15.0 + (raw_temp / 4095.0) * 30.0; // 15-45°C
    data.soilHumidity = (raw_humidity / 4095.0) * 100.0;  // 0-100% humidity
    data.waterLevel = (raw_water / 4095.0) * 100.0;       // 0-100% water
    data.pumpStatus = digitalRead(WATER_PUMP) == HIGH;
    data.timestamp = millis();
}

void controlPump(bool state)
{
    digitalWrite(WATER_PUMP, state ? HIGH : LOW);
    pumpEnabled = state;

    Serial.print("[PUMP] ");
    Serial.println(state ? "✓ ON - Watering plant" : "✗ OFF - Idle");
}

void printSensorData(const SensorData &data)
{
    Serial.println("\n┌─────────────────────────────────────┐");
    Serial.println("│        SENSOR READINGS               │");
    Serial.println("├─────────────────────────────────────┤");

    // Light sensors
    Serial.print("│ ☀️  Light 1:      ");
    Serial.print(data.light1, 1);
    Serial.println(" %              │");

    Serial.print("│ ☀️  Light 2:      ");
    Serial.print(data.light2, 1);
    Serial.println(" %              │");

    // Temperature
    Serial.print("│ 🌡️  Temperature:  ");
    Serial.print(data.temperature, 1);
    Serial.println(" °C           │");

    // Soil humidity
    Serial.print("│ 💧 Soil Humidity: ");
    Serial.print(data.soilHumidity, 1);
    Serial.println(" %              │");

    // Water level
    Serial.print("│ 💦 Water Level:   ");
    Serial.print(data.waterLevel, 1);
    Serial.println(" %              │");

    // Pump status
    Serial.print("│ 💨 Pump:          ");
    Serial.println(data.pumpStatus ? "ON ✓              │" : "OFF              │");

    Serial.printf("│ ⏱️  Uptime:        %u ms          │\n", data.timestamp);
    Serial.println("└─────────────────────────────────────┘");
}

void checkAutoWatering()
{
    // Auto-watering logic: turn on pump if soil humidity is too low
    // This is just an example - adjust thresholds as needed

    static uint32_t pumpOnTime = 0;
    const uint32_t PUMP_RUN_TIME = 5000;   // Run pump for 5 seconds max
    const float HUMIDITY_THRESHOLD = 40.0; // Turn on if below 40%

    if (currentData.soilHumidity < HUMIDITY_THRESHOLD && !pumpEnabled)
    {
        // Soil is dry, turn on pump
        controlPump(true);
        pumpOnTime = millis();
        Serial.println("\n[AUTO] 🚰 Soil humidity low - Starting automatic watering\n");
    }
    else if (pumpEnabled && (millis() - pumpOnTime > PUMP_RUN_TIME))
    {
        // Pump has been on long enough, turn it off
        controlPump(false);
        Serial.println("\n[AUTO] ⏱️  Pump timeout - Stopping automatic watering\n");
    }
    else if (currentData.soilHumidity > 70.0 && pumpEnabled)
    {
        // Soil is wet enough, turn off pump
        controlPump(false);
        Serial.println("\n[AUTO] ✓ Soil humidity optimal - Stopping pump\n");
    }
}

// ============ SERIAL COMMANDS ============
// You can send commands via Serial Monitor to test pump control

void serialEvent()
{
    while (Serial.available())
    {
        String command = Serial.readStringUntil('\n');
        command.toLowerCase();

        if (command == "pump on")
        {
            controlPump(true);
        }
        else if (command == "pump off")
        {
            controlPump(false);
        }
        else if (command == "help")
        {
            Serial.println("\n📋 Available Commands:");
            Serial.println("  pump on  - Turn water pump ON");
            Serial.println("  pump off - Turn water pump OFF");
            Serial.println("  help     - Show this menu\n");
        }
        else if (command != "")
        {
            Serial.println("Unknown command. Type 'help' for options.");
        }
    }
}
