#include "uart.h"
#include <stdio.h>
#include <sys/types.h>

void button_init();

ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    
    for(int i = 0; i < count; i++){
        uart_send(*letter);
        letter++;
    }
    
    return count;
}

ssize_t _read(int fd, void *buf, size_t count){
    char *str = (char *)(buf);
    char letter;
    
    do {
        letter = uart_read();
    } while(letter == '\0');
    
    *str = letter;
    return 1;
}

int main() {
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

    button_init();
    uart_init();

    // GPIO->OUT &= ~(1 << 17);

	int sleep = 0;

    iprintf("\n\r");

    // iprintf("The average grade in TTK%d was in %d was %c\n\r", 4235, 2022, 'B');
    int num1;
    int num2;
    iprintf("Give me two numbers: \n\r");

    iscanf("%d", &num1);
    iscanf("%d", &num2);
    // scanf("Give me a number again: %d\n\r", &num2);

    iprintf("The product between these two numbers is %d\n\r", num1 * num2);

    iprintf("\n\r");

    while (1) {
        
        // if ((GPIO->IN & (1 << 13)) == 0) {
        // 	// GPIO->OUT |= (1 << 17); // Disable
        //     uart_send('A');
        // }

		// if ((GPIO->IN & (1 << 14)) == 0) {
        // 	// GPIO->OUT |= (1 << 17); // Disable
        //     uart_send('B');
		// }

        // if (uart_read() != '\0') {
        // 	// GPIO->OUT |= (1 << 17); // Disable
        //     GPIO->OUT ^= (1 << 17);
        // }

        sleep = 10000;
		while(--sleep); // Delay
    }

    return 5;
}

void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2); // Button 1
	GPIO->PIN_CNF[14] = (3 << 2); // Button 2
}