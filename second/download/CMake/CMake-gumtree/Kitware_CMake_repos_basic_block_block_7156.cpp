f(nread == 0) {
      connssl->recv_connection_closed = true;
      infof(data, "schannel: server closed the connection\n");
    }