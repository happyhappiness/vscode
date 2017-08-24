{
  int rc;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  /* Initiate the connection, if not already done */
  if(ssl_connect_1==connssl->connecting_state) {
    rc = gtls_connect_step1(conn, sockindex);
    if(rc)
      return rc;
  }

  rc = handshake(conn, sockindex, TRUE, nonblocking);
  if(rc)
    /* handshake() sets its own error message with failf() */
    return rc;

  /* Finish connecting once the handshake is done */
  if(ssl_connect_1==connssl->connecting_state) {
    rc = gtls_connect_step3(conn, sockindex);
    if(rc)
      return rc;
  }

  *done = ssl_connect_1==connssl->connecting_state;

  return CURLE_OK;
}