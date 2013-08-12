#include <mcs51/8051.h>
#include "compara.h"
#include "serial.h"

volatile unsigned int offset1;
volatile unsigned int total;

void compara_blocos(char *b1, char *b2, unsigned int sz2) {
	int i, n;
	 
	if(total > sz2) {
		n = sz2;
		total -= sz2;
	}
	else
		n = total;
		
 	for(i = 0; i < n; i++) {
		if(b1[i + offset1] != b2[i])
			transmite_int_serial(i + offset1);
	} 
	
	offset1 += sz2;
}

void set_offset_total(unsigned int t) {
	total = t;
	offset1 = 0;
}
