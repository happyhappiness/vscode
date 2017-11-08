CURLcode Curl_write(struct connectdata *conn, int sockfd,
                    void *mem, size_t len,
                    ssize_t *written)
{
  ssize_t bytes_written;

#ifdef USE_SSLEAY
  /* SSL_write() is said to return 'int' while write() and send() returns
     'size_t' */
  if (conn->ssl.use) {
    int err;
    int rc = SSL_write(conn->ssl.handle, mem, len);

    if(rc < 0) {
      err = SSL_get_error(conn->ssl.handle, rc);
    
      switch(err) {
      case SSL_ERROR_WANT_READ:
      case SSL_ERROR_WANT_WRITE:
        /* this is basicly the EWOULDBLOCK equivalent */
        *written = 0;
        return CURLE_OK;
      case SSL_ERROR_SYSCALL:
        failf(conn->data, "SSL_write() returned SYSCALL, errno = %d\n", errno);
        return CURLE_SEND_ERROR;
      }
      /* a true error */
      failf(conn->data, "SSL_write() return error %d\n", err);
      return CURLE_SEND_ERROR;
    }
    bytes_written = rc;
  }
  else {
#endif
#ifdef KRB4
    if(conn->sec_complete) {
      bytes_written = Curl_sec_write(conn, sockfd, mem, len);
    }
    else
#endif /* KRB4 */
    {
      bytes_written = swrite(sockfd, mem, len);
    }
    if(-1 == bytes_written) {
#ifdef WIN32
      if(WSAEWOULDBLOCK == GetLastError())
#else
      /* As pointed out by Christophe Demory on March 11 2003, errno
         may be EWOULDBLOCK or on some systems EAGAIN when it returned
         due to its inability to send off data without blocking. We
         therefor treat both error codes the same here */
      if((EWOULDBLOCK == errno) || (EAGAIN == errno))
#endif
      {
        /* this is just a case of EWOULDBLOCK */
        *written=0;
        return CURLE_OK;
      }
    }
#ifdef USE_SSLEAY
  }
#endif

  *written = bytes_written;
  return (-1 != bytes_written)?CURLE_OK:CURLE_SEND_ERROR;
}