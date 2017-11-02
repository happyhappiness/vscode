static int waitconnect_getsock(struct connectdata *conn,
                               curl_socket_t *sock,
                               int numsocks)
{
  int i;
  int s=0;
  int rc=0;

  if(!numsocks)
    return GETSOCK_BLANK;

  for(i=0; i<2; i++) {
    if(conn->tempsock[i] != CURL_SOCKET_BAD) {
      sock[s] = conn->tempsock[i];
      rc |= GETSOCK_WRITESOCK(s++);
    }
  }

  /* when we've sent a CONNECT to a proxy, we should rather wait for the
     socket to become readable to be able to get the response headers */
  if(conn->tunnel_state[FIRSTSOCKET] == TUNNEL_CONNECT) {
    sock[0] = conn->sock[FIRSTSOCKET];
    rc = GETSOCK_READSOCK(0);
  }

  return rc;
}