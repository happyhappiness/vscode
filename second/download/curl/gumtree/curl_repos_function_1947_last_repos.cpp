static
CURLcode ftp_regular_transfer(struct connectdata *conn,
                              bool *dophase_done)
{
  CURLcode result = CURLE_OK;
  bool connected = FALSE;
  struct Curl_easy *data = conn->data;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  data->req.size = -1; /* make sure this is unknown at this point */

  Curl_pgrsSetUploadCounter(data, 0);
  Curl_pgrsSetDownloadCounter(data, 0);
  Curl_pgrsSetUploadSize(data, -1);
  Curl_pgrsSetDownloadSize(data, -1);

  ftpc->ctl_valid = TRUE; /* starts good */

  result = ftp_perform(conn,
                       &connected, /* have we connected after PASV/PORT */
                       dophase_done); /* all commands in the DO-phase done? */

  if(!result) {

    if(!*dophase_done)
      /* the DO phase has not completed yet */
      return CURLE_OK;

    result = ftp_dophase_done(conn, connected);

    if(result)
      return result;
  }
  else
    freedirs(ftpc);

  return result;
}