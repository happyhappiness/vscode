static CURLcode ftp_state_post_mdtm(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->proto.ftp;
  struct SessionHandle *data = conn->data;

  /* If we have selected NOBODY and HEADER, it means that we only want file
     information. Which in FTP can't be much more than the file size and
     date. */
  if(conn->bits.no_body && data->set.include_header && ftp->file) {
    /* The SIZE command is _not_ RFC 959 specified, and therefor many servers
       may not support it! It is however the only way we have to get a file's
       size! */

    ftp->no_transfer = TRUE; /* this means no actual transfer will be made */

    /* Some servers return different sizes for different modes, and thus we
       must set the proper type before we check the size */
    NBFTPSENDF(conn, "TYPE %c",
               data->set.ftp_ascii?'A':'I');
    state(conn, FTP_TYPE);
  }
  else
    result = ftp_state_post_type(conn);

  return result;
}