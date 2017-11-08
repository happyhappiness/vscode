CURLcode
Curl_schannel_connect_nonblocking(struct connectdata *conn, int sockindex,
                                  bool *done)
{
  return schannel_connect_common(conn, sockindex, TRUE, done);
}