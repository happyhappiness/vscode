ssize_t Curl_ssl_send(struct connectdata *conn,
                      int sockindex,
                      void *mem,
                      size_t len)
{
#ifdef USE_SSLEAY
  return Curl_ossl_send(conn, sockindex, mem, len);
#else
#ifdef USE_GNUTLS
  return Curl_gtls_send(conn, sockindex, mem, len);
#else
#ifdef USE_NSS
  return Curl_nss_send(conn, sockindex, mem, len);
#else
#ifdef USE_QSOSSL
  return Curl_qsossl_send(conn, sockindex, mem, len);
#else
  (void)conn;
  (void)sockindex;
  (void)mem;
  (void)len;
  return 0;
#endif /* USE_QSOSSL */
#endif /* USE_NSS */
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
}