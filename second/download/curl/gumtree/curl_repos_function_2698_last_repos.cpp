static bool Curl_polarssl_data_pending(const struct connectdata *conn,
                                       int sockindex)
{
  const struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  return ssl_get_bytes_avail(&BACKEND->ssl) != 0;
}