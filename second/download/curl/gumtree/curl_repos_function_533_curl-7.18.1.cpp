static CURLcode ssh_easy_statemach(struct connectdata *conn)
{
  struct ssh_conn *sshc = &conn->proto.sshc;
  CURLcode result = CURLE_OK;

  while((sshc->state != SSH_STOP) && !result)
    result = ssh_statemach_act(conn);

  return result;
}