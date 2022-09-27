#!/bin/sh

exec killall warpd & 
exec dunst &
exec /usr/libexec/kdeconnectd & 
exec nitrogen --restore &
exec goodvibes --without-ui &
exec warpd &
exec picom -f --backend glx --vsync --paint-on-overlay --experimental-backends --glx-no-stencil --xrender-sync-fence -b -i 0.5 &
exec xrandr --output HDMI-A-0 --set TearFree on &
exec xrandr --output eDP --set TearFree on &

exec amixer cset -c 2 numid=10,iface=MIXER,name='Internal Mic Boost Volume' 0 &

exec amixer cset -c 2 numid=7,iface=MIXER,name='Capture Volume' 53 & 

# exec amixer set -c 3 'Mic' 77 & 

exec amixer cset -c 2 numid=8,iface=MIXER,name='Capture Switch' off &

# exec amixer cset -c 3 numid=7,iface=MIXER,name='Mic Capture Switch' off &

while true; do
	
	memory=$(free -h | awk '(NR==2){ print $3 }')

	volume=$(amixer get -c 2 Master | awk -F'[][]' 'END{print $2 }')

	micvolume=$(amixer get -c 2 Capture | awk -F'[][]' 'END{ print $6"::"$2 }')	
	#micbvolume=$(amixer get -c 3 Mic | awk -F '[][]' 'END{ print $6":"$2 }')
	
	temperature=$(sed 's/000$/°C/' /sys/class/thermal/thermal_zone0/temp)

	battery=$(cat /sys/class/power_supply/BAT0/capacity)

	clock=$(date +'%m::%d %a %H:%M:%S::%N')	

	xsetroot -name " T::$temperature | M: $micvolume | V::$volume | B::$battery% | $clock " &
	
	wait
done &

