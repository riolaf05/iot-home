def on_message(client, userdata, msg):
        try:
                test = str(msg.payload)
                # If Reading is valid
                if isinstance(test, str):
                        print(test)
                        # Closing the connection
                        conn.close()
                else:
                        print('Error')
                sleep(20)
        except:
                print "connessione persa!"