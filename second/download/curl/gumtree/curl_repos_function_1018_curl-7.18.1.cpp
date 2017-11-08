CURLcode
Curl_ssl_connect_nonblocking(struct connectdata *conn, int sockindex,
                             bool *done)
{
#if defined(USE_SSL) && defined(USE_SSLEAY)
  /* mark this is being ssl enabled from here on. */
  conn->ssl[sockindex].use = TRUE;
  return Curl_ossl_connect_nonblocking(conn, sockindex, done);

#else
#ifdef USE_NSS
  *done = TRUE; /* fallback to BLOCKING */
  conn->ssl[sockindex].use = TRUE;
  return Curl_nss_connect(conn, sockindex);
#else
#ifdef USE_QSOSSL
  *done = TRUE; /* fallback to BLOCKING */
  conn->ssl[sockindex].use = TRUE;
  return Curl_qsossl_connect(conn, sockindex);
#else
  /* not implemented!
     fallback to BLOCKING call. */
  *done = TRUE;
  conn->ssl[sockindex].use = TRUE;
  return Curl_ssl_connect(conn, sockindex);
#endif /* USE_QSOSSL */
#endif /* USE_NSS */
#endif /* USE_SSLEAY */
}