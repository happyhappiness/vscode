static CURLcode Curl_darwinssl_connect_nonblocking(struct connectdata *conn,
                                                   int sockindex, bool *done)
{
  return darwinssl_connect_common(conn, sockindex, TRUE, done);
}