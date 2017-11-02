static CURLcode ftp_state_stor_resp(struct connectdata *conn,
                                    int ftpcode, ftpstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  if(ftpcode>=400) {
    failf(data, "Failed FTP upload: %0d", ftpcode);
    state(conn, FTP_STOP);
    /* oops, we never close the sockets! */
    return CURLE_UPLOAD_FAILED;
  }

  conn->proto.ftpc.state_saved = instate;

  /* PORT means we are now awaiting the server to connect to us. */
  if(data->set.ftp_use_port) {
    bool connected;

    state(conn, FTP_STOP); /* no longer in STOR state */

    result = AllowServerConnect(conn, &connected);
    if(result)
      return result;

    if(!connected) {
      struct ftp_conn *ftpc = &conn->proto.ftpc;
      infof(data, "Data conn was not available immediately\n");
      ftpc->wait_data_conn = TRUE;
    }

    return CURLE_OK;
  }
  else
    return InitiateTransfer(conn);
}