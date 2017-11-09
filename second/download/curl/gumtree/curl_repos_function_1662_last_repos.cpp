bool Curl_recv_has_postponed_data(struct connectdata *conn, int sockindex)
{
  (void)conn;
  (void)sockindex;
  return false;
}