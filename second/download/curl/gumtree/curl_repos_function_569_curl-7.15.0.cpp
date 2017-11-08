static CURLcode ftp_state_ul_setup(struct connectdata *conn,
                                   bool sizechecked)
{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->proto.ftp;
  struct SessionHandle *data = conn->data;
  curl_off_t passed=0;

  if((conn->resume_from && !sizechecked) ||
     ((conn->resume_from > 0) && sizechecked)) {
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

    if(conn->resume_from < 0 ) {
      /* Got no given size to start from, figure it out */
      NBFTPSENDF(conn, "SIZE %s", ftp->file);
      state(conn, FTP_STOR_SIZE);
      return result;
    }

    /* enable append */
    data->set.ftp_append = TRUE;

    /* Let's read off the proper amount of bytes from the input. If we knew it
       was a proper file we could've just fseek()ed but we only have a stream
       here */

    /* TODO: allow the ioctlfunction to provide a fast forward function that
       can be used here and use this method only as a fallback! */
    do {
      curl_off_t readthisamountnow = (conn->resume_from - passed);
      curl_off_t actuallyread;

      if(readthisamountnow > BUFSIZE)
        readthisamountnow = BUFSIZE;

      actuallyread = (curl_off_t)
        conn->fread(data->state.buffer, 1, (size_t)readthisamountnow,
                    conn->fread_in);

      passed += actuallyread;
      if(actuallyread != readthisamountnow) {
        failf(data, "Could only read %" FORMAT_OFF_T
              " bytes from the input", passed);
        return CURLE_FTP_COULDNT_USE_REST;
      }
    } while(passed != conn->resume_from);

    /* now, decrease the size of the read */
    if(data->set.infilesize>0) {
      data->set.infilesize -= conn->resume_from;

      if(data->set.infilesize <= 0) {
        infof(data, "File already completely uploaded\n");

        /* no data to transfer */
        result=Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);

        /* Set no_transfer so that we won't get any error in
         * Curl_ftp_done() because we didn't transfer anything! */
        ftp->no_transfer = TRUE;

        state(conn, FTP_STOP);
        return CURLE_OK;
      }
    }
    /* we've passed, proceed as normal */
  } /* resume_from */

  NBFTPSENDF(conn, data->set.ftp_append?"APPE %s":"STOR %s",
             ftp->file);

  state(conn, FTP_STOR);

  return result;
}