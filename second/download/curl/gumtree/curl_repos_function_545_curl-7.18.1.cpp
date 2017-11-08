static CURLcode sftp_disconnect(struct connectdata *conn)
{
  CURLcode result;

  DEBUGF(infof(conn->data, "SSH DISCONNECT starts now\n"));

  Curl_safefree(conn->data->state.proto.ssh);
  conn->data->state.proto.ssh = NULL;

  state(conn, SSH_SFTP_SHUTDOWN);
  result = ssh_easy_statemach(conn);

  DEBUGF(infof(conn->data, "SSH DISCONNECT is done\n"));

  return result;

}