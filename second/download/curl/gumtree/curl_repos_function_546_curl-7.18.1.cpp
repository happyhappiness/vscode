static CURLcode sftp_done(struct connectdata *conn, CURLcode status,
                               bool premature)
{
  CURLcode result = CURLE_OK;
  bool done = FALSE;
  struct ssh_conn *sshc = &conn->proto.sshc;

  (void)status; /* unused */

  if(status == CURLE_OK) {
    /* Before we shut down, see if there are any post-quote commands to send: */
    if(!status && !premature && conn->data->set.postquote) {
      sshc->nextstate = SSH_SFTP_CLOSE;
      state(conn, SSH_SFTP_POSTQUOTE_INIT);
    }
    else
      state(conn, SSH_SFTP_CLOSE);

    /* run the state-machine */
    if(conn->data->state.used_interface == Curl_if_multi)
      result = ssh_multi_statemach(conn, &done);
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
    Curl_pgrsDone(conn);
  }

  return result;
}