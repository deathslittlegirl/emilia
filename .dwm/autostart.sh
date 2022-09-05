#!/bin/sh

exec dunst &
exec /usr/libexec/kdeconnectd & 
exec nitrogen --restore &
exec goodvibes --without-ui &
exec warpd &
exec picom --backend glx --vsync opengl-swc --paint-on-overlay --glx-no-stencil &

while true; do
	
	memory=$(free -h | awk '(NR==2){ print $3 }')

	volume=$(amixer get Master | awk -F'[][]' 'END{print $2 }')

	micvolume=$(amixer get -c 2 Capture | awk -F'[][]' 'END{ print $6"::"$2 }')	
	#micbvolume=$(amixer get -c 3 Mic | awk -F '[][]' 'END{ print $6":"$2 }')
	
	temperature=$(sed 's/000$/°C/' /sys/class/thermal/thermal_zone0/temp)

	battery=$(cat /sys/class/power_supply/BAT0/capacity)

	clock=$(date +'%m::%d %a %H:%M:%S::%N')	

	xsetroot -name " T::$temperature | M: $micvolume | V::$volume | B::$battery% | $clock " &
	
	wait
done &

