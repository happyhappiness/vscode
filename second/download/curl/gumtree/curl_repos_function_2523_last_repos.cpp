static ssize_t cyassl_send(struct connectdata *conn,
                           int sockindex,
                           const void *mem,
                           size_t len,
                           CURLcode *curlcode)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  char error_buffer[CYASSL_MAX_ERROR_SZ];
  int  memlen = (len > (size_t)INT_MAX) ? INT_MAX : (int)len;
  int  rc     = SSL_write(BACKEND->handle, mem, memlen);

  if(rc < 0) {
    int err = SSL_get_error(BACKEND->handle, rc);

    switch(err) {
    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE:
      /* there's data pending, re-invoke SSL_write() */
      *curlcode = CURLE_AGAIN;
      return -1;
    default:
      failf(conn->data, "SSL write: %s, errno %d",
            ERR_error_string(err, error_buffer),
            SOCKERRNO);
      *curlcode = CURLE_SEND_ERROR;
      return -1;
    }
  }
  return rc;
}