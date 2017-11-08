static CURLcode ftp_state_user(struct connectdata *conn)
{
  CURLcode result;
  struct FTP *ftp = conn->data->req.protop;
  /* send USER */
  PPSENDF(&conn->proto.ftpc.pp, "USER %s", ftp->user?ftp->user:"");

  state(conn, FTP_USER);
  conn->data->state.ftp_trying_alternative = FALSE;

  return CURLE_OK;
}