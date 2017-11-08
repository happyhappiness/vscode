static CURLcode scp_done(struct connectdata *conn, CURLcode status,
                         bool premature)
{
  CURLcode result = CURLE_OK;
  bool done = FALSE;
  (void)premature; /* not used */
  (void)status; /* unused */

  if(status == CURLE_OK) {
    state(conn, SSH_SCP_DONE);
    /* run the state-machine */
    if(conn->data->state.used_interface == Curl_if_multi) {
      result = ssh_multi_statemach(conn, &done);
    }
    else {
      result = ssh_easy_statemach(conn);
      done = TRUE;
    }
  }
  else {
    result = status;
    done = TRUE;
  }

  if(done) {
    struct SSHPROTO *sftp_scp = conn->data->state.proto.ssh;
    Curl_safefree(sftp_scp->path);
    sftp_scp->path = NULL;
    Curl_pgrsDone(conn);
  }

  return result;

}