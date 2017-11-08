static CURLcode ssh_do(struct connectdata *conn, bool *done)
{
  CURLcode res;
  bool connected = 0;
  struct SessionHandle *data = conn->data;

  *done = FALSE; /* default to false */

  /*
    Since connections can be re-used between SessionHandles, this might be a
    connection already existing but on a fresh SessionHandle struct so we must
    make sure we have a good 'struct SSHPROTO' to play with. For new
    connections, the struct SSHPROTO is allocated and setup in the
    ssh_connect() function.
  */
  Curl_reset_reqproto(conn);
  res = ssh_init(conn);
  if(res)
    return res;

  data->req.size = -1; /* make sure this is unknown at this point */

  Curl_pgrsSetUploadCounter(data, 0);
  Curl_pgrsSetDownloadCounter(data, 0);
  Curl_pgrsSetUploadSize(data, 0);
  Curl_pgrsSetDownloadSize(data, 0);

  if(conn->protocol & PROT_SCP)
    res = scp_perform(conn, &connected,  done);
  else
    res = sftp_perform(conn, &connected,  done);

  return res;
}