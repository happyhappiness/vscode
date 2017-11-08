int Curl_pp_getsock(struct pingpong *pp,
                    curl_socket_t *socks,
                    int numsocks)
{
  struct connectdata *conn = pp->conn;

  if(!numsocks)
    return GETSOCK_BLANK;

  socks[0] = conn->sock[FIRSTSOCKET];

  if(pp->sendleft) {
    /* write mode */
    return GETSOCK_WRITESOCK(0);
  }

  /* read mode */
  return GETSOCK_READSOCK(0);
}