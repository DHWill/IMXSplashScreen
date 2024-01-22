#!/bin/bash

INDEX=0
SPLASH_APP="/home/root/player/SplashScreen"
PLAYER_APP="/home/root/player/launcher.sh"

folder="/home/root/player/AW"

# Initialize an empty array
directories=()

# Loop through the directory and save the directory names in the array
for dir in "$folder"/*/; do
    dir=${dir%*/}
    directories+=("${dir##*/}")
done

# Print the array elements
for ((i=0; i<${#directories[@]}; i++)); do
    echo "${directories[i]}"
done

while true; do
   # Read GPIO value
    GPIO_VALUE=$(gpioget 2 8)

    if [[ "$GPIO_VALUE" -eq 0 ]]; then
	#Button Pressed
	SPLASH_IMAGE=$folder"/"${directories[INDEX]}"/splash.jpg"

	if [ -e $SPLASH_IMAGE ]; then
  	   $SPLASH_APP $folder"/"${directories[INDEX]}"/splash.jpg" 4.5 &
	   killall helloworld-debug &
	   killall helloworld &
	   sleep 1
#	   $SPLASH_APP $folder"/"${directories[INDEX]}"/splash.jpg" 1 &
	   $PLAYER_APP $folder"/"${directories[INDEX]}"/Video.mp4" $folder"/"${directories[INDEX]}"/video_states.json" & >/dev/null
	   
	else
	   echo "no splash image in: "$SPLASH_IMAGE
	fi

        sleep 2
	((INDEX++))
	INDEX=$(($INDEX % ${#directories[@]}))        
    fi

    sleep 0.33

done


