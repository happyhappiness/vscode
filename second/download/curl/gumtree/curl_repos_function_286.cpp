ssize_t Curl_ossl_recv(struct connectdata *conn, /* connection data */
                       int num,                  /* socketindex */
                       char *buf,                /* store read data here */
                       size_t buffersize,        /* max amount to read */
                       bool *wouldblock)
{
  char error_buffer[120]; /* OpenSSL documents that this must be at
                             least 120 bytes long. */
  unsigned long sslerror;
  ssize_t nread = (ssize_t)SSL_read(conn->ssl[num].handle, buf,
                                    (int)buffersize);
  *wouldblock = FALSE;
  if(nread < 0) {
    /* failed SSL_read */
    int err = SSL_get_error(conn->ssl[num].handle, (int)nread);

    switch(err) {
    case SSL_ERROR_NONE: /* this is not an error */
    case SSL_ERROR_ZERO_RETURN: /* no more data */
      break;
    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE:
      /* there's data pending, re-invoke SSL_read() */
      *wouldblock = TRUE;
      return -1; /* basically EWOULDBLOCK */
    default:
      /* openssl/ssl.h says "look at error stack/return value/errno" */
      sslerror = ERR_get_error();
      failf(conn->data, "SSL read: %s, errno %d",
            ERR_error_string(sslerror, error_buffer),
            Curl_ourerrno() );
      return -1;
    }
  }
  return nread;
}