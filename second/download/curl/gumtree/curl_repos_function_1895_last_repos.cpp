static CURLcode ftp_state_pwd(struct connectdata *conn)
{
  CURLcode result;

  /* send PWD to discover our entry point */
  PPSENDF(&conn->proto.ftpc.pp, "%s", "PWD");
  state(conn, FTP_PWD);

  return CURLE_OK;
}