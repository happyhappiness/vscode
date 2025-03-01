static ssize_t mbed_recv(struct connectdata *conn, int num,
                         char *buf, size_t buffersize,
                         CURLcode *curlcode)
{
  int ret = -1;
  ssize_t len = -1;

  memset(buf, 0, buffersize);
  ret = mbedtls_ssl_read(&conn->ssl[num].ssl, (unsigned char *)buf,
                         buffersize);

  if(ret <= 0) {
    if(ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY)
      return 0;

    *curlcode = (ret == MBEDTLS_ERR_SSL_WANT_READ) ?
      CURLE_AGAIN : CURLE_RECV_ERROR;
    return -1;
  }

  len = ret;

  return len;
}