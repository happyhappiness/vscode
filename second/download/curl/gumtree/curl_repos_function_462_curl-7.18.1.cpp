ssize_t Curl_qsossl_recv(struct connectdata * conn, int num, char * buf,
                         size_t buffersize, bool * wouldblock)

{
  char error_buffer[120]; /* OpenSSL documents that this must be at
                             least 120 bytes long. */
  unsigned long sslerror;
  int nread;

  nread = SSL_Read(conn->ssl[num].handle, buf, (int) buffersize);
  *wouldblock = FALSE;

  if(nread < 0) {
    /* failed SSL_read */

    switch (nread) {

    case SSL_ERROR_BAD_STATE:
      /* there's data pending, re-invoke SSL_Read(). */
      *wouldblock = TRUE;
      return -1; /* basically EWOULDBLOCK */

    case SSL_ERROR_IO:
      switch (errno) {
      case EWOULDBLOCK:
        *wouldblock = TRUE;
        return -1;
        }

      failf(conn->data, "SSL_Read() I/O error: %s", strerror(errno));
      return -1;

    default:
      failf(conn->data, "SSL read error: %s", SSL_Strerror(nread, NULL));
      return -1;
    }
  }
  return (ssize_t) nread;
}