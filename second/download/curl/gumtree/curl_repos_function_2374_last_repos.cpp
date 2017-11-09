static void Curl_ossl_close(struct connectdata *conn, int sockindex)
{
  ossl_close(&conn->ssl[sockindex]);
  ossl_close(&conn->proxy_ssl[sockindex]);
}