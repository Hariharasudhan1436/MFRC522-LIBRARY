#ifndef MFRC522_H
#define MFRC522_H

#include "hardware/spi.h"
#include "pico/stdlib.h"

class MFRC522 {
public:
    MFRC522(spi_inst_t* spi, uint cs_pin, uint rst_pin);
    void begin();
    bool isCardPresent();
    bool readCardUID(uint8_t *uid, uint8*_
