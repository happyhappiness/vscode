ssize_t Curl_qsossl_send(struct connectdata * conn, int sockindex, void * mem,
                         size_t len)

{
  /* SSL_Write() is said to return 'int' while write() and send() returns
     'size_t' */
  int rc;

  rc = SSL_Write(conn->ssl[sockindex].handle, mem, (int) len);

  if(rc < 0) {
    switch(rc) {

    case SSL_ERROR_BAD_STATE:
      /* The operation did not complete; the same SSL I/O function
         should be called again later. This is basicly an EWOULDBLOCK
         equivalent. */
      return 0;

    case SSL_ERROR_IO:
      switch (errno) {
      case EWOULDBLOCK:
      case EINTR:
        return 0;
        }

      failf(conn->data, "SSL_Write() I/O error: %s", strerror(errno));
      return -1;
    }

    /* An SSL error. */
    failf(conn->data, "SSL_Write() returned error %d",
          SSL_Strerror(rc, NULL));
    return -1;
  }

  return (ssize_t) rc; /* number of bytes */
}