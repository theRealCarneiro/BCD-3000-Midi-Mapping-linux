#include <alsa/asoundlib.h>
#include <alsa/control.h>

int midiValues[37] = { //-1 equals no led
	-1, //0
	-1, //1
	-1, //2
	-1, //3
	-1, //4
	21, //5
	-1, //6
	-1, //7
	-1, //8
	-1, //9
	-1, //10
	13, //11
	24, //12
	23, //13
	22, //14
	-1, //15
	20, //16
	19, //17
	18, //18
	17, //19
	16, //20
	15, //21
	14, //22
	-1, //23
	12, //24
	11, //25
	10, //26
	 9, //27
	25, //28
	 8, //29
	 7, //30
	 6, //31
	 5, //32
	 4, //33 
	 3, //34
	 2, //35
	 1  //36
 };

int ledStatus[37] = {0};


typedef void (*keyFunc) (char);

void errormessage(const char *format, ...);

void openMidi(const char* portname);

int readMidi(char buffer[3]);

void writeMidi(char noteon[3]);

void mainVolume(char led);

void musicVolume(char led);

void micVolume(char led);

void mainMaster(char led);

void mainPhone(char led);

void musicMaster(char led);

void musicPhone(char led);

void pauseSpotify(char led);

void nextSong(char led);

void previousSong(char led);

void noFunc(char led);

