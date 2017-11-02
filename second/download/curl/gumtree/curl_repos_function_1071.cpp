static CURLcode ssh_do(struct connectdata *conn, bool *done)
{
  CURLcode result;
  bool connected = 0;
  struct SessionHandle *data = conn->data;
  struct ssh_conn *sshc = &conn->proto.sshc;

  *done = FALSE; /* default to false */

  data->req.size = -1; /* make sure this is unknown at this point */

  sshc->actualcode = CURLE_OK; /* reset error code */
  sshc->secondCreateDirs =0;   /* reset the create dir attempt state
                                  variable */

  Curl_pgrsSetUploadCounter(data, 0);
  Curl_pgrsSetDownloadCounter(data, 0);
  Curl_pgrsSetUploadSize(data, -1);
  Curl_pgrsSetDownloadSize(data, -1);

  if(conn->handler->protocol & CURLPROTO_SCP)
    result = scp_perform(conn, &connected,  done);
  else
    result = sftp_perform(conn, &connected,  done);

  return result;
}