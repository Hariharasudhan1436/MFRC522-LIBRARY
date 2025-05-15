# MFRC522-LIBRARY
# MFRC522 RFID Reader Library for Raspberry Pi Pico

This is a reusable C++ library for interfacing the MFRC522 RFID reader over SPI with Raspberry Pi Pico.

## 🔧 Features
- SPI communication with MFRC522 (1 MHz)
- Detect RFID tag presence
- Read UID of scanned tags/cards
- Modular and reusable Pico SDK C++ code

## 🛠️ Connections

| MFRC522 Pin | Pico Pin |
|-------------|-----------|
| SDA (SS)    | GPIO 5    |
| SCK         | GPIO 2    |
| MOSI        | GPIO 3    |
| MISO        | GPIO 4    |
| RST         | GPIO 6    |
| 3.3V        | 3.3V      |
| GND         | GND       |

## 🧪 Sample Output
MFRC522 RFID Reader Initialized.
Card UID: 3A 4F 92 01 6C


## 📦 Build

```bash
mkdir build
cd build
cmake ..
make

Copy the .uf2 file to the Pico, open serial monitor at 115200 baud, and scan an RFID card!

📜 License
MIT

---

Let me know if you'd like a `.zip` of the whole folder, or help uploading it to GitHub!
