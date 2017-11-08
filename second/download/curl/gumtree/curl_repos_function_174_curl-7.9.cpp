CURLcode Curl_read(struct connectdata *conn, int sockfd,
                   char *buf, size_t buffersize,
                   ssize_t *n)
{
  ssize_t nread;

#ifdef USE_SSLEAY
  if (conn->ssl.use) {
    int loop=100; /* just a precaution to never loop endlessly */
    while(loop--) {
      nread = SSL_read(conn->ssl.handle, buf, buffersize);
      if((-1 != nread) ||
         (SSL_ERROR_WANT_READ != SSL_get_error(conn->ssl.handle, nread) ))
        break;
    }
  }
  else {
#endif
#ifdef KRB4
    if(conn->sec_complete)
      nread = Curl_sec_read(conn, sockfd, buf, buffersize);
    else
#endif
      nread = sread (sockfd, buf, buffersize);
#ifdef USE_SSLEAY
  }
#endif /* USE_SSLEAY */
  *n = nread;
  return CURLE_OK;
}