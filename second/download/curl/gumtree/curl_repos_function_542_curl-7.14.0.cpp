static CURLcode ftp_state_rest_resp(struct connectdata *conn,
                                    int ftpcode,
                                    ftpstate instate)
{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->proto.ftp;

  switch(instate) {
  case FTP_REST:
  default:
    if (ftpcode == 350) {
      result = Curl_client_write(conn->data, CLIENTWRITE_BOTH,
                               (char *)"Accept-ranges: bytes\r\n", 0);
      if(result)
        return result;
    }

    result = ftp_state_post_rest(conn);
    break;

  case FTP_RETR_REST:
    if (ftpcode != 350) {
      failf(conn->data, "Couldn't use REST");
      result = CURLE_FTP_COULDNT_USE_REST;
    }
    else {
      NBFTPSENDF(conn, "RETR %s", ftp->file);
      state(conn, FTP_RETR);
    }
    break;
  }

  return result;
}