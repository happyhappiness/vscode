static ssize_t axtls_recv(struct connectdata *conn, /* connection data */
                          int num,                  /* socketindex */
                          char *buf,                /* store read data here */
                          size_t buffersize,        /* max amount to read */
                          CURLcode *err)
{
  struct ssl_connect_data *connssl = &conn->ssl[num];
  ssize_t ret = 0;
  uint8_t *read_buf;

  infof(conn->data, "  axtls_recv\n");

  *err = CURLE_OK;
  if(connssl) {
    ret = ssl_read(BACKEND->ssl, &read_buf);
    if(ret > SSL_OK) {
      /* ssl_read returns SSL_OK if there is more data to read, so if it is
         larger, then all data has been read already.  */
      memcpy(buf, read_buf,
             (size_t)ret > buffersize ? buffersize : (size_t)ret);
    }
    else if(ret == SSL_OK) {
      /* more data to be read, signal caller to call again */
      *err = CURLE_AGAIN;
      ret = -1;
    }
    else if(ret == -3) {
      /* With patched axTLS, SSL_CLOSE_NOTIFY=-3.  Hard-coding until axTLS
         team approves proposed fix. */
      Curl_axtls_close(conn, num);
    }
    else {
      failf(conn->data, "axTLS recv error (%d)", ret);
      *err = map_error_to_curl((int) ret);
      ret = -1;
    }
  }

  return ret;
}