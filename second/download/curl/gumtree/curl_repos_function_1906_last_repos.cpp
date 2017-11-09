static CURLcode ftp_state_stor_prequote(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  /* We've sent the TYPE, now we must send the list of prequote strings */

  result = ftp_state_quote(conn, TRUE, FTP_STOR_PREQUOTE);

  return result;
}