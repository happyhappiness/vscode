CURLcode
Curl_axtls_connect(struct connectdata *conn,
                  int sockindex)

{
  CURLcode conn_step = connect_prep(conn, sockindex);
  int ssl_fcn_return;
  SSL *ssl = conn->ssl[sockindex].ssl;

  if(conn_step != CURLE_OK) {
    Curl_axtls_close(conn, sockindex);
    return conn_step;
  }

  /* Check to make sure handshake was ok. */
  while(ssl_handshake_status(ssl) != SSL_OK) {
    ssl_fcn_return = ssl_read(ssl, NULL);
    if(ssl_fcn_return < 0) {
      Curl_axtls_close(conn, sockindex);
      ssl_display_error(ssl_fcn_return); /* goes to stdout. */
      return map_error_to_curl(ssl_fcn_return);
    }
    usleep(10000);
    /* TODO: check for timeout as this could hang indefinitely otherwise */
  }
  infof (conn->data, "handshake completed successfully\n");

  conn_step = connect_finish(conn, sockindex);
  if(conn_step != CURLE_OK) {
    Curl_axtls_close(conn, sockindex);
    return conn_step;
  }

  return CURLE_OK;
}