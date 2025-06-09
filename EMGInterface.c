#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_CHANNEL 0
#define SPI_SPEED   1000000  // 1 MHz

// Read analog data from MCP3008 ADC
int readADC(int channel) {
    unsigned char buffer[3];

    buffer[0] = 1;  // Start bit
    buffer[1] = (8 + channel) << 4;  // Channel config
    buffer[2] = 0;

    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 3);

    int result = ((buffer[1] & 3) << 8) + buffer[2];
    return result;
}

int main() {
    if (wiringPiSetup() == -1 || wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1) {
        printf("SPI setup failed.\n");
        return 1;
    }

    while (1) {
        printf("EMG Readings:\n");
        for (int i = 0; i < 4; i++) {
            int value = readADC(i);
            printf("  Channel %d: %d\n", i, value);
        }
        delay(200);  // Delay 200 ms
    }

    return 0;
}