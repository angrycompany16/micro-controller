#include "uart.h"

void button_init();

int main() {
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

    button_init();
    uart_init();

    GPIO->OUT &= ~(1 << 17);

    uart_read();

	int sleep = 0;
    while (1) {
        GPIO->OUT &= ~(1 << 17);

        if ((GPIO->IN & (1 << 13)) == 0) {
        	GPIO->OUT |= (1 << 17); // Disable
            uart_send('A');
        }

		if ((GPIO->IN & (1 << 14)) == 0) {
        	GPIO->OUT |= (1 << 17); // Disable
            uart_send('B');
		}

        sleep = 10000;
		while(--sleep); // Delay
    }

    return 5;
}

void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2); // Button 1
	GPIO->PIN_CNF[14] = (3 << 2); // Button 2
	// Fill inn the configuration for the remaining buttons 
}