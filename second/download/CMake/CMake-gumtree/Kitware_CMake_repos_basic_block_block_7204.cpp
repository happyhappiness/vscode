{
  CURLcode result;

  if(conn->bits.proxy_ssl_connected[sockindex]) {
    result = ssl_connect_init_proxy(conn, sockindex);
    if(result)
      return result;
  }

  if(!ssl_prefs_check(conn->data))
    return CURLE_SSL_CONNECT_ERROR;

  /* mark this is being ssl-enabled from here on. */
  conn->ssl[sockindex].use = TRUE;
  conn->ssl[sockindex].state = ssl_connection_negotiating;

  result = curlssl_connect(conn, sockindex);

  if(!result)
    Curl_pgrsTime(conn->data, TIMER_APPCONNECT); /* SSL is connected */

  return result;
}