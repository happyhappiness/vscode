static ssize_t ossl_recv(struct connectdata *conn, /* connection data */
                         int num,                  /* socketindex */
                         char *buf,                /* store read data here */
                         size_t buffersize,        /* max amount to read */
                         CURLcode *curlcode)
{
  char error_buffer[256];
  unsigned long sslerror;
  ssize_t nread;
  int buffsize;
  struct ssl_connect_data *connssl = &conn->ssl[num];

  ERR_clear_error();

  buffsize = (buffersize > (size_t)INT_MAX) ? INT_MAX : (int)buffersize;
  nread = (ssize_t)SSL_read(BACKEND->handle, buf, buffsize);
  if(nread <= 0) {
    /* failed SSL_read */
    int err = SSL_get_error(BACKEND->handle, (int)nread);

    switch(err) {
    case SSL_ERROR_NONE: /* this is not an error */
    case SSL_ERROR_ZERO_RETURN: /* no more data */
      break;
    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE:
      /* there's data pending, re-invoke SSL_read() */
      *curlcode = CURLE_AGAIN;
      return -1;
    default:
      /* openssl/ssl.h for SSL_ERROR_SYSCALL says "look at error stack/return
         value/errno" */
      /* https://www.openssl.org/docs/crypto/ERR_get_error.html */
      sslerror = ERR_get_error();
      if((nread < 0) || sslerror) {
        /* If the return code was negative or there actually is an error in the
           queue */
        failf(conn->data, OSSL_PACKAGE " SSL_read: %s, errno %d",
              (sslerror ?
               ossl_strerror(sslerror, error_buffer, sizeof(error_buffer)) :
               SSL_ERROR_to_str(err)),
              SOCKERRNO);
        *curlcode = CURLE_RECV_ERROR;
        return -1;
      }
    }
  }
  return nread;
}