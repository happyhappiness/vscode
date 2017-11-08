static CURLcode ftp_state_ul_setup(struct connectdata *conn,
                                   bool sizechecked)
{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->data->state.proto.ftp;
  struct SessionHandle *data = conn->data;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  if((data->state.resume_from && !sizechecked) ||
     ((data->state.resume_from > 0) && sizechecked)) {
    /* we're about to continue the uploading of a file */
    /* 1. get already existing file's size. We use the SIZE command for this
       which may not exist in the server!  The SIZE command is not in
       RFC959. */

    /* 2. This used to set REST. But since we can do append, we
       don't another ftp command. We just skip the source file
       offset and then we APPEND the rest on the file instead */

    /* 3. pass file-size number of bytes in the source file */
    /* 4. lower the infilesize counter */
    /* => transfer as usual */

    if(data->state.resume_from < 0 ) {
      /* Got no given size to start from, figure it out */
      NBFTPSENDF(conn, "SIZE %s", ftpc->file);
      state(conn, FTP_STOR_SIZE);
      return result;
    }

    /* enable append */
    data->set.ftp_append = TRUE;

    /* Let's read off the proper amount of bytes from the input. */
    if(conn->seek_func) {
      curl_off_t readthisamountnow = data->state.resume_from;

      if(conn->seek_func(conn->seek_client,
			 readthisamountnow, SEEK_SET) != 0) {
        failf(data, "Could not seek stream");
        return CURLE_FTP_COULDNT_USE_REST;
      }
    }

    else {
      curl_off_t passed=0;
      do {
        curl_off_t readthisamountnow = (data->state.resume_from - passed);
        curl_off_t actuallyread;

        if(readthisamountnow > BUFSIZE)
          readthisamountnow = BUFSIZE;

        actuallyread = (curl_off_t)
          conn->fread_func(data->state.buffer, 1, (size_t)readthisamountnow,
                      conn->fread_in);

        passed += actuallyread;
        if((actuallyread <= 0) || (actuallyread > readthisamountnow)) {
          /* this checks for greater-than only to make sure that the
             CURL_READFUNC_ABORT return code still aborts */
          failf(data, "Failed to read data");
          return CURLE_FTP_COULDNT_USE_REST;
        }
      } while(passed < data->state.resume_from);
    }

    /* now, decrease the size of the read */
    if(data->set.infilesize>0) {
      data->set.infilesize -= data->state.resume_from;

      if(data->set.infilesize <= 0) {
        infof(data, "File already completely uploaded\n");

        /* no data to transfer */
        result=Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);

        /* Set ->transfer so that we won't get any error in
         * ftp_done() because we didn't transfer anything! */
        ftp->transfer = FTPTRANSFER_NONE;

        state(conn, FTP_STOP);
        return CURLE_OK;
      }
    }
    /* we've passed, proceed as normal */
  } /* resume_from */

  NBFTPSENDF(conn, data->set.ftp_append?"APPE %s":"STOR %s",
             ftpc->file);

  state(conn, FTP_STOR);

  return result;
}