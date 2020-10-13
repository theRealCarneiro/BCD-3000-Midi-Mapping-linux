BCD:	BCD_3000_Midi.o
	gcc BCD_3000_Midi.o -o BCD -lasound
BCD_3000_Midi.o:	BCD_3000_Midi.c
	gcc -c BCD_3000_Midi.c
clean:
	rm -rf *.o BCD
install:
	install BCD /usr/local/bin
uninstall:
	rm /usr/local/bin/BCD
