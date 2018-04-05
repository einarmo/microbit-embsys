#include "uart.h"
#include "gpio.h"

void uartInit() {
    GPIO->DIRSET = (1 << 24);
    GPIO->DIRCLR = (1 << 25);
    GPIO->PIN_CNF[24] = 1;
    GPIO->PIN_CNF[25] = 0;
    UART->PSELTXD =  0xFFFFFFFF & ~(1 << 24);
    UART->PSELRXD =  0xFFFFFFFF & ~(1 << 25);
    UART->PSELCTS =  0xFFFFFFFF;
    UART->PSELRTS =  0xFFFFFFFF;
    UART->BAUDRATE = 0x00275000;
    UART->ENABLE = 4;
    UART->STARTRX = 1;
}

void uartSend(char letter) {
    // UART->STOPRX = 1;
    // UART->TXDRDY = 0;
    UART->STARTTX = 1;
    UART->TXD = (uint32_t) letter;
    // if (UART->TXDRDY) {
    //    GPIO->OUTSET = (1 << 14);
    // }
    while(!UART->TXDRDY);

    UART->TXDRDY = 0;
    UART->STOPTX = 1;
}

char uartRead() {
    if (UART->RXDRDY) {
        UART->RXDRDY = 0;
        return (char) UART->RXD;
    }
    return '\0';
}
