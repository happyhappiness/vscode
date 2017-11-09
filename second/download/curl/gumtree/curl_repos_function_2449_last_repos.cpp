static CURLcode gskit_connect_step2(struct connectdata *conn, int sockindex,
                                    bool nonblocking)
{
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  Qso_OverlappedIO_t cstat;
  long timeout_ms;
  struct timeval stmv;
  CURLcode result;

  /* Poll or wait for end of SSL asynchronous handshake. */

  for(;;) {
    timeout_ms = nonblocking? 0: Curl_timeleft(data, NULL, TRUE);
    if(timeout_ms < 0)
      timeout_ms = 0;
    stmv.tv_sec = timeout_ms / 1000;
    stmv.tv_usec = (timeout_ms - stmv.tv_sec * 1000) * 1000;
    switch(QsoWaitForIOCompletion(BACKEND->iocport, &cstat, &stmv)) {
    case 1:             /* Operation complete. */
      break;
    case -1:            /* An error occurred: handshake still in progress. */
      if(errno == EINTR) {
        if(nonblocking)
          return CURLE_OK;
        continue;       /* Retry. */
      }
      if(errno != ETIME) {
        failf(data, "QsoWaitForIOCompletion() I/O error: %s", strerror(errno));
        cancel_async_handshake(conn, sockindex);
        close_async_handshake(connssl);
        return CURLE_SSL_CONNECT_ERROR;
      }
      /* FALL INTO... */
    case 0:             /* Handshake in progress, timeout occurred. */
      if(nonblocking)
        return CURLE_OK;
      cancel_async_handshake(conn, sockindex);
      close_async_handshake(connssl);
      return CURLE_OPERATION_TIMEDOUT;
    }
    break;
  }
  result = gskit_status(data, cstat.returnValue, "SSL handshake",
                        CURLE_SSL_CONNECT_ERROR);
  if(!result)
    connssl->connecting_state = ssl_connect_3;
  close_async_handshake(connssl);
  return result;
}