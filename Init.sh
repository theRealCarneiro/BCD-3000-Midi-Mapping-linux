#!/bin/sh
pacmd unload-module module-jack-sink
sleep 1
pactl load-module module-jack-sink client_name=main connect=yes channels=2
sleep 1
pactl load-module module-jack-sink client_name=music connect=yes channels=2
jack_disconnect main:front-left system:playback_1
jack_disconnect main:front-right system:playback_2
jack_disconnect main:front-left system:playback_3
jack_disconnect main:front-right system:playback_4
jack_disconnect music:front-left system:playback_1
jack_disconnect music:front-right system:playback_2
jack_disconnect music:front-left system:playback_3
jack_disconnect music:front-right system:playback_4
