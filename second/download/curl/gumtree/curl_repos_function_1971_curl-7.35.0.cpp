static ssize_t qsossl_send(struct connectdata * conn, int sockindex,
                           const void * mem, size_t len, CURLcode * curlcode)

{
  /* SSL_Write() is said to return 'int' while write() and send() returns
     'size_t' */
  int rc;

  rc = SSL_Write(conn->ssl[sockindex].handle, (void *) mem, (int) len);

  if(rc < 0) {
    switch(rc) {

    case SSL_ERROR_BAD_STATE:
      /* The operation did not complete; the same SSL I/O function
         should be called again later. This is basically an EWOULDBLOCK
         equivalent. */
      *curlcode = CURLE_AGAIN;
      return -1;

    case SSL_ERROR_IO:
      switch (errno) {
      case EWOULDBLOCK:
      case EINTR:
        *curlcode = CURLE_AGAIN;
        return -1;
        }

      failf(conn->data, "SSL_Write() I/O error: %s", strerror(errno));
      *curlcode = CURLE_SEND_ERROR;
      return -1;
    }

    /* An SSL error. */
    failf(conn->data, "SSL_Write() returned error %s",
          SSL_Strerror(rc, NULL));
    *curlcode = CURLE_SEND_ERROR;
    return -1;
  }

  return (ssize_t) rc; /* number of bytes */
}