#ifndef Pin_h
#define Pin_h

namespace PIN
{
    //按钮
    constexpr uint8_t BTN1 = 4;
    constexpr uint8_t BTN2 = 5;

    //I2C引脚
    constexpr uint8_t I2C_SCL = 22;
    constexpr uint8_t I2C_SDA = 21;

    //SPI通信共用引脚
    constexpr uint8_t SPI_SCLK = 13;
    constexpr uint8_t SPI_MOSI = 14;
    constexpr uint8_t SPI_MISO = 25;

    //屏幕
    constexpr uint8_t TFT_RES1 = 18;
    constexpr uint8_t TFT_RES2 = 19;
    constexpr uint8_t TFT_DC1 = 27;
    constexpr uint8_t TFT_CS1 = 26;
    constexpr uint8_t TFT_DC2 = 33;
    constexpr uint8_t TFT_CS2 = 32;

    //SD模块
    constexpr uint8_t SD_CS = 23;
}