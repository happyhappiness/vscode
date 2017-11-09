static CURLcode Curl_multissl_connect(struct connectdata *conn, int sockindex)
{
  if(multissl_init(NULL))
    return CURLE_FAILED_INIT;
  return Curl_ssl->connect(conn, sockindex);
}