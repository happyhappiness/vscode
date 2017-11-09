static CURLcode ssh_done(struct connectdata *conn, CURLcode status)
{
  CURLcode result = CURLE_OK;
  struct SSHPROTO *sftp_scp = conn->data->req.protop;

  if(!status) {
    /* run the state-machine

       TODO: when the multi interface is used, this _really_ should be using
       the ssh_multi_statemach function but we have no general support for
       non-blocking DONE operations!
    */
    result = ssh_block_statemach(conn, FALSE);
  }
  else
    result = status;

  if(sftp_scp)
    Curl_safefree(sftp_scp->path);
  if(Curl_pgrsDone(conn))
    return CURLE_ABORTED_BY_CALLBACK;

  conn->data->req.keepon = 0; /* clear all bits */
  return result;
}