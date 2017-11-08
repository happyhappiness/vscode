static CURLcode ftp_state_post_rest(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->proto.ftp;
  struct SessionHandle *data = conn->data;

  if(ftp->no_transfer || conn->bits.no_body) {
    /* then we're done with a "head"-like request, goto STOP */
    state(conn, FTP_STOP);

    /* doesn't transfer any data */
    ftp->no_transfer = TRUE;
  }
  else if(data->set.ftp_use_port) {
    /* We have chosen to use the PORT (or similar) command */
    result = ftp_state_use_port(conn, EPRT);
  }
  else {
    /* We have chosen (this is default) to use the PASV (or similar) command */
    result = ftp_state_use_pasv(conn);
  }
  return result;
}