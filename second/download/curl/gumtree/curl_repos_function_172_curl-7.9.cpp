CURLcode Curl_write(struct connectdata *conn, int sockfd,
                    void *mem, size_t len,
                    size_t *written)
{
  size_t bytes_written;

#ifdef USE_SSLEAY
  /* SSL_write() is said to return 'int' while write() and send() returns
     'size_t' */
  int ssl_bytes;
  if (conn->ssl.use) {
    int loop=100; /* just a precaution to never loop endlessly */
    while(loop--) {
      ssl_bytes = SSL_write(conn->ssl.handle, mem, len);
      if((0 >= ssl_bytes) ||
         (SSL_ERROR_WANT_WRITE != SSL_get_error(conn->ssl.handle,
                                                ssl_bytes) )) {
        /* this converts from signed to unsigned... */
        bytes_written = ssl_bytes;
        break;
      }
    }
  }
  else {
#endif
#ifdef KRB4
    if(conn->sec_complete) {
      bytes_written = Curl_sec_write(conn, sockfd, mem, len);
    }
    else
#endif /* KRB4 */
      bytes_written = swrite(sockfd, mem, len);
#ifdef USE_SSLEAY
  }
#endif

  *written = bytes_written;
  return CURLE_OK;
}