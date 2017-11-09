static ssize_t cyassl_recv(struct connectdata *conn,
                           int num,
                           char *buf,
                           size_t buffersize,
                           CURLcode *curlcode)
{
  struct ssl_connect_data *connssl = &conn->ssl[num];
  char error_buffer[CYASSL_MAX_ERROR_SZ];
  int  buffsize = (buffersize > (size_t)INT_MAX) ? INT_MAX : (int)buffersize;
  int  nread    = SSL_read(BACKEND->handle, buf, buffsize);

  if(nread < 0) {
    int err = SSL_get_error(BACKEND->handle, nread);

    switch(err) {
    case SSL_ERROR_ZERO_RETURN: /* no more data */
      break;
    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE:
      /* there's data pending, re-invoke SSL_read() */
      *curlcode = CURLE_AGAIN;
      return -1;
    default:
      failf(conn->data, "SSL read: %s, errno %d",
            ERR_error_string(err, error_buffer),
            SOCKERRNO);
      *curlcode = CURLE_RECV_ERROR;
      return -1;
    }
  }
  return nread;
}