#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// ============ PIN DEFINITIONS ============
const int LIGHT_SENSOR_1 = 36; // Analog input for light sensor 1
const int LIGHT_SENSOR_2 = 39; // Analog input for light sensor 2
const int TEMP_SENSOR = 34;    // Analog input for temperature sensor
const int SOIL_HUMIDITY = 35;  // Analog input for soil humidity
const int WATER_LEVEL = 32;    // Analog input for water level
const int WATER_PUMP = 25;     // Digital output for water pump control

// ============ WiFi CREDENTIALS ============
const char *SSID = "YOUR_WIFI_SSID";
const char *PASSWORD = "YOUR_WIFI_PASSWORD";

// ============ SERVER CONFIGURATION ============
const char *SERVER_URL = "https://your-firebase-project.firebaseio.com";
const char *API_KEY = "YOUR_FIREBASE_API_KEY";

// ============ SENSOR DATA STRUCTURE ============
struct SensorData
{
    float light1;
    float light2;
    float temperature;
    float soilHumidity;
    float waterLevel;
    bool pumpStatus;
};

// ============ FUNCTION DECLARATIONS ============
void setupWiFi();
void readSensors(SensorData &data);
void sendDataToCloud(const SensorData &data);
void controlPump(bool state);
void printSensorData(const SensorData &data);

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("\n\nGreenerDays - Smart Plant Monitoring System");
    Serial.println("============================================");

    // Initialize pins
    pinMode(WATER_PUMP, OUTPUT);
    digitalWrite(WATER_PUMP, LOW);

    // Setup WiFi
    setupWiFi();

    Serial.println("Setup complete!");
}

void loop()
{
    SensorData data;

    // Read all sensors
    readSensors(data);

    // Print data to serial for debugging
    printSensorData(data);

    // Send data to cloud
    if (WiFi.status() == WL_CONNECTED)
    {
        sendDataToCloud(data);
    }
    else
    {
        Serial.println("WiFi disconnected");
    }

    // Wait 10 seconds before next read
    delay(10000);
}

// ============ IMPLEMENTATION ============

void setupWiFi()
{
    Serial.print("Connecting to WiFi: ");
    Serial.println(SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    Serial.println();
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.print("WiFi connected! IP: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("Failed to connect to WiFi");
    }
}

void readSensors(SensorData &data)
{
    // Read analog sensors (0-4095 range for ESP32)
    int raw_light1 = analogRead(LIGHT_SENSOR_1);
    int raw_light2 = analogRead(LIGHT_SENSOR_2);
    int raw_temp = analogRead(TEMP_SENSOR);
    int raw_humidity = analogRead(SOIL_HUMIDITY);
    int raw_water = analogRead(WATER_LEVEL);

    // Convert raw values to meaningful data
    // These conversions depend on your sensor specifications
    data.light1 = (raw_light1 / 4095.0) * 100.0;         // 0-100%
    data.light2 = (raw_light2 / 4095.0) * 100.0;         // 0-100%
    data.temperature = (raw_temp / 4095.0) * 50.0;       // 0-50°C (adjust for your sensor)
    data.soilHumidity = (raw_humidity / 4095.0) * 100.0; // 0-100%
    data.waterLevel = (raw_water / 4095.0) * 100.0;      // 0-100%
    data.pumpStatus = digitalRead(WATER_PUMP);
}

void sendDataToCloud(const SensorData &data)
{
    HTTPClient http;

    // Construct JSON payload
    String json = "{";
    json += "\"light1\":" + String(data.light1, 2) + ",";
    json += "\"light2\":" + String(data.light2, 2) + ",";
    json += "\"temperature\":" + String(data.temperature, 2) + ",";
    json += "\"soilHumidity\":" + String(data.soilHumidity, 2) + ",";
    json += "\"waterLevel\":" + String(data.waterLevel, 2) + ",";
    json += "\"pumpStatus\":" + (data.pumpStatus ? "true" : "false") + ",";
    json += "\"timestamp\":" + String(millis());
    json += "}";

    // Send data to server
    String url = String(SERVER_URL) + "/plant-data.json?auth=" + String(API_KEY);
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST(json);

    if (httpCode > 0)
    {
        Serial.print("HTTP Response: ");
        Serial.println(httpCode);
    }
    else
    {
        Serial.print("HTTP Error: ");
        Serial.println(http.errorToString(httpCode));
    }

    http.end();
}

void controlPump(bool state)
{
    digitalWrite(WATER_PUMP, state ? HIGH : LOW);
    Serial.print("Pump: ");
    Serial.println(state ? "ON" : "OFF");
}

void printSensorData(const SensorData &data)
{
    Serial.println("\n--- SENSOR DATA ---");
    Serial.print("Light 1: ");
    Serial.print(data.light1, 2);
    Serial.println("%");

    Serial.print("Light 2: ");
    Serial.print(data.light2, 2);
    Serial.println("%");

    Serial.print("Temperature: ");
    Serial.print(data.temperature, 2);
    Serial.println("°C");

    Serial.print("Soil Humidity: ");
    Serial.print(data.soilHumidity, 2);
    Serial.println("%");

    Serial.print("Water Level: ");
    Serial.print(data.waterLevel, 2);
    Serial.println("%");

    Serial.print("Pump Status: ");
    Serial.println(data.pumpStatus ? "ON" : "OFF");
    Serial.println("-------------------");
}
