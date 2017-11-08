CURLcode
Curl_ssl_connect_nonblocking(struct connectdata *conn, int sockindex,
                             bool *done)
{
  CURLcode res;
  /* mark this is being ssl requested from here on. */
  conn->ssl[sockindex].use = TRUE;
#ifdef curlssl_connect_nonblocking
  res = curlssl_connect_nonblocking(conn, sockindex, done);
#else
  *done = TRUE; /* fallback to BLOCKING */
  res = curlssl_connect(conn, sockindex);
#endif /* non-blocking connect support */
  if(!res && *done)
    Curl_pgrsTime(conn->data, TIMER_APPCONNECT); /* SSL is connected */
  return res;
}