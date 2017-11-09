static void Curl_gtls_close(struct connectdata *conn, int sockindex)
{
  close_one(&conn->ssl[sockindex]);
  close_one(&conn->proxy_ssl[sockindex]);
}