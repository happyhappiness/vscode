int Curl_mbedtls_data_pending(const struct connectdata *conn, int sockindex)
{
  return mbedtls_ssl_get_bytes_avail(&conn->ssl[sockindex].ssl) != 0;
}