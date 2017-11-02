CURLcode
Curl_gtls_connect_nonblocking(struct connectdata *conn,
                              int sockindex,
                              bool *done)
{
  return gtls_connect_common(conn, sockindex, TRUE, done);
}