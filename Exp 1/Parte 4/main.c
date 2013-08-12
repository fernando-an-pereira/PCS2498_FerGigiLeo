#include <mcs51/8051.h>
#include "serial.h"
#include "compara.h"

char __xdata bloco_enviado[1024];
char __xdata bloco_recebido[256];

void main()
{	
	
	init_serial();
	
	set_offset_total(1024);
	
	transmite_bloco_serial(bloco_enviado, 1024);
	recebe_bloco_serial(bloco_recebido, 256);
	
	compara_blocos(bloco_enviado, bloco_recebido, 256);
	
	

	while(1)
	{
		;
	}
}
