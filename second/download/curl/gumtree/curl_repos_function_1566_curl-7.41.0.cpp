static int pop3_getsock(struct connectdata *conn, curl_socket_t *socks,
                        int numsocks)
{
  return Curl_pp_getsock(&conn->proto.pop3c.pp, socks, numsocks);
}