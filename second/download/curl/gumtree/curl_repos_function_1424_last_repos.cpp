static int https_getsock(struct connectdata *conn,
                         curl_socket_t *socks,
                         int numsocks)
{
  if(conn->handler->flags & PROTOPT_SSL)
    return Curl_ssl_getsock(conn, socks, numsocks);
  return GETSOCK_BLANK;
}