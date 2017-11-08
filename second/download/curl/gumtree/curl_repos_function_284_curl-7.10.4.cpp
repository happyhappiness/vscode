int Curl_read(struct connectdata *conn,
              int sockfd,
              char *buf,
              size_t buffersize,
              ssize_t *n)
{
  ssize_t nread;
  *n=0; /* reset amount to zero */

#ifdef USE_SSLEAY
  if (conn->ssl.use) {
    nread = SSL_read(conn->ssl.handle, buf, buffersize);

    if(nread < 0) {
      /* failed SSL_read */
      int err = SSL_get_error(conn->ssl.handle, nread);

      switch(err) {
      case SSL_ERROR_NONE: /* this is not an error */
      case SSL_ERROR_ZERO_RETURN: /* no more data */
        break;
      case SSL_ERROR_WANT_READ:
      case SSL_ERROR_WANT_WRITE:
        /* there's data pending, re-invoke SSL_read() */
        return -1; /* basicly EWOULDBLOCK */
      default:
        failf(conn->data, "SSL read error: %d", err);
        return CURLE_RECV_ERROR;
      }
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

    if(-1 == nread) {
#ifdef WIN32
      if(WSAEWOULDBLOCK == GetLastError())
#else
      if(EWOULDBLOCK == errno)
#endif
        return -1;
    }

#ifdef USE_SSLEAY
  }
#endif /* USE_SSLEAY */
  *n = nread;
  return CURLE_OK;
}