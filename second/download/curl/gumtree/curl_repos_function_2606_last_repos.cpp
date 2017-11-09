static CURLcode Curl_multissl_connect_nonblocking(struct connectdata *conn,
                                                  int sockindex, bool *done)
{
  if(multissl_init(NULL))
    return CURLE_FAILED_INIT;
  return Curl_ssl->connect_nonblocking(conn, sockindex, done);
}