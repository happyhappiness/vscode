CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
{
  struct SessionHandle *data=conn->data;
  CURLcode result = CURLE_OK;

  /* the ftp struct is inited in Curl_ftp_connect() */
  struct FTP *ftp = conn->proto.ftp;

  DEBUGF(infof(data, "DO-MORE phase starts\n"));

  if(!ftp->no_transfer && !conn->bits.no_body) {
    /* a transfer is about to take place */

    if(data->set.upload) {
      NBFTPSENDF(conn, "TYPE %c", data->set.ftp_ascii?'A':'I');
      state(conn, FTP_STOR_TYPE);
    }
    else {
      /* download */
      ftp->downloadsize = -1; /* unknown as of yet */

      result = ftp_range(conn);
      if(result)
        ;
      else if((data->set.ftp_list_only) || !ftp->file) {
        /* The specified path ends with a slash, and therefore we think this
           is a directory that is requested, use LIST. But before that we
           need to set ASCII transfer mode. */
        NBFTPSENDF(conn, "TYPE A", NULL);
        state(conn, FTP_LIST_TYPE);
      }
      else {
        NBFTPSENDF(conn, "TYPE %c", data->set.ftp_ascii?'A':'I');
        state(conn, FTP_RETR_TYPE);
      }
    }
    result = ftp_easy_statemach(conn);
  }

  if(ftp->no_transfer)
    /* no data to transfer. FIX: it feels like a kludge to have this here
       too! */
    result=Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);

  /* end of transfer */
  DEBUGF(infof(data, "DO-MORE phase ends\n"));

  return result;
}