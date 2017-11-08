static CURLcode ssh_init(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  struct SSHPROTO *ssh;
  struct ssh_conn *sshc = &conn->proto.sshc;

  sshc->actualcode = CURLE_OK; /* reset error code */
  sshc->secondCreateDirs =0;   /* reset the create dir attempt state variable */

  if(data->state.proto.ssh)
    return CURLE_OK;

  ssh = (struct SSHPROTO *)calloc(sizeof(struct SSHPROTO), 1);
  if(!ssh)
    return CURLE_OUT_OF_MEMORY;

  data->state.proto.ssh = ssh;

  return CURLE_OK;
}