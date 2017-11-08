static int waitconnect_getsock(struct connectdata *conn,
                               curl_socket_t *sock,
                               int numsocks)
{
  if(!numsocks)
    return GETSOCK_BLANK;

  sock[0] = conn->sock[FIRSTSOCKET];
  return GETSOCK_WRITESOCK(0);
}