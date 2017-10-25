static CURLcode ftp_state_post_size(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->proto.ftp;

  if(ftp->no_transfer) {
    /* if a "head"-like request is being made */

    /* Determine if server can respond to REST command and therefore
       whether it supports range */
    NBFTPSENDF(conn, "REST %d", 0);

    state(conn, FTP_REST);
  }
  else
    result = ftp_state_post_rest(conn);

  return result;
}