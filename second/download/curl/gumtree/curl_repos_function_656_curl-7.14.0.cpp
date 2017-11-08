int Curl_ssl_send(struct connectdata *conn,
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
  (void)conn;
  (void)sockindex;
  (void)mem;
  (void)len;
  return 0;
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
}