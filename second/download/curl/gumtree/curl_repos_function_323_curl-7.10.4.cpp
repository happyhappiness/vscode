CURLcode Curl_ftp_done(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  struct FTP *ftp = conn->proto.ftp;
  ssize_t nread;
  int ftpcode;
  CURLcode result=CURLE_OK;

  if(data->set.upload) {
    if((-1 != data->set.infilesize) &&
       (data->set.infilesize != *ftp->bytecountp) &&
       !data->set.crlf) {
      failf(data, "Uploaded unaligned file size (%d out of %d bytes)",
            *ftp->bytecountp, data->set.infilesize);
      return CURLE_PARTIAL_FILE;
    }
  }
  else {
    if((-1 != conn->size) && (conn->size != *ftp->bytecountp) &&
       (conn->maxdownload != *ftp->bytecountp)) {
      failf(data, "Received only partial file: %d bytes", *ftp->bytecountp);
      return CURLE_PARTIAL_FILE;
    }
    else if(!ftp->dont_check &&
            !*ftp->bytecountp &&
            (conn->size>0)) {
      /* We consider this an error, but there's no true FTP error received
         why we need to continue to "read out" the server response too.
         We don't want to leave a "waiting" server reply if we'll get told
         to make a second request on this same connection! */
      failf(data, "No data was received!");
      result = CURLE_FTP_COULDNT_RETR_FILE;
    }
  }

#ifdef KRB4
  Curl_sec_fflush_fd(conn, conn->secondarysocket);
#endif
  /* shut down the socket to inform the server we're done */
  sclose(conn->secondarysocket);
  conn->secondarysocket = -1;

  if(!ftp->no_transfer) {
    /* Let's see what the server says about the transfer we just performed,
       but lower the timeout as sometimes this connection has died while 
       the data has been transfered. This happens when doing through NATs
       etc that abandon old silent connections.
    */
    ftp->response_time = 60; /* give it only a minute for now */

    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);

    ftp->response_time = 3600; /* set this back to one hour waits */
  
    if(!nread && (CURLE_OPERATION_TIMEDOUT == result)) {
      failf(data, "control connection looks dead");
      return result;
    }

    if(result)
      return result;

    if(!ftp->dont_check) {
      /* 226 Transfer complete, 250 Requested file action okay, completed. */
      if((ftpcode != 226) && (ftpcode != 250)) {
        failf(data, "server did not report OK, got %d", ftpcode);
        return CURLE_FTP_WRITE_ERROR;
      }
    }
  }

  /* clear these for next connection */
  ftp->no_transfer = FALSE;
  ftp->dont_check = FALSE; 

  /* Send any post-transfer QUOTE strings? */
  if(!result && data->set.postquote)
    result = ftp_sendquote(conn, data->set.postquote);

  return result;
}