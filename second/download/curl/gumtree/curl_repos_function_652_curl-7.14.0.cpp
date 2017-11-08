void Curl_ssl_close(struct connectdata *conn)
{
  if(conn->ssl[FIRSTSOCKET].use) {
#ifdef USE_SSLEAY
    Curl_ossl_close(conn);
#else
#ifdef USE_GNUTLS
    Curl_gtls_close(conn);
#else
  (void)conn;
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
  }
}