CURLcode Curl_ftp(struct connectdata *conn, bool *done)
{
  CURLcode retcode = CURLE_OK;

  *done = FALSE; /* default to false */

  retcode = ftp_parse_url_path(conn);
  if (retcode)
    return retcode;

  if (conn->sec_conn) {
    /* 3rd party transfer */
    *done = TRUE; /* BLOCKING */
    retcode = ftp_3rdparty(conn);
  }
  else
    retcode = ftp_regular_transfer(conn, done);

  return retcode;
}