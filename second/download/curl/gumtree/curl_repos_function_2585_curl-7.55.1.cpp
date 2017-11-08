bool Curl_gtls_data_pending(const struct connectdata *conn, int connindex)
{
  bool res = FALSE;
  if(conn->ssl[connindex].session &&
     0 != gnutls_record_check_pending(conn->ssl[connindex].session))
    res = TRUE;

  if(conn->proxy_ssl[connindex].session &&
     0 != gnutls_record_check_pending(conn->proxy_ssl[connindex].session))
    res = TRUE;

  return res;
}