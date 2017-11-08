static ssize_t qsossl_recv(struct connectdata * conn, int num, char * buf,
                           size_t buffersize, CURLcode * curlcode)

{
  char error_buffer[120]; /* OpenSSL documents that this must be at
                             least 120 bytes long. */
  unsigned long sslerror;
  int buffsize;
  int nread;

  buffsize = (buffersize > (size_t)INT_MAX) ? INT_MAX : (int)buffersize;
  nread = SSL_Read(conn->ssl[num].handle, buf, buffsize);

  if(nread < 0) {
    /* failed SSL_read */

    switch (nread) {

    case SSL_ERROR_BAD_STATE:
      /* there's data pending, re-invoke SSL_Read(). */
      *curlcode = CURLE_AGAIN;
      return -1;

    case SSL_ERROR_IO:
      switch (errno) {
      case EWOULDBLOCK:
        *curlcode = CURLE_AGAIN;
        return -1;
        }

      failf(conn->data, "SSL_Read() I/O error: %s", strerror(errno));
      *curlcode = CURLE_RECV_ERROR;
      return -1;

    default:
      failf(conn->data, "SSL read error: %s", SSL_Strerror(nread, NULL));
      *curlcode = CURLE_RECV_ERROR;
      return -1;
    }
  }
  return (ssize_t) nread;
}