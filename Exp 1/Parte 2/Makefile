TRG1 = prog1
TRG2 = prog2
DELAY = delay

SDCCFLAGS = --model-large

ASLINKFLAGS = --xram-loc 0x8000 --code-loc 0xA000

%.rel: %.c
	sdcc $(SDCCFLAGS) -c $<

$(DELAY).rel: $(DELAY).asm
	sdas8051 -losg $^

%.hex: %.ihx
	packihx $< > $@

all: $(TRG1).hex $(TRG2).hex

%.ihx: %.rel 
	sdcc $(SDCCFLAGS) $(ASLINKFLAGS) $^
	
clean:
	rm -f *.lk *.cdb *.omf *.ihx *.lnk *.lst *.map *.rel *.rst *.sym $(TRG1).asm $(TRG2).asm *.mem
