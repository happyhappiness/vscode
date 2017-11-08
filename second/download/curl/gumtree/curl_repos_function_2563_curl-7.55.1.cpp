int Curl_polarssl_data_pending(const struct connectdata *conn, int sockindex)
{
  return ssl_get_bytes_avail(&conn->ssl[sockindex].ssl) != 0;
}