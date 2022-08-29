#!/bin/sh

exec dunst &
exec nitrogen --restore &
exec xcompmgr -f -D 5 &

exec amixer set -c 2 'Internal Mic Boost' 0 &
exec amixer set -c 2 'Capture' 52 & 
exec amixer cset -c 2 numid=8,iface=MIXER,name='Capture Switch' off &

while true; do
	
	memory=$(free -h | awk '(NR==2){ print $3 }')

	volume=$(amixer get Master | awk -F'[][]' 'END{print $2 }')

	micvolume=$(amixer get -c 2 Capture | awk -F'[][]' 'END{ print $6":"$2 }')	
	#micbvolume=$(amixer get -c 3 Mic | awk -F '[][]' 'END{ print $6":"$2 }')
	
	temperature=$(sed 's/000$/°C/' /sys/class/thermal/thermal_zone0/temp)

	battery=$(cat /sys/class/power_supply/BAT0/capacity)

	clock=$(date +'%m-%d %a %H:%M:%S:%N')	

	xsetroot -name " T: $temperature | M: $micvolume | V: $volume | B: $battery% :: $clock " &
	
	wait
done &

