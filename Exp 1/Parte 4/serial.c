#include <mcs51/8051.h>
#include "serial.h"
#include "compara.h"

#define XON 0x11
#define XOFF 0x13

unsigned char __far __at 0xFFFC vet_relogio[] = {0x02, 0xA0, 0x23};

volatile char *__xdata bloco;
volatile char *__xdata bloco_transmitido;
volatile unsigned int pos_bloco;
volatile unsigned int size_bloco;

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
		bloco[pos_bloco++] = aux;
		if(pos_bloco >= size_bloco) {
			xoff_serial();
			compara_blocos(bloco_transmitido, bloco, size_bloco);
			xon_serial();
		}
	} 
} 

void transmite_serial(char c) 
{
	while (!TI); /* Espera transmissor estar pronto para transmitir */
	TI = 0; /* Bloqueia transmissor */
	SBUF = c; /* Envia caractere */
}

void transmite_int_serial(int i) {
	int numero[8];
	int algarismos = 0, j;
	
	do {
		numero[algarismos++] = i % 10;
		i /= 10;
		
	}while(i > 0);
	
	for(j = algarismos - 1; j >= 0; j++) {
		switch(numero[j]) {
			case 0:	transmite_serial('0');
				break;
			case 1:	transmite_serial('1');
				break;
			case 2:	transmite_serial('2');
				break;
			case 3:	transmite_serial('3');
				break;
			case 4:	transmite_serial('4');
				break;
			case 5:	transmite_serial('5');
				break;
			case 6:	transmite_serial('6');
				break;
			case 7:	transmite_serial('7');
				break;
			case 8:	transmite_serial('8');
				break;
			case 9:	transmite_serial('9');
				break;
			default:
		}
				
	} 
	
	transmite_serial(' ');
}

void transmite_bloco_serial(char *bl, int sz)
{
	int i;
	for(i = 0; i < sz; i++)
		transmite_serial(bl[i]);
	bloco_transmitido = bl;
		
}

void recebe_bloco_serial(char *bl, int sz)
{
	bloco = bl;
	size_bloco = sz;
	pos_bloco = 0;	
}

void xon_serial()
{
	transmite_serial(XON);
}

void xoff_serial()
{
	transmite_serial(XOFF);
}
