# 📡 IRremoteEsp32
Lightweight ESP32 IR remote library for capturing and sending raw pulse width data.

⚠️ This library uses PWM channel 0 of the ESP32.

Receive and send raw IR signals (pulse width) for devices like TVs, air conditioners, and possibly other IR-controlled electronics.

# 🔧 Configuration
Edit the definitions in IRRemote.h to match your hardware setup:

```cpp
#define IR_RECEIVER_PIN       5     // IR receiver pin
#define IR_TRANSMITTER_PIN    4     // IR LED transmitter pin
#define PULSE_WIDTH_VECTOR_SIZE 500 // Max size of pulse width array
#define MAXIMUM_GAP         50000   // Handles large gaps (e.g., in AC codes)

// PWM Configuration for sending IR at 38 kHz
#define PWM_CHANNEL          0
#define PWM_FREQ         38000
#define PWM_RESOLUTION       8
```

# 🚀 Getting Started

## 1️⃣ Create an object
```cpp
IRCode IRcode;
```

## 2️⃣ Setup in setup()
```cpp
void setup() {
  Serial.begin(115200);
  IRcode.begin();
}
```

## 3️⃣ Receive IR code easily
```cpp
IRcode.IRrecStart();
Serial.print("Waiting code:");
for (int i = 0; i < 10; i++) {
  Serial.print(".");
  delay(500);
}
IRcode.IRrecStop();
Serial.println("Acquisition end.");
```

## 4️⃣ Print received data
```cpp
IRcode.printPulseWidthVector();         // Print as durations
IRcode.printPulseWidthVectorinBinary(); // Print as binary signal
```
💡 Ensure Serial.begin(115200); is called in setup().

## 5️⃣ Send the IR code
```cpp
IRcode.IRsendRaw();
```
## 📊 Accessing raw data
The pulse widths (in microseconds) are stored in the array:
```cpp
IRcode.pulseWidthVector[]; // type: int
```

📁 Example structure
For a basic usage example, see the folder:
```swift
examples/IRremoteDemo/IRremoteDemo.ino
```
