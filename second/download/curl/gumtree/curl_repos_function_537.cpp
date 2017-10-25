static CURLcode ftp_state_port_resp(struct connectdata *conn,
                                    int ftpcode)
{
  struct FTP *ftp = conn->proto.ftp;
  struct SessionHandle *data = conn->data;
  ftpport fcmd = (ftpport)ftp->count1;
  CURLcode result = CURLE_OK;

  if(ftpcode != 200) {
    /* the command failed */

    if (EPRT == fcmd) {
      infof(data, "disabling EPRT usage\n");
      conn->bits.ftp_use_eprt = FALSE;
    }
    else if (LPRT == fcmd) {
      infof(data, "disabling LPRT usage\n");
      conn->bits.ftp_use_lprt = FALSE;
    }
    fcmd++;

    if(fcmd == DONE) {
      failf(data, "Failed to do PORT");
      result = CURLE_FTP_PORT_FAILED;
    }
    else
      /* try next */
      result = ftp_state_use_port(conn, fcmd);
  }
  else {
    infof(data, "Connect data stream actively\n");
    state(conn, FTP_STOP); /* end of DO phase */
  }

  return result;
}