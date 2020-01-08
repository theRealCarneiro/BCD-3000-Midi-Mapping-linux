#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "jackHeader.h"

void volume(char noteon[3]){
	if(noteon[1] == 2){
		char text[40];
		char a[6];
		if(noteon[2] < 100){
			sprintf(a, "%d", noteon[2]);
		}
		else strcpy(a, "100");
		strcat(strcpy(text, "pactl set-sink-volume jack_out.2 "), strcat(a,"%"));
		system(text);
	}

	else if(noteon[1] == 0){
		char text[40];
		char a[6];
		if(noteon[2] < 100){
			sprintf(a, "%d", noteon[2]);
		}
		else strcpy(a, "100");
		strcat(strcpy(text, "pactl set-sink-volume jack_out "), strcat(a,"%"));
		system(text);
	}
}

void master(int status, int channel){
	if(status == 1){
    		if(channel == 0){
			system("jack_connect main:front-left system:playback_1");
    			system("jack_connect main:front-right system:playback_2");
		}
		else if(channel == 1){
			system("jack_connect music:front-left system:playback_1");
    			system("jack_connect music:front-right system:playback_2");
		}
	}
	else if (status == 0) {
		if(channel == 0){
			system("jack_disconnect main:front-left system:playback_1");
    			system("jack_disconnect main:front-right system:playback_2");
		}
		else if(channel == 1){
			system("jack_disconnect music:front-left system:playback_1");
    			system("jack_disconnect music:front-right system:playback_2");
		}
	}
}

void phone(int status, int channel){ //status == 0 disconnect, == 1 == connect // channel == 0 == master, == 1 == phone
	if(status == 1){
    		if(channel == 0){
			system("jack_connect main:front-left system:playback_3");
    			system("jack_connect main:front-right system:playback_4");
		}
		else if(channel == 1){
			system("jack_connect music:front-left system:playback_3");
    			system("jack_connect music:front-right system:playback_4");
		}
	}
	else if (status == 0) {
		if(channel == 0){
			system("jack_disconnect main:front-left system:playback_3");
    			system("jack_disconnect main:front-right system:playback_4");
		}
		else if(channel == 1){
			system("jack_disconnect music:front-left system:playback_3");
    			system("jack_disconnect music:front-right system:playback_4");
		}
	}
}

void midiJack(int key, int led){
	if(key == 24){
		if(led == 127){
			master(1, 0);
		}
		else master(0, 0);
	}
	else if(key == 23){
		if(led == 127){
			phone(1, 0);
		}
		else phone(0, 0);
	}
	else if(key == 16){
		if(led == 127){
			master(1, 1);
		}
		else master(0, 1);
	}
	else if(key == 15){
		if(led == 127){
			phone(1, 1);
		}
		else phone(0, 1);
	}
}
