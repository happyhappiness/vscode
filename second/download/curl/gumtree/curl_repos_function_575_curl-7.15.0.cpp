static CURLcode ftp_state_post_retr_size(struct connectdata *conn,
                                         curl_off_t filesize)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data=conn->data;
  struct FTP *ftp = conn->proto.ftp;

  if (data->set.max_filesize && (filesize > data->set.max_filesize)) {
    failf(data, "Maximum file size exceeded");
    return CURLE_FILESIZE_EXCEEDED;
  }
  ftp->downloadsize = filesize;

  if(conn->resume_from) {
    /* We always (attempt to) get the size of downloads, so it is done before
       this even when not doing resumes. */
    if(filesize == -1) {
      infof(data, "ftp server doesn't support SIZE\n");
      /* We couldn't get the size and therefore we can't know if there really
         is a part of the file left to get, although the server will just
         close the connection when we start the connection so it won't cause
         us any harm, just not make us exit as nicely. */
    }
    else {
      /* We got a file size report, so we check that there actually is a
         part of the file left to get, or else we go home.  */
      if(conn->resume_from< 0) {
        /* We're supposed to download the last abs(from) bytes */
        if(filesize < -conn->resume_from) {
          failf(data, "Offset (%" FORMAT_OFF_T
                ") was beyond file size (%" FORMAT_OFF_T ")",
                conn->resume_from, filesize);
          return CURLE_BAD_DOWNLOAD_RESUME;
        }
        /* convert to size to download */
        ftp->downloadsize = -conn->resume_from;
        /* download from where? */
        conn->resume_from = filesize - ftp->downloadsize;
      }
      else {
        if(filesize < conn->resume_from) {
          failf(data, "Offset (%" FORMAT_OFF_T
                ") was beyond file size (%" FORMAT_OFF_T ")",
                conn->resume_from, filesize);
          return CURLE_BAD_DOWNLOAD_RESUME;
        }
        /* Now store the number of bytes we are expected to download */
        ftp->downloadsize = filesize-conn->resume_from;
      }
    }

    if(ftp->downloadsize == 0) {
      /* no data to transfer */
      result=Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
      infof(data, "File already completely downloaded\n");

      /* Set no_transfer so that we won't get any error in Curl_ftp_done()
       * because we didn't transfer the any file */
      ftp->no_transfer = TRUE;
      state(conn, FTP_STOP);
      return CURLE_OK;
    }

    /* Set resume file transfer offset */
    infof(data, "Instructs server to resume from offset %" FORMAT_OFF_T
          "\n", conn->resume_from);

    NBFTPSENDF(conn, "REST %" FORMAT_OFF_T, conn->resume_from);

    state(conn, FTP_RETR_REST);

  }
  else {
    /* no resume */
    NBFTPSENDF(conn, "RETR %s", ftp->file);
    state(conn, FTP_RETR);
  }

  return result;
}