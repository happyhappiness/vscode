static CURLcode ftp_state_post_type(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->proto.ftp;

  if(ftp->no_transfer) {
    /* if a "head"-like request is being made */

    /* we know ftp->file is a valid pointer to a file name */
    NBFTPSENDF(conn, "SIZE %s", ftp->file);

    state(conn, FTP_SIZE);
  }
  else
    result = ftp_state_post_size(conn);

  return result;
}