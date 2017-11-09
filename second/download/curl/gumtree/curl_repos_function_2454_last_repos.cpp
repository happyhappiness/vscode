static void Curl_gskit_close(struct connectdata *conn, int sockindex)
{
  close_one(&conn->ssl[sockindex], conn, sockindex);
  close_one(&conn->proxy_ssl[sockindex], conn, sockindex);
}