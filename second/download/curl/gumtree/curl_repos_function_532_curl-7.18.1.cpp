static CURLcode ssh_multi_statemach(struct connectdata *conn, bool *done)
{
  struct ssh_conn *sshc = &conn->proto.sshc;
  CURLcode result = CURLE_OK;

  result = ssh_statemach_act(conn);
  *done = (bool)(sshc->state == SSH_STOP);

  return result;
}