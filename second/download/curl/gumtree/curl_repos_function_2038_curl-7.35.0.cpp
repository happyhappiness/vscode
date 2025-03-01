static CURLcode gskit_connect_common(struct connectdata *conn, int sockindex,
                                     bool nonblocking, bool *done)
{
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  long timeout_ms;
  Qso_OverlappedIO_t cstat;
  CURLcode cc = CURLE_OK;

  *done = connssl->state == ssl_connection_complete;
  if(*done)
    return CURLE_OK;

  /* Step 1: create session, start handshake. */
  if(connssl->connecting_state == ssl_connect_1) {
    /* check allowed time left */
    timeout_ms = Curl_timeleft(data, NULL, TRUE);

    if(timeout_ms < 0) {
      /* no need to continue if time already is up */
      failf(data, "SSL connection timeout");
      cc = CURLE_OPERATION_TIMEDOUT;
    }
    else
      cc = gskit_connect_step1(conn, sockindex);
  }

  /* Step 2: check if handshake is over. */
  if(cc == CURLE_OK && connssl->connecting_state == ssl_connect_2) {
    /* check allowed time left */
    timeout_ms = Curl_timeleft(data, NULL, TRUE);

    if(timeout_ms < 0) {
      /* no need to continue if time already is up */
      failf(data, "SSL connection timeout");
      cc = CURLE_OPERATION_TIMEDOUT;
    }
    else
      cc = gskit_connect_step2(conn, sockindex, nonblocking);
  }

  /* Step 3: gather certificate info, verify host. */
  if(cc == CURLE_OK && connssl->connecting_state == ssl_connect_3)
    cc = gskit_connect_step3(conn, sockindex);

  if(cc != CURLE_OK)
    close_one(connssl, data);
  else if(connssl->connecting_state == ssl_connect_done) {
    connssl->state = ssl_connection_complete;
    connssl->connecting_state = ssl_connect_1;
    conn->recv[sockindex] = gskit_recv;
    conn->send[sockindex] = gskit_send;
    *done = TRUE;
  }

  return cc;
}