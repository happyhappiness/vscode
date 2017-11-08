static CURLcode ftp_nextconnect(struct connectdata *conn)
{
  struct SessionHandle *data=conn->data;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  CURLcode result = CURLE_OK;

  /* the ftp struct is inited in ftp_connect() */
  struct FTP *ftp = data->state.proto.ftp;

  DEBUGF(infof(data, "DO-MORE phase starts\n"));

  if(ftp->transfer <= FTPTRANSFER_INFO) {
    /* a transfer is about to take place, or if not a file name was given
       so we'll do a SIZE on it later and then we need the right TYPE first */

    if(data->set.upload) {
      result = ftp_nb_type(conn, data->set.prefer_ascii, FTP_STOR_TYPE);
      if(result)
        return result;
    }
    else {
      /* download */
      ftp->downloadsize = -1; /* unknown as of yet */

      result = ftp_range(conn);
      if(result)
        ;
      else if(data->set.ftp_list_only || !ftpc->file) {
        /* The specified path ends with a slash, and therefore we think this
           is a directory that is requested, use LIST. But before that we
           need to set ASCII transfer mode. */

        /* But only if a body transfer was requested. */
        if(ftp->transfer == FTPTRANSFER_BODY) {
          result = ftp_nb_type(conn, 1, FTP_LIST_TYPE);
          if(result)
            return result;
        }
        /* otherwise just fall through */
      }
      else {
        result = ftp_nb_type(conn, data->set.prefer_ascii, FTP_RETR_TYPE);
        if(result)
          return result;
      }
    }
    result = ftp_easy_statemach(conn);
  }

  if((result == CURLE_OK) && (ftp->transfer != FTPTRANSFER_BODY))
    /* no data to transfer. FIX: it feels like a kludge to have this here
       too! */
    result = Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);

  /* end of transfer */
  DEBUGF(infof(data, "DO-MORE phase ends with %d\n", result));

  return result;
}