#ifndef SERIAL_H_
#define SERIAL_H_

void init_serial(void);
void transmite_serial(char c);
void transmite_int_serial(int i);
void transmite_bloco_serial(char *bl, int sz);
void recebe_bloco_serial(char *bl, int sz);
void xon_serial();
void xoff_serial();

#endif
