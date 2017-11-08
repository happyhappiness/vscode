static CURLcode ftp_do(struct connectdata *conn, bool *done)
{
  CURLcode retcode = CURLE_OK;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  *done = FALSE; /* default to false */
  ftpc->wait_data_conn = FALSE; /* default to no such wait */

  if(conn->data->set.wildcardmatch) {
    retcode = wc_statemach(conn);
    if(conn->data->wildcard.state == CURLWC_SKIP ||
      conn->data->wildcard.state == CURLWC_DONE) {
      /* do not call ftp_regular_transfer */
      return CURLE_OK;
    }
    if(retcode) /* error, loop or skipping the file */
      return retcode;
  }
  else { /* no wildcard FSM needed */
    retcode = ftp_parse_url_path(conn);
    if(retcode)
      return retcode;
  }

  retcode = ftp_regular_transfer(conn, done);

  return retcode;
}