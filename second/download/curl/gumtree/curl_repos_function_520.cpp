static CURLcode ftp_state_user(struct connectdata *conn)
{
  CURLcode result;
  struct FTP *ftp = conn->proto.ftp;
  /* send USER */
  NBFTPSENDF(conn, "USER %s", ftp->user?ftp->user:"");

  state(conn, FTP_USER);

  return CURLE_OK;
}