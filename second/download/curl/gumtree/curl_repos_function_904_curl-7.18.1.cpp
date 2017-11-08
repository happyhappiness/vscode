static CURLcode ftp_do(struct connectdata *conn, bool *done)
{
  CURLcode retcode = CURLE_OK;

  *done = FALSE; /* default to false */

  /*
    Since connections can be re-used between SessionHandles, this might be a
    connection already existing but on a fresh SessionHandle struct so we must
    make sure we have a good 'struct FTP' to play with. For new connections,
    the struct FTP is allocated and setup in the ftp_connect() function.
  */
  Curl_reset_reqproto(conn);
  retcode = ftp_init(conn);
  if(retcode)
    return retcode;

  retcode = ftp_parse_url_path(conn);
  if(retcode)
    return retcode;

  retcode = ftp_regular_transfer(conn, done);

  return retcode;
}