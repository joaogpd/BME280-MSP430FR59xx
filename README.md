This library provides a port of [SparkFun's BME280 Arduino library](https://github.com/sparkfun/SparkFun_BME280_Arduino_Library) for the MSP430FR59xx family of boards.

Contrary to the original implementation, only the SPI communication is currently supported, through using the [MSP430FR59xx-SPI library](), by joaogpd. An I2C interface may be added
at a later date. 

As specified previously, this library requires MSP430FR59xx-SPI to work, available on the link above. 

This library was developed and tested on Texas Instruments' Code Composer Studio 12, with the TI v21.6.1 LTS compiler, with the MSP-EXP430FR5994 development board.
