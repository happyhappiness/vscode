void Curl_nss_close(struct connectdata *conn, int sockindex)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  struct ssl_connect_data *connssl_proxy = &conn->proxy_ssl[sockindex];

  if(connssl->handle || connssl_proxy->handle) {
    /* NSS closes the socket we previously handed to it, so we must mark it
       as closed to avoid double close */
    fake_sclose(conn->sock[sockindex]);
    conn->sock[sockindex] = CURL_SOCKET_BAD;
  }

  if(connssl->handle)
    /* nss_close(connssl) will transitively close also connssl_proxy->handle
       if both are used. Clear it to avoid a double close leading to crash. */
    connssl_proxy->handle = NULL;

  nss_close(connssl);
  nss_close(connssl_proxy);
}