static CURLcode ssh_setup_connection(struct connectdata *conn)
{
  struct SSHPROTO *ssh;

  conn->data->req.protop = ssh = calloc(1, sizeof(struct SSHPROTO));
  if(!ssh)
    return CURLE_OUT_OF_MEMORY;

  return CURLE_OK;
}