su raspberry tg è installato sulla cartella /home/pi/Desktop/telegram_pi, è un client telegram x raspberry che contiene un 
interpretre LUA
tramite uno script LUA lanciato con il comando: 

bin/./telegram-cli -k tg-server.pub -W -s ./action.lua

è possibile effettuare delle operazioni quando viene ricevuto un msg su telegram (seguire il tutorial: https://pimylifeup.com/raspberry-pi-telegram-bot/)

il file action.lua va in /tg e contiene gli script LUA per rispondere ai msg ricevuti su telegram
il file camra.sh è uno script che scatta una foto (motion deve essere disattivato per rendere disponibile la telecamera)
