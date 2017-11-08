static CURLcode ssh_multi_statemach(struct connectdata *conn, bool *done)
{
  struct ssh_conn *sshc = &conn->proto.sshc;
  CURLcode result = CURLE_OK;
  bool block; /* we store the status and use that to provide a ssh_getsock()
                 implementation */

  result = ssh_statemach_act(conn, &block);
  *done = (sshc->state == SSH_STOP) ? TRUE : FALSE;
  ssh_block2waitfor(conn, block);

  return result;
}