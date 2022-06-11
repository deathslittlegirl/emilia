#!/bin/sh

# Execute warpd for keyboard-based mouse control.
exec warpd &
# Execute nitrogen to restore the set wallpaper.
exec nitrogen --restore &
# Execute oneko for cute maid girl <33333 
exec oneko -sakura &

# Add clock to bar

while true; do

	xsetroot -name " $(date) " &
	sleep 2
	wait

done &

# Set microphone to VOIP friendly levels. 

exec amixer set -c 2 'Internal Mic Boost' 0 &
exec amixer set -c 2 'Capture' 45 & 
