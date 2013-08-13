#include <mcs51/8051.h>
#include "serial.h"
#include "relogio.h"

void main()
{
	init_serial();
	transmite_serial('\n');
	init_relogio();
	display_relogio();
	while(1)
	{
		display_relogio();
	}
}
