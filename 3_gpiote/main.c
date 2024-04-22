#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2); // Button 1
	GPIO->PIN_CNF[14] = (3 << 2); // Button 2
	// Fill inn the configuration for the remaining buttons 
}

int main(){
    // Configure LED Matrix
	for(int i = 17; i <= 20; i++) {
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

    GPIOTE->CONFIG[0] |= 1;
    GPIOTE->CONFIG[0] |= (13 << 8);
    GPIOTE->CONFIG[0] |= (2 << 16);

    for (int i = 1; i <= 4; i++) { 
        GPIOTE->CONFIG[i] |= 3;
        GPIOTE->CONFIG[i] |= ((16+i) << 8);
        GPIOTE->CONFIG[i] |= (3 << 16);
        GPIOTE->CONFIG[i] |= (1 << 20);

        PPI->PPI_CH[i-1].EEP = (uint32_t)&(GPIOTE->IN[0]);
        PPI->PPI_CH[i-1].TEP = (uint32_t)&(GPIOTE->OUT[i]);
    }
    
    PPI->CHENSET |= 15;

    button_init();

	GPIO->OUT |= (1 << 17); // Disable
	GPIO->OUT |= (1 << 18); // Disable
	GPIO->OUT |= (1 << 19); // Disable
	GPIO->OUT |= (1 << 20); // Disable


    int sleep;
    while(1) {
        sleep = 10000;
		while(--sleep); // Delay
    }

    return 0;
}