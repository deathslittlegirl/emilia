#!/bin/sh
# Execute warpd for keyboard-based mouse control.
exec warpd &
# Execute nitrogen to restore the set wallpaper.
exec nitrogen --restore &
# Ghost girl?
exec oneko -tomoyo &

# Add clock to bar



while true; do
	
	memory=$(free -h | awk '(NR==2){ print $4 }')
	volume=$(amixer get -c 2 Master | awk -F'[][]' 'END{ print $4 }')
	micvolume=$(amixer get -c 2 Capture | awk -F'[][]' 'END{ print $4":"$6 }')	
	temperature=$(sed 's/000$/°C/' /sys/class/thermal/thermal_zone0/temp)
	battery=$(cat /sys/class/power_supply/BAT0/capacity)
	clock=$(date +'%F %H:%M:%S.%N')

	xsetroot -name " T: $temperature |  M: $micvolume | $clock | V: $volume | B: $battery% |" &
	
	wait

done &
