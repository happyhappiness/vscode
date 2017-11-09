static ssize_t ossl_send(struct connectdata *conn,
                         int sockindex,
                         const void *mem,
                         size_t len,
                         CURLcode *curlcode)
{
  /* SSL_write() is said to return 'int' while write() and send() returns
     'size_t' */
  int err;
  char error_buffer[256];
  unsigned long sslerror;
  int memlen;
  int rc;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  ERR_clear_error();

  memlen = (len > (size_t)INT_MAX) ? INT_MAX : (int)len;
  rc = SSL_write(BACKEND->handle, mem, memlen);

  if(rc <= 0) {
    err = SSL_get_error(BACKEND->handle, rc);

    switch(err) {
    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE:
      /* The operation did not complete; the same TLS/SSL I/O function
         should be called again later. This is basically an EWOULDBLOCK
         equivalent. */
      *curlcode = CURLE_AGAIN;
      return -1;
    case SSL_ERROR_SYSCALL:
      failf(conn->data, "SSL_write() returned SYSCALL, errno = %d",
            SOCKERRNO);
      *curlcode = CURLE_SEND_ERROR;
      return -1;
    case SSL_ERROR_SSL:
      /*  A failure in the SSL library occurred, usually a protocol error.
          The OpenSSL error queue contains more information on the error. */
      sslerror = ERR_get_error();
      if(ERR_GET_LIB(sslerror) == ERR_LIB_SSL &&
         ERR_GET_REASON(sslerror) == SSL_R_BIO_NOT_SET &&
         conn->ssl[sockindex].state == ssl_connection_complete &&
         conn->proxy_ssl[sockindex].state == ssl_connection_complete) {
        char ver[120];
        Curl_ossl_version(ver, 120);
        failf(conn->data, "Error: %s does not support double SSL tunneling.",
              ver);
      }
      else
        failf(conn->data, "SSL_write() error: %s",
              ossl_strerror(sslerror, error_buffer, sizeof(error_buffer)));
      *curlcode = CURLE_SEND_ERROR;
      return -1;
    }
    /* a true error */
    failf(conn->data, OSSL_PACKAGE " SSL_write: %s, errno %d",
          SSL_ERROR_to_str(err), SOCKERRNO);
    *curlcode = CURLE_SEND_ERROR;
    return -1;
  }
  *curlcode = CURLE_OK;
  return (ssize_t)rc; /* number of bytes */
}