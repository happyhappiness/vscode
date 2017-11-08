static CURLcode ftp_quit(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  if(conn->proto.ftp->ctl_valid) {
    NBFTPSENDF(conn, "QUIT", NULL);
    state(conn, FTP_QUIT);

    result = ftp_easy_statemach(conn);
  }

  return result;
}