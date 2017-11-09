static bool Curl_gtls_data_pending(const struct connectdata *conn,
                                   int connindex)
{
  const struct ssl_connect_data *connssl = &conn->ssl[connindex];
  bool res = FALSE;
  if(BACKEND->session &&
     0 != gnutls_record_check_pending(BACKEND->session))
    res = TRUE;

  connssl = &conn->proxy_ssl[connindex];
  if(BACKEND->session &&
     0 != gnutls_record_check_pending(BACKEND->session))
    res = TRUE;

  return res;
}