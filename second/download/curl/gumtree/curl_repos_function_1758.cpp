static CURLcode ftp_state_rest(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->data->req.protop;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  if((ftp->transfer != FTPTRANSFER_BODY) && ftpc->file) {
    /* if a "head"-like request is being made (on a file) */

    /* Determine if server can respond to REST command and therefore
       whether it supports range */
    PPSENDF(&conn->proto.ftpc.pp, "REST %d", 0);

    state(conn, FTP_REST);
  }
  else
    result = ftp_state_prepare_transfer(conn);

  return result;
}