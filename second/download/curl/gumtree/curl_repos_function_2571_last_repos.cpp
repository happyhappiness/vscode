void Curl_ssl_close(struct connectdata *conn, int sockindex)
{
  DEBUGASSERT((sockindex <= 1) && (sockindex >= -1));
  Curl_ssl->close(conn, sockindex);
}