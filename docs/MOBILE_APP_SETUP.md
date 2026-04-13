# Mobile App Development Guide

## Project Setup

### Prerequisites
- Flutter SDK installed
- Xcode (for iOS) or Android Studio (for Android)
- Firebase account

### Initialize Flutter Project

```bash
cd mobile-app
flutter create --org com.greenerdays greener_days
cd greener_days
```

## Project Structure

```
mobile-app/greener_days/
├── lib/
│   ├── main.dart
│   ├── screens/
│   │   ├── home_screen.dart
│   │   ├── plant_detail_screen.dart
│   │   └── settings_screen.dart
│   ├── services/
│   │   └── firebase_service.dart
│   ├── models/
│   │   └── plant_data.dart
│   └── widgets/
│       ├── sensor_card.dart
│       └── pump_control.dart
├── pubspec.yaml
└── pubspec.lock
```

## Dependencies

Update `pubspec.yaml`:

```yaml
dependencies:
  flutter:
    sdk: flutter
  firebase_core: ^latest
  firebase_database: ^latest
  firebase_auth: ^latest
  provider: ^latest
  charts_flutter: ^latest
  intl: ^latest
  http: ^latest
  fl_chart: ^latest

dev_dependencies:
  flutter_test:
    sdk: flutter
```

## Architecture

### Models (`lib/models/plant_data.dart`)

```dart
class PlantData {
  double light1;
  double light2;
  double temperature;
  double soilHumidity;
  double waterLevel;
  bool pumpStatus;
  DateTime timestamp;
  
  PlantData({
    required this.light1,
    required this.light2,
    required this.temperature,
    required this.soilHumidity,
    required this.waterLevel,
    required this.pumpStatus,
    required this.timestamp,
  });
}
```

### Firebase Service (`lib/services/firebase_service.dart`)

Handle all Firebase operations:
- Real-time data listeners
- Device pairing
- Pump control commands
- User authentication

### Screens

1. **Home Screen** - Dashboard with real-time sensor data
2. **Plant Detail Screen** - Detailed graphs and history
3. **Settings Screen** - Device configuration and notifications

## UI Components

### Sensor Cards
Display real-time sensor readings with:
- Current value
- Min/Max values
- Visual indicator (gauge or color coding)
- Last update time

### Pump Control
Simple button/toggle to:
- Turn pump on/off
- Show pump status
- Confirm actions

### Data Visualization
- Line charts for temperature trends
- Gauge charts for humidity levels
- Multi-series charts for comparison

## Firebase Integration

### Real-time Listeners

```dart
listen() {
  FirebaseDatabase.instance
    .ref('plant-data')
    .onValue.listen((event) {
      final data = event.snapshot.value;
      updateUI(data);
    });
}
```

### Pump Control

```dart
controlPump(bool state) async {
  await FirebaseDatabase.instance
    .ref('plant-data/pumpStatus')
    .set(state);
}
```

## Development Workflow

1. **Design Phase**: Create wireframes for each screen
2. **Model Phase**: Define data models
3. **Service Phase**: Implement Firebase service
4. **UI Phase**: Build screens and widgets
5. **Integration Phase**: Connect services to UI
6. **Testing Phase**: Test on real devices

## Testing

Run on emulator/device:

```bash
flutter pub get
flutter run        # Debug mode
flutter run -v     # Verbose logging
```

## Building for Release

### iOS
```bash
flutter build ios --release
# Open in Xcode and upload to App Store
```

### Android
```bash
flutter build apk --release
flutter build appbundle --release
# Upload to Google Play
```

## Common Features to Implement

- [ ] Real-time sensor dashboard
- [ ] Historical data charts
- [ ] Automatic watering triggers
- [ ] Push notifications
- [ ] Device pairing/setup wizard
- [ ] Data export (CSV)
- [ ] Dark mode support
- [ ] Offline data caching

## Performance Tips

- Use StreamBuilder for real-time updates
- Implement data pagination for history
- Cache data locally with Hive or Shared Preferences
- Optimize chart rendering
- Use image optimization for plant photos
