ssize_t Curl_gtls_recv(struct connectdata *conn, /* connection data */
                       int num,                  /* socketindex */
                       char *buf,                /* store read data here */
                       size_t buffersize,        /* max amount to read */
                       bool *wouldblock)
{
  ssize_t ret;

  ret = gnutls_record_recv(conn->ssl[num].session, buf, buffersize);
  if((ret == GNUTLS_E_AGAIN) || (ret == GNUTLS_E_INTERRUPTED)) {
    *wouldblock = TRUE;
    return -1;
  }

  if(ret == GNUTLS_E_REHANDSHAKE) {
    /* BLOCKING call, this is bad but a work-around for now. Fixing this "the
       proper way" takes a whole lot of work. */
    CURLcode rc = handshake(conn, conn->ssl[num].session, num, FALSE);
    if(rc)
      /* handshake() writes error message on its own */
      return rc;
    *wouldblock = TRUE; /* then return as if this was a wouldblock */
    return -1;
  }

  *wouldblock = FALSE;
  if(!ret) {
    failf(conn->data, "Peer closed the TLS connection");
    return -1;
  }

  if(ret < 0) {
    failf(conn->data, "GnuTLS recv error (%d): %s",
          (int)ret, gnutls_strerror(ret));
    return -1;
  }

  return ret;
}