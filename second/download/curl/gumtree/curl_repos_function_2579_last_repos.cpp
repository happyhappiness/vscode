bool Curl_ssl_data_pending(const struct connectdata *conn,
                           int connindex)
{
  return Curl_ssl->data_pending(conn, connindex);
}