TRG = main
OBJ = main.rel serial.rel compara.rel

SDCCFLAGS = --model-large

ASLINKFLAGS = --xram-loc 0x8000 --code-loc 0xA000

%.rel: %.c
	sdcc $(SDCCFLAGS) -c $<

$(TRG).hex: $(TRG).ihx
	packihx $(TRG).ihx > $(TRG).hex

all: $(TRG).hex

$(TRG).ihx: $(OBJ)
	sdcc $(SDCCFLAGS) $(ASLINKFLAGS) $^

clean:
	rm -f *.lk *.cdb *.omf *.ihx *.lnk *.lst *.map *.rel *.rst *.sym *.asm *.mem
