{
  struct ssl_connect_data *connssl = &conn->ssl[FIRSTSOCKET];

  if(!numsocks)
    return GETSOCK_BLANK;

  if(connssl->connecting_state == ssl_connect_2_writing) {
    /* write mode */
    socks[0] = conn->sock[FIRSTSOCKET];
    return GETSOCK_WRITESOCK(0);
  }
  if(connssl->connecting_state == ssl_connect_2_reading) {
    /* read mode */
    socks[0] = conn->sock[FIRSTSOCKET];
    return GETSOCK_READSOCK(0);
  }

  return GETSOCK_BLANK;
}