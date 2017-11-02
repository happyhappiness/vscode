static CURLcode sftp_done(struct connectdata *conn, CURLcode status,
                               bool premature)
{
  struct ssh_conn *sshc = &conn->proto.sshc;

  if(!status) {
    /* Post quote commands are executed after the SFTP_CLOSE state to avoid
       errors that could happen due to open file handles during POSTQUOTE
       operation */
    if(!status && !premature && conn->data->set.postquote) {
      sshc->nextstate = SSH_SFTP_POSTQUOTE_INIT;
      state(conn, SSH_SFTP_CLOSE);
    }
    else
      state(conn, SSH_SFTP_CLOSE);
  }
  return ssh_done(conn, status);
}