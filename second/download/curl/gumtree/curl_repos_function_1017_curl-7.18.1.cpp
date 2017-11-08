CURLcode
Curl_ssl_connect(struct connectdata *conn, int sockindex)
{
#ifdef USE_SSL
  /* mark this is being ssl enabled from here on. */
  conn->ssl[sockindex].use = TRUE;
  conn->ssl[sockindex].state = ssl_connection_negotiating;

#ifdef USE_SSLEAY
  return Curl_ossl_connect(conn, sockindex);
#else
#ifdef USE_GNUTLS
  return Curl_gtls_connect(conn, sockindex);
#else
#ifdef USE_NSS
  return Curl_nss_connect(conn, sockindex);
#else
#ifdef USE_QSOSSL
  return Curl_qsossl_connect(conn, sockindex);
#endif /* USE_QSOSSL */
#endif /* USE_NSS */
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */

#else
  /* without SSL */
  (void)conn;
  (void)sockindex;
  return CURLE_OK;
#endif /* USE_SSL */
}