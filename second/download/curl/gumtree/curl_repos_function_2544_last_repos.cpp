static ssize_t axtls_send(struct connectdata *conn,
                          int sockindex,
                          const void *mem,
                          size_t len,
                          CURLcode *err)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  /* ssl_write() returns 'int' while write() and send() returns 'size_t' */
  int rc = ssl_write(BACKEND->ssl, mem, (int)len);

  infof(conn->data, "  axtls_send\n");

  if(rc < 0) {
    *err = map_error_to_curl(rc);
    rc = -1; /* generic error code for send failure */
  }

  *err = CURLE_OK;
  return rc;
}