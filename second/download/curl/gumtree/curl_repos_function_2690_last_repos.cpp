static ssize_t polarssl_recv(struct connectdata *conn,
                             int num,
                             char *buf,
                             size_t buffersize,
                             CURLcode *curlcode)
{
  struct ssl_connect_data *connssl = &conn->ssl[num];
  int ret = -1;
  ssize_t len = -1;

  memset(buf, 0, buffersize);
  ret = ssl_read(&BACKEND->ssl, (unsigned char *)buf, buffersize);

  if(ret <= 0) {
    if(ret == POLARSSL_ERR_SSL_PEER_CLOSE_NOTIFY)
      return 0;

    *curlcode = (ret == POLARSSL_ERR_NET_WANT_READ) ?
      CURLE_AGAIN : CURLE_RECV_ERROR;
    return -1;
  }

  len = ret;

  return len;
}