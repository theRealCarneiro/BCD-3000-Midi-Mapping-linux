#include <alsa/asoundlib.h>
#include <alsa/control.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "header.h"

int status;
int mode = SND_RAWMIDI_SYNC;
snd_rawmidi_t *midiin = NULL;
snd_rawmidi_t *midiout = NULL;

void main(){
	system("amidi -l | grep BCD | awk '{print $2}' > /home/gabriel/hw.txt");
     FILE *fp;
     char hw[10];
     int i = 0;
	fp = fopen("/home/gabriel/hw.txt","rt");
	while((hw[i] = fgetc(fp)) != EOF) i++;
	hw[8] = '\0';
	fclose(fp);
	remove("/home/gabriel/hw.txt");
	
	const char *portname = hw;
	char noteon[3];
	openMidi(portname);
	while(1){
		int key = readMidi(noteon); //reads midi input and return the key/knob that was used
		noteon[1] = midiValues[key];
		if(noteon[1] != -1 && (unsigned char)noteon[0] == 0x90){ //0x90 == button 0xB0 == knob
			noteon[0] = 0xB0;
			noteon[2] = ledStatus[key] = 127 - ledStatus[key]; //toggle led
			writeMidi(noteon);
		}
		//printf("%x %d %d\n",(unsigned char)noteon[0], (int)noteon[1], (int)noteon[2]); //to print info
	}
}

void errormessage(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
	putc('\n', stderr);
}

void openMidi(const char* portname){
	if ((status = snd_rawmidi_open(&midiin, &midiout, portname, mode)) < 0){
		errormessage("Problem opening MIDI input: %s", snd_strerror(status));
		exit(1);
	}
}

int readMidi(char buffer[3]){
	int key = 0;
	do {
		fflush(stdout);
		if ((status = snd_rawmidi_read(midiin, buffer, 3)) < 0){
			errormessage("Problem reading MIDI input: %s", snd_strerror(status));
		}
		key = (int)buffer[1];

		//printf("%x %d %d\n",(unsigned char)buffer[0], (int)buffer[1], (int)buffer[2]);
	}
	while(((int)buffer[2] != 127 && 
		(unsigned char)buffer[0] == 0x90) ||
		(((unsigned char)buffer[0] != 0x90) && 
		(key == 18 || key == 19 || key == 12 || key == 11)));
	return key;
}


void writeMidi(char noteon[3]){
	if ((status = snd_rawmidi_write(midiout, noteon, 3)) < 0) { // Writes the signal 
		errormessage("Problem writing to MIDI output: %s", snd_strerror(status));
		exit(1);
	}
}
