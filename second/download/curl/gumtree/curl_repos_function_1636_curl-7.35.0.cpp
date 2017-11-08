static int ftp_domore_getsock(struct connectdata *conn, curl_socket_t *socks,
                              int numsocks)
{
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  if(!numsocks)
    return GETSOCK_BLANK;

  /* When in DO_MORE state, we could be either waiting for us to connect to a
   * remote site, or we could wait for that site to connect to us. Or just
   * handle ordinary commands.
   */

  if(FTP_STOP == ftpc->state) {
    /* if stopped and still in this state, then we're also waiting for a
       connect on the secondary connection */
    socks[0] = conn->sock[FIRSTSOCKET];
    socks[1] = conn->sock[SECONDARYSOCKET];

    return GETSOCK_READSOCK(FIRSTSOCKET) |
      GETSOCK_WRITESOCK(SECONDARYSOCKET);
  }
  else
    return Curl_pp_getsock(&conn->proto.ftpc.pp, socks, numsocks);
}