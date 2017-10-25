int Curl_ossl_send(struct connectdata *conn,
                   int sockindex,
                   void *mem,
                   size_t len)
{
  /* SSL_write() is said to return 'int' while write() and send() returns
     'size_t' */
  int err;
  char error_buffer[120]; /* OpenSSL documents that this must be at least 120
                             bytes long. */
  unsigned long sslerror;
  int rc = SSL_write(conn->ssl[sockindex].handle, mem, (int)len);

  if(rc < 0) {
    err = SSL_get_error(conn->ssl[sockindex].handle, rc);

    switch(err) {
    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE:
      /* The operation did not complete; the same TLS/SSL I/O function
         should be called again later. This is basicly an EWOULDBLOCK
         equivalent. */
      return 0;
    case SSL_ERROR_SYSCALL:
      failf(conn->data, "SSL_write() returned SYSCALL, errno = %d\n",
            Curl_ourerrno());
      return -1;
    case SSL_ERROR_SSL:
      /*  A failure in the SSL library occurred, usually a protocol error.
          The OpenSSL error queue contains more information on the error. */
      sslerror = ERR_get_error();
      failf(conn->data, "SSL_write() error: %s\n",
            ERR_error_string(sslerror, error_buffer));
      return -1;
    }
    /* a true error */
    failf(conn->data, "SSL_write() return error %d\n", err);
    return -1;
  }
  return rc; /* number of bytes */
}