echo "Installing dependencies.."
pip3 install -r requirements.txt

echo "Updating cronjobs.."
echo "Writing out current crontabs"
crontab -l > mycron

if grep -q "get_server_info.sh" mycron
then
    echo "Cronjob already set!"
else
    echo "Writing out new crontabs"
    echo "@reboot $HOME/Scripts/api-server.py" >> mycron

    echo "Installing new cron file"
    crontab mycron
    rm mycron
fi