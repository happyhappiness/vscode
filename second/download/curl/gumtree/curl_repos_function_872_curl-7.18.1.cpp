static CURLcode ftp_state_post_retrtype(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  /* We've sent the TYPE, now we must send the list of prequote strings */

  result = ftp_state_quote(conn, TRUE, FTP_RETR_PREQUOTE);

  return result;
}