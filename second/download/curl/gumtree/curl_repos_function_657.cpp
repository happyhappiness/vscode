int Curl_ssl_recv(struct connectdata *conn, /* connection data */
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
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
  if(nread == -1) {
    infof(conn->data, "Curl_xxx_rcvs returned -1, block = %s\n",
          block?"TRUE":"FALSE");
    if(!block)
      return 0; /* this is a true error, not EWOULDBLOCK */
    else
      return -1;
  }

  return (int)nread;

#else /* USE_SSL */
  (void)conn;
  (void)sockindex;
  (void)mem;
  (void)len;
  return 0;
#endif /* USE_SSL */
}