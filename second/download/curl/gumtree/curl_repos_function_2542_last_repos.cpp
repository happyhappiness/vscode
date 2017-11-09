static CURLcode Curl_axtls_connect_nonblocking(struct connectdata *conn,
                                               int sockindex, bool *done)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  CURLcode conn_step;
  int ssl_fcn_return;
  int i;

 *done = FALSE;
  /* connectdata is calloc'd and connecting_state is only changed in this
     function, so this is safe, as the state is effectively initialized. */
  if(connssl->connecting_state == ssl_connect_1) {
    conn_step = connect_prep(conn, sockindex);
    if(conn_step != CURLE_OK) {
      Curl_axtls_close(conn, sockindex);
      return conn_step;
    }
    connssl->connecting_state = ssl_connect_2;
  }

  if(connssl->connecting_state == ssl_connect_2) {
    /* Check to make sure handshake was ok. */
    if(ssl_handshake_status(BACKEND->ssl) != SSL_OK) {
      /* Loop to perform more work in between sleeps. This is work around the
         fact that axtls does not expose any knowledge about when work needs
         to be performed. This can save ~25% of time on SSL handshakes. */
      for(i = 0; i<5; i++) {
        ssl_fcn_return = ssl_read(BACKEND->ssl, NULL);
        if(ssl_fcn_return < 0) {
          Curl_axtls_close(conn, sockindex);
          ssl_display_error(ssl_fcn_return); /* goes to stdout. */
          return map_error_to_curl(ssl_fcn_return);
        }
        return CURLE_OK;
      }
    }
    infof(conn->data, "handshake completed successfully\n");
    connssl->connecting_state = ssl_connect_3;
  }

  if(connssl->connecting_state == ssl_connect_3) {
    conn_step = connect_finish(conn, sockindex);
    if(conn_step != CURLE_OK) {
      Curl_axtls_close(conn, sockindex);
      return conn_step;
    }

    /* Reset connect state */
    connssl->connecting_state = ssl_connect_1;

    *done = TRUE;
    return CURLE_OK;
  }

  /* Unrecognized state.  Things are very bad. */
  connssl->state  = ssl_connection_none;
  connssl->connecting_state = ssl_connect_1;
  /* Return value perhaps not strictly correct, but distinguishes the issue.*/
  return CURLE_BAD_FUNCTION_ARGUMENT;
}