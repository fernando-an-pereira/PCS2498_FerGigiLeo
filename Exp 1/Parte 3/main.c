#include <mcs51/8051.h>
#include "serial.h"
#include "relogio.h"

void main()
{
	init_serial();
	init_relogio();
	while(1)
	{
		display_relogio();
	}
}