static CURLcode ftp_state_pwd(struct connectdata *conn)
{
  CURLcode result;

  /* send PWD to discover our entry point */
  NBFTPSENDF(conn, "PWD", NULL);
  state(conn, FTP_PWD);

  return CURLE_OK;
}