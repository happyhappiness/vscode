bool Curl_ossl_data_pending(const struct connectdata *conn, int connindex)
{
  if(conn->ssl[connindex].handle)
    /* SSL is in use */
    return (0 != SSL_pending(conn->ssl[connindex].handle) ||
           (conn->proxy_ssl[connindex].handle &&
            0 != SSL_pending(conn->proxy_ssl[connindex].handle))) ?
           TRUE : FALSE;
  return FALSE;
}