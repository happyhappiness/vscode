static CURLcode ftp_3rdparty_pretransfer(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct connectdata *sec_conn = conn->sec_conn;

  conn->xfertype = TARGET3RD;
  sec_conn->xfertype = SOURCE3RD;

  /* sets transfer type */
  result = ftp_transfertype(conn, data->set.ftp_ascii);
  if (result)
    return result;

  result = ftp_transfertype(sec_conn, data->set.ftp_ascii);
  if (result)
    return result;

  /* Send any PREQUOTE strings after transfer type is set? */
  if (data->set.source_prequote) {
    /* sends command(s) to source server before file transfer */
    result = ftp_sendquote(sec_conn, data->set.source_prequote);
  }
  if (!result && data->set.prequote)
    result = ftp_sendquote(conn, data->set.prequote);

  return result;
}