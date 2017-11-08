CURLcode
Curl_ssl_connect(struct connectdata *conn, int sockindex)
{
  CURLcode res;
  /* mark this is being ssl-enabled from here on. */
  conn->ssl[sockindex].use = TRUE;
  conn->ssl[sockindex].state = ssl_connection_negotiating;

  res = curlssl_connect(conn, sockindex);

  if(!res)
    Curl_pgrsTime(conn->data, TIMER_APPCONNECT); /* SSL is connected */

  return res;
}