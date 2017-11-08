static CURLcode ftp_state_post_cwd(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  /* Requested time of file or time-depended transfer? */
  if((data->set.get_filetime || data->set.timecondition) && ftpc->file) {

    /* we have requested to get the modified-time of the file, this is a white
       spot as the MDTM is not mentioned in RFC959 */
    NBFTPSENDF(conn, "MDTM %s", ftpc->file);

    state(conn, FTP_MDTM);
  }
  else
    result = ftp_state_post_mdtm(conn);

  return result;
}