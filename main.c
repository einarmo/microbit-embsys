#include "uart.h"
#include "gpio.h"

int main() {
    GPIO->DIRSET = ((1 << 16) - (1 << 4));
    GPIO->OUTCLR = ((1 << 16) - (1 << 4));
    GPIO->PIN_CNF[17] = 0;
    GPIO->PIN_CNF[26] = 0;

    int sleep = 0;
    uartInit();
    //while(uartRead() == '\0');
    GPIO->OUTSET = (1 << 15);
    while(1) {
        if (UART->ERRORSRC & (1 << 2)) {
            GPIO->OUTCLR = (1 << 16) - (1 << 13);
            GPIO->OUTSET = (1 << 15);
        }
        if (!(GPIO->IN & (1 << 17))) {
            uartSend('A');
            GPIO->OUTSET = (1 << 16) - (1 << 13);
        } else if (!(GPIO->IN & (1 << 26))) {
            uartSend('B');
            GPIO->OUTCLR = (1 << 16) - (1 << 13);
        }
        sleep = 10000;
        while(--sleep);
    }
    return 0;
}
