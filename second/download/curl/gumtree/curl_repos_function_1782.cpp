static CURLcode ftp_multi_statemach(struct connectdata *conn,
                                    bool *done)
{
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  CURLcode result = Curl_pp_statemach(&ftpc->pp, FALSE);

  /* Check for the state outside of the Curl_socket_ready() return code checks
     since at times we are in fact already in this state when this function
     gets called. */
  *done = (ftpc->state == FTP_STOP) ? TRUE : FALSE;

  return result;
}