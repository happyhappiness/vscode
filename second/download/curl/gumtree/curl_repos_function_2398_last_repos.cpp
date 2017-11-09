static bool Curl_ossl_data_pending(const struct connectdata *conn,
                                   int connindex)
{
  const struct ssl_connect_data *connssl = &conn->ssl[connindex];
  const struct ssl_connect_data *proxyssl = &conn->proxy_ssl[connindex];
  if(BACKEND->handle)
    /* SSL is in use */
    return (0 != SSL_pending(BACKEND->handle) ||
           (proxyssl->backend->handle &&
            0 != SSL_pending(proxyssl->backend->handle))) ?
           TRUE : FALSE;
  return FALSE;
}