# GreenerDays - Smart Plant Monitoring System

A complete IoT solution for monitoring plants in garden pots using the Heltec WiFi LoRa 32 V2 (ESP32).

## 🌱 Project Overview

**GreenerDays** is a smart plant monitoring system that:
- Reads sensor data (light, temperature, soil humidity, water level)
- Controls a water pump automatically
- Stores data in the cloud
- Provides a mobile app (iOS/Android) for remote monitoring from anywhere

## 📁 Project Structure

```
greener-days/
├── firmware/           # ESP32 firmware (PlatformIO)
│   ├── src/           # Source code
│   ├── lib/           # Libraries
│   └── platformio.ini # PlatformIO configuration
├── mobile-app/        # Flutter mobile application
├── backend/           # Firebase cloud backend
├── docs/              # Project documentation
└── README.md
```

## 🛠️ Technology Stack

| Component | Technology | Purpose |
|-----------|-----------|---------|
| **Firmware** | Arduino/PlatformIO | ESP32 sensor reading & pump control |
| **Cloud** | Firebase Realtime DB | Data storage & real-time sync |
| **Mobile** | Flutter | iOS/Android monitoring app |
| **Communication** | REST API / Firebase SDK | Device ↔ Cloud ↔ Mobile |

## 📊 Sensors & Hardware

- **Light Sensors (2x)** - Monitor light levels
- **Temperature Sensor (1x)** - Track ambient temperature
- **Soil Humidity Sensor (1x)** - Soil moisture level
- **Water Level Sensor (1x)** - Tank/reservoir level
- **Water Pump (1x)** - Automatic watering control
- **Heltec WiFi LoRa 32 V2** - Main microcontroller (ESP32)

## 🚀 Getting Started

### 1. Firmware Development
```bash
cd firmware
# Install PlatformIO extension in VS Code
# Open platformio.ini and configure
# Upload code to ESP32
```

### 2. Backend Setup
Configure Firebase project for cloud data storage.

### 3. Mobile App
```bash
cd mobile-app
flutter create .
flutter pub get
flutter run
```

## 📱 Features (Roadmap)

- [x] Project structure created
- [ ] Firmware: Sensor reading implementation
- [ ] Firmware: Water pump control
- [ ] Firmware: WiFi connectivity
- [ ] Backend: Firebase setup
- [ ] Backend: REST API endpoints
- [ ] Mobile: Data visualization
- [ ] Mobile: Alert notifications
- [ ] Mobile: Pump control interface

## 📖 Documentation

See [docs/](docs/) for detailed guides:
- Hardware setup & wiring
- Firmware development
- Firebase configuration
- Mobile app development

## 👤 Author

Created for the GreenerDays project

## 📄 License

MIT License
