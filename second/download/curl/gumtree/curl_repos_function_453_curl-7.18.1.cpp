static CURLcode Curl_qsossl_create(struct connectdata * conn, int sockindex)

{
  SSLHandle * h;
  struct ssl_connect_data * connssl = &conn->ssl[sockindex];

  h = SSL_Create(conn->sock[sockindex], SSL_ENCRYPT);

  if(!h) {
    failf(conn->data, "SSL_Create() I/O error: %s", strerror(errno));
    return CURLE_SSL_CONNECT_ERROR;
  }

  connssl->handle = h;
  return CURLE_OK;
}