{
    connssl->state = ssl_connection_complete;
    conn->recv[sockindex] = polarssl_recv;
    conn->send[sockindex] = polarssl_send;
    *done = TRUE;
  }