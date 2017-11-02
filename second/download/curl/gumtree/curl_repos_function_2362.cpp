void Curl_gtls_close(struct connectdata *conn, int sockindex)
{
  close_one(conn, sockindex);
}