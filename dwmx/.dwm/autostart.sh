#!/bin/sh

# Execute warpd for keyboard-based mouse control.
exec warpd &
# Execute nitrogen to restore the set wallpaper.
exec nitrogen --restore &
# Execute oneko for cute ghost girl <33333 
exec oneko -tomoyo &

# Add clock to bar

while true; do

	xsetroot -name " $(date) $(battery) " &

	sleep 2
	wait

done &

# Launch Debian bot

while true; do

        cd $HOME/Documents/tek/
	exec python tek.py &
	wait

done &

# Set microphone to VOIP friendly levels. 

exec amixer set -c 2 'Internal Mic Boost' 0 &
exec amixer set -c 2 'Capture' 45 & 
