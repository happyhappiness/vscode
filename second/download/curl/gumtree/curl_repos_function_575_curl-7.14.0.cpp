static CURLcode ftp_3rdparty(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  conn->proto.ftp->ctl_valid = conn->sec_conn->proto.ftp->ctl_valid = TRUE;
  conn->size = conn->sec_conn->size = -1;

  result = ftp_3rdparty_pretransfer(conn);
  if (!result)
    result = ftp_3rdparty_transfer(conn);

  return result;
}