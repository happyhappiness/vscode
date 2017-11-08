static int ftp_getsock(struct connectdata *conn,
                       curl_socket_t *socks,
                       int numsocks)
{
  return Curl_pp_getsock(&conn->proto.ftpc.pp, socks, numsocks);
}