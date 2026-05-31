#include <MKL25Z4.h>
#include <string.h>

//declaring the functions
void UART0_init();
void delay(int n);
char keypad();
void timeout();
void short_delay(int n);

//main function
int main() {
    UART0_init();	//calling the UART

    SIM_SCGC5 |= 0x400;    // Port B
    SIM_SCGC5 |= 0x2000;   // Port E
    SIM_SCGC5 |= 0x800;    // Port C

    // Configure pins
    PORTC_PCR12 |= 0x100;
    PORTB_PCR0  |= 0x100;
    PORTB_PCR1  |= 0x100;
    PORTB_PCR2  |= 0x100;
    PORTB_PCR3  |= 0x100;
    PORTE_PCR0  |= 0x100;
    PORTE_PCR1  |= 0x100;
    PORTE_PCR2  |= 0x100;
    PORTE_PCR3  |= 0x100;

    GPIOB_PDDR |= 0xF;   // Output
    GPIOE_PDDR |= 0x0;   // Input
    GPIOC_PDDR |= 0x0;   // Input

    while (1) {
        if (GPIOC_PDIR == 0x1000) {		//if the switch is clicked	
            int tries = 0;
            char entered_pin[6];

            while (tries < 3) {		//trying for 3 turns
                char str1[] = "Enter your pin number:\r\n";
                for (int i = 0; i < strlen(str1); i++) {			//transmitting the statement
                    while (!(UART0_S1 & 0x80));
                    UART0_D = str1[i];
                }

                for (int k = 0; k < 5; k++) {			
                    delay(1);
                    entered_pin[k] = keypad();
                    while (!(UART0_S1 & 0x80));
                    UART0_D = entered_pin[k];
                }
                entered_pin[5] = '\0';

                while (!(UART0_S1 & 0x80));			//
                UART0_D = '\r';
                while (!(UART0_S1 & 0x80));
                UART0_D = '\n';

                char pin[] = "12345";

                if (strcmp(entered_pin, pin) == 0) {
                    char str2[] = "Entered pin is correct \r\n";
                    for (int j = 0; j < strlen(str2); j++) {
                        while (!(UART0_S1 & 0x80));
                        UART0_D = str2[j];
                    }

                    char str4[] = "Entered amount to be withdrawn \r\n";
                    for (int a = 0; a < strlen(str4); a++) {
                        while (!(UART0_S1 & 0x80));
                        UART0_D = str4[a];
                    }

                    char amount[4];
										int timeout_flag = 0;

										for (int a = 0; a < 4; a++) {
											int wait_time = 0;
											while (!(UART0_S1 & 0x20)) {
												short_delay(1);           // ~100ms
												wait_time++;
												if (wait_time >= 50) {  // ~5 seconds
													timeout_flag = 1;
												break;
												}
											}
											if (timeout_flag) break;
												amount[a] = UART0_D;
											}

											// Timeout check
											if (timeout_flag) {
												char timeout_msg[] = "Timeout!!\r\n";
												for (int j = 0; j < strlen(timeout_msg); j++) {
													while (!(UART0_S1 & 0x80));
														UART0_D = timeout_msg[j];
												}
												break;
											}

											// Echo back amount if no timeout
											for (int a = 0; a < 4; a++) {
												while (!(UART0_S1 & 0x80));
													UART0_D = amount[a];
											}

                    while (!(UART0_S1 & 0x80));
                    UART0_D = '\r';
                    while (!(UART0_S1 & 0x80));
                    UART0_D = '\n';

                    // Convert to int
                    int value = 0;
                    for (int a = 0; a < 4; a++) {
                        value = value * 10 + (amount[a] - '0');
                    }

                    if (value > 5000) {
                        char str5[] = "Insufficient Balance \r\n";
                        for (int j = 0; j < strlen(str5); j++) {
                            while (!(UART0_S1 & 0x80));
                            UART0_D = str5[j];
                        }
                        break;
                    } else {
                        char str6[] = "Transaction success \r\n";
                        for (int j = 0; j < strlen(str6); j++) {
                            while (!(UART0_S1 & 0x80));
                            UART0_D = str6[j];
                        }
                        break;
                    }
                } else {
                    tries++;
                }
            }

            if (tries >= 3) {
                char str3[] = "Incorrect pin , Aborted!\r\n";
                for (int j = 0; j < strlen(str3); j++) {
                    while (!(UART0_S1 & 0x80));
                    UART0_D = str3[j];
                }
            }
        }
    }
}

// Timeout function
void timeout() {
    char str7[] = "TimeOut!!!!\r\n";
    for (int j = 0; j < strlen(str7); j++) {
        while (!(UART0_S1 & 0x80));
        UART0_D = str7[j];
    }
}

// Simple delay loop
void delay(int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 2000000; j++);
}

void short_delay(int n) {
     for (int i = 0; i < 65000; i++);
}

// Keypad reading function
char keypad() {
    char key = '\0';

    GPIOB_PDOR = 0x0E;
    delay(1);
    if (GPIOE_PDIR == 0x0E) key = '1';
    if (GPIOE_PDIR == 0x0D) key = '2';
    if (GPIOE_PDIR == 0x0B) key = '3';
    if (GPIOE_PDIR == 0x07) key = 'A';

    GPIOB_PDOR = 0x0D;
    delay(1);
    if (GPIOE_PDIR == 0x0E) key = '4';
    if (GPIOE_PDIR == 0x0D) key = '5';
    if (GPIOE_PDIR == 0x0B) key = '6';
    if (GPIOE_PDIR == 0x07) key = 'B';

    GPIOB_PDOR = 0x0B;
    delay(1);
    if (GPIOE_PDIR == 0x0E) key = '7';
    if (GPIOE_PDIR == 0x0D) key = '8';
    if (GPIOE_PDIR == 0x0B) key = '9';
    if (GPIOE_PDIR == 0x07) key = 'C';

    GPIOB_PDOR = 0x07;
    delay(1);
    if (GPIOE_PDIR == 0x0E) key = '*';
    if (GPIOE_PDIR == 0x0D) key = '0';
    if (GPIOE_PDIR == 0x0B) key = '#';
    if (GPIOE_PDIR == 0x07) key = 'D';

    return key;
}

// UART0 initialization
void UART0_init() {
    SIM_SCGC5 |= 0x200;       // Enable Port A clock
    PORTA_PCR1 |= 0x200;      // PTA1 RX
    PORTA_PCR2 |= 0x200;      // PTA2 TX
    SIM_SCGC4 |= 0x400;       // UART0 clock
    SIM_SOPT2 |= 0x4000000;   // MCGFLLCLK clock source

    UART0_BDH = 0;
    UART0_BDL = 0x89;         // 9600 baud
    UART0_C4 = 0x0F;
    UART0_C1 = 0;
    UART0_C2 |= 0x08;         // Enable transmitter
    UART0_C2 |= 0x04;         // Enable receiver
}
