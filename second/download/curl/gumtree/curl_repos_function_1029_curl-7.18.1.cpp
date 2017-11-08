ssize_t Curl_ssl_recv(struct connectdata *conn, /* connection data */
                      int sockindex,            /* socketindex */
                      char *mem,                /* store read data here */
                      size_t len)               /* max amount to read */
{
#ifdef USE_SSL
  ssize_t nread;
  bool block = FALSE;

#ifdef USE_SSLEAY
  nread = Curl_ossl_recv(conn, sockindex, mem, len, &block);
#else
#ifdef USE_GNUTLS
  nread = Curl_gtls_recv(conn, sockindex, mem, len, &block);
#else
#ifdef USE_NSS
  nread = Curl_nss_recv(conn, sockindex, mem, len, &block);
#else
#ifdef USE_QSOSSL
  nread = Curl_qsossl_recv(conn, sockindex, mem, len, &block);
#endif /* USE_QSOSSL */
#endif /* USE_NSS */
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
  if(nread == -1) {
    if(!block)
      return 0; /* this is a true error, not EWOULDBLOCK */
    else
      return -1;
  }

  return nread;

#else /* USE_SSL */
  (void)conn;
  (void)sockindex;
  (void)mem;
  (void)len;
  return 0;
#endif /* USE_SSL */
}