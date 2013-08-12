#include <mcs51/8051.h>
#include "serial.h"
#include "relogio.h"

unsigned char __far __at 0xFFF3 vet_serial[] = {0x02, 0xA0, 0x0B};

/* Contadores */
/* contador de centesimos de segundos */
volatile unsigned char __near cs0;
volatile unsigned char __near cs1;
/* contador de segundos */
volatile unsigned char __near s0;
volatile unsigned char __near s1;
/* contador de minutos */
volatile unsigned char __near min0;
volatile unsigned char __near min1;
/* contador auxiliar */
volatile unsigned char __near count;

/* rotina de tratamento da interrupção do timer 0 */
void timer0_int () __interrupt 1 __using 1 {
	count = count - 0x01;
	if(count == 0x00) { /* verifica se o contador chegou ao fim */
		incr_relogio(); /* incrementa valor do relógio */	
		count = 0x24; /* restaura contador */
	}
}

/* subrotina de inicialização do relógio */
void init_relogio() {
	TMOD |= 0x02; /* modo de operação 2 do timer */
	TH0 = 0x00; /* valor inicial do high value do timer0 */
	TL0 = 0x00; /* valor inicial do low value do timer0 */
	count = 0x24; /* valor inicial do contador auxiliar */
	IE |= 0x82; /* IE.1- habilita interrupção timer0  e IE.7- global */ 
}

/* subrotina que inicia a contagem do relógio */
void inicia_relogio () {
	TR0 = 1;
}

/* subrotina que inicia para do relógio */
void para_relogio () {
	TR0 = 0;
}

/* subrotina que zera o relogio */
void zera_relogio() {
	cs0 = '0';
	cs1 = '0';
	s0 = '0';
	s1= '0';
	min0 = '0';
	min1 = '0';
}

/* subrotina de incremento do relógio */
void incr_relogio() {
	cs0 += 0x01;
	if(cs0 < 0x3A) return;
	cs0 = '0';
	cs1 += 0x01;
	if(cs1 < 0x3A) return;
	cs1 = '0';
	s0 += 0x01;
	if(s0 < 0x3A) return;
	s0 = '0';
	s1 += 0x01;
	if(s1 < 0x36) return;
	s1 = '0';
	min0 += 0x01;
	if(min0 < 0x3A) return;
	min0 = '0';
	min1 += 0x01;
	if(min1 < 0x36) return;
	min1 = '0';
}

void display_relogio() {
	transmite_serial('\r');
	transmite_serial(min1);
	transmite_serial(min0);
	transmite_serial(':');
	transmite_serial(s1);
	transmite_serial(s0);
	transmite_serial(':');
	transmite_serial(cs1);
	transmite_serial(cs0);
}
