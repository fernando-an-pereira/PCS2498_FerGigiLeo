#include <mcs51/8051.h>
#include "relogio.h"

unsigned char __far __at 0xFFFC vet[] = {0x02, 0xA0, 0x23};

void init_serial(void) 
{ 	/* Timer 1 é utilizado para gerar a taxa de comunicação */
	PCON = 0x00; /* SMOD=0, no modo 1, divide o clock por 32 */
	SCON = 0x52; /* Seleciona modo 1: UART, 8 bits, clock do Timer 1 */ 
	/* SCON.4 - REN=1(habilita a recepção) */
	/* SCON.1 - TI=1 (transmissor pronto) */
	/* SCON.0 - RI=0 (receptor vazio)*/ 
	TMOD |= 0x20; /* Configura timer 1: modo 2, 8 bits, auto reload */
	TH1 = 0xFD; /* divisão para 9.600 baud */
	TR1 = 1; /* TCON.6 - dispara timer 1 */
	IE |= 0x90; /* IE.1- habilita interrupção timer0, IE.4- do canal serial e IE.7- global */ 
} 

void int_serial (void) __interrupt 4 __using 1 
{ 
	char aux;
	if (RI == 1) 
	{ /* Se for interrupção de recepção: */
		RI = 0; /* limpa pedido de interrupção de recepção */
		aux = SBUF; /* Retira caractere recebido do bufer */
		if(aux == 'z' || aux == 'Z')
			zera_relogio();
		else if(aux == 'p' || aux == 'P')
			para_relogio();
		else if (aux == 'c' || aux == 'C')
			inicia_relogio();
	} 
} 

void transmite_serial(char c) 
{
	while (!TI); /* Espera transmissor estar pronto para transmitir */
	TI = 0; /* Bloqueia transmissor */
	SBUF = c; /* Envia caractere */
}
