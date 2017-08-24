{
        if(connssl->connecting_state != ssl_connect_2_writing)
          connssl->connecting_state = ssl_connect_2_reading;
        infof(data, "schannel: failed to receive handshake, "
              "need more data\n");
        return CURLE_OK;
      }