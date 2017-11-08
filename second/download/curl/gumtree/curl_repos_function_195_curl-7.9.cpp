CURLcode Curl_ftp_done(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  struct FTP *ftp = conn->proto.ftp;
  ssize_t nread;
  char *buf = data->state.buffer; /* this is our buffer */
  int ftpcode;

  if(data->set.upload) {
    if((-1 != data->set.infilesize) && (data->set.infilesize != *ftp->bytecountp)) {
      failf(data, "Wrote only partial file (%d out of %d bytes)",
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
    else if(!conn->bits.resume_done &&
            !data->set.no_body &&
            (0 == *ftp->bytecountp)) {
      failf(data, "No data was received!");
      return CURLE_FTP_COULDNT_RETR_FILE;
    }
  }

#ifdef KRB4
  Curl_sec_fflush_fd(conn, conn->secondarysocket);
#endif
  /* shut down the socket to inform the server we're done */
  sclose(conn->secondarysocket);
  conn->secondarysocket = -1;

  if(!data->set.no_body && !conn->bits.resume_done) {  
    /* now let's see what the server says about the transfer we
       just performed: */
    nread = Curl_GetFTPResponse(conn->firstsocket, buf, conn, &ftpcode);
    if(nread < 0)
      return CURLE_OPERATION_TIMEOUTED;

    /* 226 Transfer complete, 250 Requested file action okay, completed. */
    if((ftpcode != 226) && (ftpcode != 250)) {
      failf(data, "server did not report OK, got %d", ftpcode);
      return CURLE_FTP_WRITE_ERROR;
    }
  }

  conn->bits.resume_done = FALSE; /* clean this for next connection */

  /* Send any post-transfer QUOTE strings? */
  if(data->set.postquote) {
    CURLcode result = _ftp_sendquote(conn, data->set.postquote);
    return result;
  }

  return CURLE_OK;
}