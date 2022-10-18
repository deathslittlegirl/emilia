#!/bin/sh

killall warpd & 
exec pkill warpd &
exec dunst &
exec /usr/lib/kdeconnectd & 
exec nitrogen --restore &
exec goodvibes --without-ui &
exec warpd &
exec picom --backend glx --vsync --experimental-backends --glx-no-stencil --xrender-sync-fence -b -i 0.5 &
exec xrandr --output HDMI-A-0 --set TearFree on &
exec xrandr --output eDP --set TearFree on &
exec /usr/lib/lxpolkit &


# exec ckb-next -b &

exec amixer cset -c 2 numid=10,iface=MIXER,name='Internal Mic Boost Volume' 0 &

exec amixer cset -c 2 numid=7,iface=MIXER,name='Capture Volume' 53 & 

# exec amixer set -c 3 'Mic' 77 & 

exec amixer cset -c 2 numid=8,iface=MIXER,name='Capture Switch' off &

# exec amixer cset -c 3 numid=7,iface=MIXER,name='Mic Capture Switch' off &

while true; do
	
	memory=$(free -h | awk '(NR==2){ print $3 }')

	speaker=$(amixer get -c 2 Master | awk -F'[][]' 'END{print $2 }')

	microphone=$(amixer get -c 2 Capture | awk -F'[][]' 'END{ print $6"::"$2 }')	
	#micbvolume=$(amixer get -c 3 Mic | awk -F '[][]' 'END{ print $6":"$2 }')
	
	temperature=$(sed 's/000$/°C/' /sys/class/thermal/thermal_zone0/temp)

	battery=$(cat /sys/class/power_supply/BAT0/capacity)

	clock=$(date +'[%m%d.%H%M.%S%N]')	

	xsetroot -name " T::$temperature | M: $microphone | S::$speaker | B::$battery% | $clock " &
	
	wait
done &

while true; do

    exec warpd -c $HOME/.config/warpd/config &
    wait

done &

while true; do

    cd $HOME/.var/app/com.discordapp.Discord
        rm -rf cache/
        cd $HOME
	sleep 120 &
	wait
done &	

while true; do

        
	liapeak=$(amixer get -c 2 'Internal Mic Boost' | awk -F'[][]' 'END{print $2 }')
	lialoud=$(amixer get -c 2 'Capture' | awk -F'[][]' 'END{print $2 }')
	
	if [ $liapeak != "0%" ]; then
		exec amixer cset -c 2 numid=10,iface=MIXER,name='Internal Mic Boost Volume' 0 & 
		exec amixer cset -c 2 numid=7,iface=MIXER,name='Capture Volume' 53 & 
	
	elif [ $lialoud == "100%" ]; then

	    exec amixer cset -c 2 numid=7,iface=MIXER,name='Capture Volume' 53 &

	fi
	
       wait
done & 
