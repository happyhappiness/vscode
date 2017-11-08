CURLcode
Curl_cyassl_connect_nonblocking(struct connectdata *conn,
                                int sockindex,
                                bool *done)
{
  return cyassl_connect_common(conn, sockindex, TRUE, done);
}