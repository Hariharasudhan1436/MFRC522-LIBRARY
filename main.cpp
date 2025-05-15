#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "mfrc522.h"

#define SPI_PORT spi0
#define CS_PIN 5
#define RST_PIN 6

int main() {
    stdio_init_all();

    MFRC522 rfid(SPI_PORT, CS_PIN, RST_PIN);
    rfid.begin();

    printf("MFRC522 RFID Reader Initialized.\n");

    uint8_t uid[5];
    uint8_t uidLen = 0;

    while (true) {
        if (rfid.isCardPresent()) {
            if (rfid.readCardUID(uid, &uidLen)) {
                printf("Card UID: ");
                for (int i = 0; i < uidLen; i++) {
                    printf("%02X ", uid[i]);
                }
                printf("\n");
                sleep_ms(1000);
            }
        }
        sleep_ms(500);
    }
}
