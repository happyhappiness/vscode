static int tftp_getsock(struct connectdata *conn, curl_socket_t *socks,
                        int numsocks)
{
  if(!numsocks)
    return GETSOCK_BLANK;

  socks[0] = conn->sock[FIRSTSOCKET];

  return GETSOCK_READSOCK(0);
}