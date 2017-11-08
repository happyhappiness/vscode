static CURLcode
ossl_connect_common(struct connectdata *conn,
                    int sockindex,
                    bool nonblocking,
                    bool *done)
{
  CURLcode retcode;
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  curl_socket_t sockfd = conn->sock[sockindex];
  long timeout_ms;

  if(ssl_connect_1==connssl->connecting_state) {
    retcode = ossl_connect_step1(conn, sockindex);
    if(retcode)
      return retcode;
  }

  timeout_ms = 0;
  while(ssl_connect_2 == connssl->connecting_state ||
        ssl_connect_2_reading == connssl->connecting_state ||
        ssl_connect_2_writing == connssl->connecting_state) {

    /* if ssl is expecting something, check if it's available. */
    if(connssl->connecting_state == ssl_connect_2_reading
        || connssl->connecting_state == ssl_connect_2_writing) {

      int writefd = ssl_connect_2_writing==
        connssl->connecting_state?sockfd:CURL_SOCKET_BAD;
      int readfd = ssl_connect_2_reading==
        connssl->connecting_state?sockfd:CURL_SOCKET_BAD;

      while(1) {
        int what = Curl_socket_ready(readfd, writefd,
                                     nonblocking?0:(int)timeout_ms);
        if(what > 0)
          /* readable or writable, go loop in the outer loop */
          break;
        else if(0 == what) {
          if(nonblocking) {
            *done = FALSE;
            return CURLE_OK;
          }
          else {
            /* timeout */
            failf(data, "SSL connection timeout");
            return CURLE_OPERATION_TIMEDOUT;
          }
        }
        else {
          /* anything that gets here is fatally bad */
          failf(data, "select/poll on SSL socket, errno: %d", SOCKERRNO);
          return CURLE_SSL_CONNECT_ERROR;
        }
      } /* while()-loop for the select() */
    }

    /* get the timeout from step2 to avoid computing it twice. */
    retcode = ossl_connect_step2(conn, sockindex, &timeout_ms);
    if(retcode)
      return retcode;

  } /* repeat step2 until all transactions are done. */


  if(ssl_connect_3==connssl->connecting_state) {
    retcode = ossl_connect_step3(conn, sockindex);
    if(retcode)
      return retcode;
  }

  if(ssl_connect_done==connssl->connecting_state) {
    connssl->state = ssl_connection_complete;
    *done = TRUE;
  }
  else
    *done = FALSE;

  /* Reset our connect state machine */
  connssl->connecting_state = ssl_connect_1;

  return CURLE_OK;
}