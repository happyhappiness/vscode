static CURLcode ftp_dophase_done(struct connectdata *conn,
                                 bool connected)
{
  struct FTP *ftp = conn->data->req.protop;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  if(connected) {
    int completed;
    CURLcode result = ftp_do_more(conn, &completed);

    if(result) {
      if(conn->sock[SECONDARYSOCKET] != CURL_SOCKET_BAD) {
        /* close the second socket if it was created already */
        Curl_closesocket(conn, conn->sock[SECONDARYSOCKET]);
        conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;
      }
      return result;
    }
  }

  if(ftp->transfer != FTPTRANSFER_BODY)
    /* no data to transfer */
    Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
  else if(!connected)
    /* since we didn't connect now, we want do_more to get called */
    conn->bits.do_more = TRUE;

  ftpc->ctl_valid = TRUE; /* seems good */

  return CURLE_OK;
}