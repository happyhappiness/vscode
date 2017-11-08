static CURLcode scp_disconnect(struct connectdata *conn)
{
  CURLcode result;

  Curl_safefree(conn->data->state.proto.ssh);
  conn->data->state.proto.ssh = NULL;

  state(conn, SSH_SESSION_DISCONNECT);

  result = ssh_easy_statemach(conn);

  return result;
}