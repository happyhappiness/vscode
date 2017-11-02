CURLcode
Curl_ssl_connect_nonblocking(struct connectdata *conn, int sockindex,
                             bool *done)
{
  CURLcode result;
  /* mark this is being ssl requested from here on. */
  conn->ssl[sockindex].use = TRUE;
#ifdef curlssl_connect_nonblocking
  result = curlssl_connect_nonblocking(conn, sockindex, done);
#else
  *done = TRUE; /* fallback to BLOCKING */
  result = curlssl_connect(conn, sockindex);
#endif /* non-blocking connect support */
  if(!result && *done)
    Curl_pgrsTime(conn->data, TIMER_APPCONNECT); /* SSL is connected */
  return result;
}