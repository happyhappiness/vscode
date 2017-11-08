void Curl_ssl_close(struct connectdata *conn, int sockindex)
{
  DEBUGASSERT((sockindex <= 1) && (sockindex >= -1));

#ifdef USE_SSLEAY
  Curl_ossl_close(conn, sockindex);
#endif /* USE_SSLEAY */
#ifdef USE_GNUTLS
  Curl_gtls_close(conn, sockindex);
#endif /* USE_GNUTLS */
#ifdef USE_NSS
  Curl_nss_close(conn, sockindex);
#endif /* USE_NSS */
#ifdef USE_QSOSSL
  Curl_qsossl_close(conn, sockindex);
#endif /* USE_QSOSSL */
#ifndef USE_SSL
  (void)conn;
  (void)sockindex;
#endif /* !USE_SSL */
}