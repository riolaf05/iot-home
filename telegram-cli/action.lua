function on_msg_receive (msg)
      if msg.out then
          return
      end
      if (msg.text=='ping') then
            send_msg (msg.from.print_name, 'pong', ok_cb, false)
      end
      if (msg.text=='photo') then
            os.execute('/home/pi/camera/camera.sh')
            send_photo (msg.from.print_name, '/home/pi/camera/photo.jpg', ok_cb, false)
      end
end

function on_our_id (our_id)
end

function on_secret_chat_update (user, what_changed)
end

function on_user_update (user, what_changed)
end

function on_chat_update (user, what_changed)
end

function on_get_difference_end ()
end

function on_binlog_replay_end ()
end
