#!/bin/bash

set -e

echo 'Blinking LED'

# catch the keyboard interruption CTRL-C
# clean up by turning gpio 17 off
trap '{
    echo "oh, I am slain"
    gpio -g write 17 0
    exit
}' SIGINT

# set gpio 17 to out mode
gpio -g mode 17 out

while true
do
    date +'%H:%M:%S'
    # switch between HIGH and LOW state, respectively
    [[ ${STATE} == 1 ]] && STATE=0 || STATE=1
    gpio -g write 17 "${STATE}"
    sleep 1s
done