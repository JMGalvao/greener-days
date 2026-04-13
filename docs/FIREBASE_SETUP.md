# Firebase Configuration Guide

## Prerequisites

1. Google account
2. Firebase project created at https://console.firebase.google.com

## Step 1: Create Firebase Project

1. Go to [Firebase Console](https://console.firebase.google.com)
2. Click "Add project"
3. Name it "GreenerDays"
4. Select your country/region
5. Create the project

## Step 2: Set Up Realtime Database

1. In Firebase Console, go to **Realtime Database**
2. Click **Create Database**
3. Choose **Start in test mode** (for development)
4. Select your region

## Step 3: Set Up Authentication

For better security, set up Firebase Authentication:

1. Go to **Authentication** → **Sign-in method**
2. Enable **Anonymous Authentication** (for testing)
3. Or enable **Email/Password** for your mobile app

## Step 4: Get Your Credentials

1. Go to **Project Settings** (gear icon)
2. Copy:
   - **Project ID**
   - **Database URL**
   - **API Key**

3. For the firmware (`main.cpp`), update:
```cpp
const char* SERVER_URL = "https://YOUR_PROJECT_ID.firebaseio.com";
const char* API_KEY = "YOUR_API_KEY";
```

## Step 5: Set Database Rules

Replace the default database rules with:

```json
{
  "rules": {
    "plant-data": {
      ".read": true,
      ".write": true
    },
    "users": {
      "$uid": {
        ".read": "$uid === auth.uid",
        ".write": "$uid === auth.uid"
      }
    }
  }
}
```

## Step 6: Database Structure

Your Realtime Database will have this structure:

```
greener-days-project/
├── plant-data/
│   ├── timestamp: 1234567890
│   ├── light1: 75.5
│   ├── light2: 82.3
│   ├── temperature: 24.5
│   ├── soilHumidity: 65.2
│   ├── waterLevel: 45.0
│   └── pumpStatus: true
└── users/
    └── $userId/
        ├── email: "user@example.com"
        ├── plantName: "My Plant"
        └── deviceId: "heltec-001"
```

## Step 7: Mobile App Firebase Setup

For Flutter, add Firebase dependencies:

```yaml
# pubspec.yaml
dependencies:
  firebase_core: ^latest
  firebase_database: ^latest
  firebase_auth: ^latest
```

## Testing the Connection

1. Upload firmware to ESP32
2. Check Serial Monitor (115200 baud)
3. Verify WiFi connection
4. Go to Firebase Console → Realtime Database → Data
5. You should see sensor data appearing in real-time!

## Security Notes

- The test mode rules are for development only
- Before production, implement proper authentication
- Restrict write access to authorized devices only
- Use Firebase Security Rules to validate data

## Troubleshooting

| Issue | Solution |
|-------|----------|
| Connection timeout | Check WiFi credentials and API key |
| 403 Forbidden error | Review Database Rules and permissions |
| Data not syncing | Check serial monitor for errors, verify JSON format |
| Slow updates | Increase interval between sends, check WiFi signal |
