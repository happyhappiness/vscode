static CURLcode Curl_ossl_connect_nonblocking(struct connectdata *conn,
                                              int sockindex,
                                              bool *done)
{
  return ossl_connect_common(conn, sockindex, TRUE, done);
}