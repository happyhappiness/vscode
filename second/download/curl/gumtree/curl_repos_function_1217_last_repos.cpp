static void ssh_block2waitfor(struct connectdata *conn, bool block)
{
  struct ssh_conn *sshc = &conn->proto.sshc;
  int dir = 0;
  if(block) {
    dir = libssh2_session_block_directions(sshc->ssh_session);
    if(dir) {
      /* translate the libssh2 define bits into our own bit defines */
      conn->waitfor = ((dir&LIBSSH2_SESSION_BLOCK_INBOUND)?KEEP_RECV:0) |
        ((dir&LIBSSH2_SESSION_BLOCK_OUTBOUND)?KEEP_SEND:0);
    }
  }
  if(!dir)
    /* It didn't block or libssh2 didn't reveal in which direction, put back
       the original set */
    conn->waitfor = sshc->orig_waitfor;
}