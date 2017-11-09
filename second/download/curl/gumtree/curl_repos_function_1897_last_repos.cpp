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
    int bits = GETSOCK_READSOCK(0);

    /* if stopped and still in this state, then we're also waiting for a
       connect on the secondary connection */
    socks[0] = conn->sock[FIRSTSOCKET];

    if(!conn->data->set.ftp_use_port) {
      int s;
      int i;
      /* PORT is used to tell the server to connect to us, and during that we
         don't do happy eyeballs, but we do if we connect to the server */
      for(s = 1, i = 0; i<2; i++) {
        if(conn->tempsock[i] != CURL_SOCKET_BAD) {
          socks[s] = conn->tempsock[i];
          bits |= GETSOCK_WRITESOCK(s++);
        }
      }
    }
    else {
      socks[1] = conn->sock[SECONDARYSOCKET];
      bits |= GETSOCK_WRITESOCK(1) | GETSOCK_READSOCK(1);
    }

    return bits;
  }
  return Curl_pp_getsock(&conn->proto.ftpc.pp, socks, numsocks);
}