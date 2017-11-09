static CURLcode Curl_axtls_connect(struct connectdata *conn, int sockindex)
{
  struct Curl_easy *data = conn->data;
  CURLcode conn_step = connect_prep(conn, sockindex);
  int ssl_fcn_return;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  SSL *ssl = BACKEND->ssl;
  long timeout_ms;

  if(conn_step != CURLE_OK) {
    Curl_axtls_close(conn, sockindex);
    return conn_step;
  }

  /* Check to make sure handshake was ok. */
  while(ssl_handshake_status(ssl) != SSL_OK) {
    /* check allowed time left */
    timeout_ms = Curl_timeleft(data, NULL, TRUE);

    if(timeout_ms < 0) {
      /* no need to continue if time already is up */
      failf(data, "SSL connection timeout");
      return CURLE_OPERATION_TIMEDOUT;
    }

    ssl_fcn_return = ssl_read(ssl, NULL);
    if(ssl_fcn_return < 0) {
      Curl_axtls_close(conn, sockindex);
      ssl_display_error(ssl_fcn_return); /* goes to stdout. */
      return map_error_to_curl(ssl_fcn_return);
    }
    /* TODO: avoid polling */
    Curl_wait_ms(10);
  }
  infof(conn->data, "handshake completed successfully\n");

  conn_step = connect_finish(conn, sockindex);
  if(conn_step != CURLE_OK) {
    Curl_axtls_close(conn, sockindex);
    return conn_step;
  }

  return CURLE_OK;
}