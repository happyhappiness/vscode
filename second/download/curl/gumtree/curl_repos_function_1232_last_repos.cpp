static CURLcode sftp_disconnect(struct connectdata *conn, bool dead_connection)
{
  CURLcode result = CURLE_OK;
  (void) dead_connection;

  DEBUGF(infof(conn->data, "SSH DISCONNECT starts now\n"));

  if(conn->proto.sshc.ssh_session) {
    /* only if there's a session still around to use! */
    state(conn, SSH_SFTP_SHUTDOWN);
    result = ssh_block_statemach(conn, TRUE);
  }

  DEBUGF(infof(conn->data, "SSH DISCONNECT is done\n"));

  return result;

}