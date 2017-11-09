static ssize_t gtls_send(struct connectdata *conn,
                         int sockindex,
                         const void *mem,
                         size_t len,
                         CURLcode *curlcode)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  ssize_t rc = gnutls_record_send(BACKEND->session, mem, len);

  if(rc < 0) {
    *curlcode = (rc == GNUTLS_E_AGAIN)
      ? CURLE_AGAIN
      : CURLE_SEND_ERROR;

    rc = -1;
  }

  return rc;
}