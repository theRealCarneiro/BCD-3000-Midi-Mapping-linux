void startMidi(const char* portname); //Starts the midi conection

int getMidiInput(char buffer[1], int status, snd_rawmidi_t *midiin, snd_rawmidi_t *midiout); //Reads the signal from the BCD

void errormessage(const char *format, ...);
