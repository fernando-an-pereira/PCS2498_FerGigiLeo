#include <mcs51/8051.h>

void delay20()
{
	unsigned char i = 0, j = 0, k = 0, m = 0;
	
	while(i < 0xff) {
		while(j < 0xff) {
			while(k < 0xff) {
				k++;
				while(m < 0xff) {
					m++;
				}
			}
			j++;
		}
		i++;
	}
	
}

void init_serial(void) 
{ 
	PCON = 0x00; /* SMOD = 0, no modo 1, divide clock por 32 */ 
	SCON = 0x42; /* Seleciona modo 1: UART, 8 bits, clock do Timer 1 */
	TMOD = 0x20 ; /* Configura timer 1: modo 2, 8 bits, auto reload */
	TH1 = 0xFA ; /* divisão para 4.800 baud */ 
	TR1 = 1; /* TCON.6 - dispara timer */ 
	TI = 1; /* Inicia TI – transmissor pronto */ 
} 


void main(void) 
{ 
	init_serial(); 
	while(1) 
	{ 
		while (!TI); /* Espera transmissor estar pronto para transmitir */
		TI = 0; /* Bloqueia transmissor */
		SBUF = 0x41; /* Envia caractere */
		delay20();
	} /* Após a transmissão, o canal serial fará TI = 1 */
	
} 
