CURLcode Curl_ssl_shutdown(struct connectdata *conn, int sockindex)
{
#ifdef USE_SSLEAY
  if(Curl_ossl_shutdown(conn, sockindex))
    return CURLE_SSL_SHUTDOWN_FAILED;
#else
#ifdef USE_GNUTLS
  if(Curl_gtls_shutdown(conn, sockindex))
    return CURLE_SSL_SHUTDOWN_FAILED;
#else
#ifdef USE_QSOSSL
  if(Curl_qsossl_shutdown(conn, sockindex))
    return CURLE_SSL_SHUTDOWN_FAILED;
#endif /* USE_QSOSSL */
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */

  conn->ssl[sockindex].use = FALSE; /* get back to ordinary socket usage */
  conn->ssl[sockindex].state = ssl_connection_none;

  return CURLE_OK;
}