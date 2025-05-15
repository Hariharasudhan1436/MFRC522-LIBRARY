#include "mfrc522.h"

// Register map shortcuts
#define CommandReg      0x01
#define ComIEnReg       0x02
#define DivIEnReg       0x03
#define ComIrqReg       0x04
#define FIFOLevelReg    0x0A
#define FIFODataReg     0x09
#define ControlReg      0x0C
#define BitFramingReg   0x0D
#define ModeReg         0x11
#define TxControlReg    0x14
#define VersionReg      0x37

// Commands
#define PCD_IDLE        0x00
#define PCD_TRANSCEIVE  0x0C
#define PICC_REQIDL     0x26
#define PICC_ANTICOLL   0x93

MFRC522::MFRC522(spi_inst_t* spi_port, uint cs_pin, uint rst_pin) {
    spi = spi_port;
    cs = cs_pin;
    rst = rst_pin;
}

void MFRC522::begin() {
    spi_init(spi, 1000000); // 1 MHz
    gpio_set_function(2, GPIO_FUNC_SPI); // SCK
    gpio_set_function(3, GPIO_FUNC_SPI); // MOSI
    gpio_set_function(4, GPIO_FUNC_SPI); // MISO

    gpio_init(cs);
    gpio_set_dir(cs, GPIO_OUT);
    gpio_put(cs, 1);

    gpio_init(rst);
    gpio_set_dir(rst, GPIO_OUT);
    gpio_put(rst, 1);

    reset();
    writeRegister(TxControlReg, 0x03); // Turn antenna on
}

void MFRC522::reset() {
    writeRegister(CommandReg, PCD_IDLE);
}

void MFRC522::writeRegister(uint8_t reg, uint8_t val) {
    uint8_t addr = ((reg << 1) & 0x7E);
    gpio_put(cs, 0);
    spi_write_blocking(spi, &addr, 1);
    spi_write_blocking(spi, &val, 1);
    gpio_put(cs, 1);
}

uint8_t MFRC522::readRegister(uint8_t reg) {
    uint8_t addr = ((reg << 1) & 0x7E) | 0x80;
    uint8_t val = 0;
    gpio_put(cs, 0);
    spi_write_blocking(spi, &addr, 1);
    spi_read_blocking(spi, 0x00, &val, 1);
    gpio_put(cs, 1);
    return val;
}

void MFRC522::setBitMask(uint8_t reg, uint8_t mask) {
    uint8_t tmp = readRegister(reg);
    writeRegister(reg, tmp | mask);
}

void MFRC522::antennaOn() {
    uint8_t temp = readRegister(TxControlReg);
    if (!(temp & 0x03)) {
        writeRegister(TxControlReg, temp | 0x03);
    }
}

bool MFRC522::isCardPresent() {
    writeRegister(BitFramingReg, 0x07);
    writeRegister(CommandReg, PCD_TRANSCEIVE);
    writeRegister(FIFODataReg, PICC_REQIDL);
    setBitMask(BitFramingReg, 0x80);
    sleep_ms(50);
    uint8_t irq = readRegister(ComIrqReg);
    return (irq & 0x01) == 0;
}

bool MFRC522::readCardUID(uint8_t *uid, uint8_t *uidLen) {
    writeRegister(BitFramingReg, 0x00);
    writeRegister(CommandReg, PCD_TRANSCEIVE);
    writeRegister(FIFODataReg, PICC_ANTICOLL);
    setBitMask(BitFramingReg, 0x80);
    sleep_ms(50);
    for (int i = 0; i < 5; i++) {
        uid[i] = readRegister(FIFODataReg);
    }
    *uidLen = 5;
    return true;
}
