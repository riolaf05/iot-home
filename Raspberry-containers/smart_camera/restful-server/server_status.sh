export HOSTNAME=$(hostname)
export MEMORIA_USATA=$(df -h /dev/sda1 | awk '{ print $3 }' | tail -n 1 | sed 's/[^0-9|\,]*//g') 
export MEMORIA_TOTALE=$(df -h / | awk '{ print $2 }' | tail -n 1 | sed 's/[^0-9|\,]*//g' )
export TEMPERATURA=$(/opt/vc/bin/vcgencmd measure_temp | sed 's/[^0-9|\.]*//g')

