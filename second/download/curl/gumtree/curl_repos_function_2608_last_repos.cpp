static void Curl_multissl_close(struct connectdata *conn, int sockindex)
{
  if(multissl_init(NULL))
    return;
  Curl_ssl->close(conn, sockindex);
}