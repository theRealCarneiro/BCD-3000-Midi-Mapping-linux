#include <alsa/asoundlib.h>
#include <alsa/control.h>

int midiValues[37] = {-1, -1, -1, -1, -1,
					  21, -1, -1, -1, -1,
					  -1, 13, 24, 23, 22,
					  -1, 20, 19, 18, 17,
					  16, 15, 14, -1, 12,
					  11, 10, 9, 25, 8, 7,
					  6, 5, 4, 3, 2, 1};

int ledStatus[37] = {-1, -1, -1, -1, -1,
					  0, -1, -1, -1, -1,
					  -1, 0, 0, 0, 0,
					  -1, 0, 0, 0, 0,
					  0, 0, 0, -1, 0,
					  0, 0, 0, 0, 0, 0,
					  0, 0, 0, 0, 0, 0};

void errormessage(const char *format, ...) {
   va_list ap;
   va_start(ap, format);
   vfprintf(stderr, format, ap);
   va_end(ap);
   putc('\n', stderr);
}

int getMidiInput(char buffer[1], int status, snd_rawmidi_t *midiin, snd_rawmidi_t *midiout);

void startMidi(const char* portname){
	int status;
    int mode = SND_RAWMIDI_SYNC;
	snd_rawmidi_t *midiin = NULL;
	snd_rawmidi_t *midiout = NULL;
    if ((status = snd_rawmidi_open(&midiin, &midiout, portname, mode)) < 0){
        errormessage("Problem opening MIDI input: %s", snd_strerror(status));
        exit(1);
    }

//     if ((status = snd_rawmidi_open(NULL, &midiout, portname, mode)) < 0) {
//       errormessage("Problem opening MIDI output: %s", snd_strerror(status));
//       exit(1);
//    }

    char buffer[1];      // Storage for input buffer received

	while(1){
    	getMidiInput(buffer, status, midiin, midiout);
	}
}

int getMidiInput(char buffer[1], int status, snd_rawmidi_t *midiin, snd_rawmidi_t *midiout){
	int i = 0;
	int led = 0;
	char noteon[3];//  = {0xB0, 17, 127};
	int key;
	while (i < 3){
        if ((status = snd_rawmidi_read(midiin, buffer, 1)) < 0){
            errormessage("Problem reading MIDI input: %s", snd_strerror(status));
        }
		if(i == 0){
			if ((unsigned char)buffer[0] == 0x90){ // command byte: print in hex
				//printf("0x%x ", (unsigned char)buffer[0]);
				led = 1;
				noteon[0] = 0xB0;
			} else break;
		}
        
        else if (i == 1){
			key = midiValues[(int)buffer[0]];
			if(key > -1)
            	noteon[1] = key;
		}

		else {
			if((int)buffer[0] == 127) {
				if(ledStatus[(int)buffer[0]] == 0){
					ledStatus[(int)buffer[0]] = 127;
					noteon[2] = 127;
				} 
				else if(ledStatus[(int)buffer[0]] == 127){
					ledStatus[(int)buffer[0]] = 0;
					noteon[2] = 0;
				} 
			}
		}
        fflush(stdout);
		i++;
    }
	if(led == 1 && key != -1) {
		if ((status = snd_rawmidi_write(midiout, noteon, 3)) < 0) {
      		errormessage("Problem writing to MIDI output: %s", snd_strerror(status));
      		exit(1);
   		}
	}
}


int main (int argc, char *argv[]){
    int status;
    const char* portname = "hw:2,0,0";
	startMidi(portname);

}
