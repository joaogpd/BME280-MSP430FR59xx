#include <stdint.h>
#include <msp430.h> 
#include <driverlib.h>
#include <spi.h>

#define BME280_ID_REG 0xD0
#define BME280_HUMIDITY_MSB_REG 0xFD
#define BME280_HUMIDITY_LSB_REG 0xFE
#define BME280_CONFIG_REG 0xF5
#define BME280_CTRL_MEAS_REG 0xF4

uint16_t readHumidityBME280(void) {
    volatile uint8_t humidityRaw[2] = {0x00};

    P7OUT &= ~(BIT1);

    SPI_A3_sendRegisterReceiveData(BME280_HUMIDITY_MSB_REG, (uint8_t*)&humidityRaw, 2);

    P7OUT |= BIT1;

    volatile uint16_t humidity = ((humidityRaw[0]) << 8) | (humidityRaw[1]);

    return humidity;
}

uint8_t readByteBME280(uint8_t regAddr) {
    P7OUT &= ~(BIT1);

    volatile uint8_t dataByte = SPI_A3_sendRegisterReceiveByte(regAddr | 0x80);

    P7OUT |= BIT1;

    return dataByte;
}

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	__bis_SR_register(GIE);

	GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN1);
	GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN1);

	GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0); // DEBUG
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0); // DEBUG

	PMM_unlockLPM5();

	SPI_A3_init(EUSCI_A_SPI_CLOCKSOURCE_SMCLK, 1000000L);

	while (1) {
	    __delay_cycles(1000000);
	    volatile uint8_t id = readByteBME280(BME280_ID_REG);
	    __no_operation();
	}
}
