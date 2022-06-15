#!/bin/sh

#* set xsetroot bar. *#

while true; do
	
	memory=$(free -h | awk '(NR==2){ print $4 }')
	volume=$(amixer get -c 2 Master | awk -F'[][]' 'END{ print $6":"$2 }')
	micvolume=$(amixer get -c 2 Capture | awk -F'[][]' 'END{ print $6":"$2 }')	
	temperature=$(sed 's/000$/°C/' /sys/class/thermal/thermal_zone0/temp)
	battery=$(cat /sys/class/power_supply/BAT0/capacity)
	clock=$(date +'%a %m-%d %H:%M:%S.%N')	
	xsetroot -name " T: $temperature | M: $micvolume | $clock | V: $volume | $battery% " &
	
	wait

done &

# execute nitrogen to restore the set wallpaper.

exec nitrogen --restore &


# execute warpd for keyboard-based mouse control.

exec warpd &
