static bool Curl_cyassl_data_pending(const struct connectdata* conn,
                                     int connindex)
{
  const struct ssl_connect_data *connssl = &conn->ssl[connindex];
  if(BACKEND->handle)   /* SSL is in use */
    return (0 != SSL_pending(BACKEND->handle)) ? TRUE : FALSE;
  else
    return FALSE;
}