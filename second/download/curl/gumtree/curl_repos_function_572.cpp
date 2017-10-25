static CURLcode ftp_dophase_done(struct connectdata *conn,
                                 bool connected)
{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->proto.ftp;

  if(connected)
    result = Curl_ftp_nextconnect(conn);

  if(result && (conn->sock[SECONDARYSOCKET] != CURL_SOCKET_BAD)) {
    /* Failure detected, close the second socket if it was created already */
    sclose(conn->sock[SECONDARYSOCKET]);
    conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;
  }

  if(ftp->no_transfer)
    /* no data to transfer */
    result=Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
  else if(!connected)
    /* since we didn't connect now, we want do_more to get called */
    conn->bits.do_more = TRUE;

  ftp->ctl_valid = TRUE; /* seems good */

  return result;
}