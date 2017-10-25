CURLcode Curl_ftp_done(struct connectdata *conn, CURLcode status)
{
  struct SessionHandle *data = conn->data;
  struct FTP *ftp = conn->proto.ftp;
  ssize_t nread;
  int ftpcode;
  CURLcode result=CURLE_OK;
  bool was_ctl_valid = ftp->ctl_valid;
  size_t flen;
  size_t dlen;
  char *path;

  /* now store a copy of the directory we are in */
  if(ftp->prevpath)
    free(ftp->prevpath);

  path = curl_unescape(conn->path, 0); /* get the "raw" path */
  if(!path)
    return CURLE_OUT_OF_MEMORY;

  flen = ftp->file?strlen(ftp->file):0; /* file is "raw" already */
  dlen = strlen(path)-flen;
  if(dlen) {
    ftp->prevpath = path;
    if(flen)
      /* if 'path' is not the whole string */
      ftp->prevpath[dlen]=0; /* terminate */
    infof(data, "Remembering we are in dir %s\n", ftp->prevpath);
  }
  else {
    ftp->prevpath = NULL; /* no path */
    free(path);
  }
  /* free the dir tree and file parts */
  freedirs(ftp);

  ftp->ctl_valid = FALSE;

  if(data->set.upload) {
    if((-1 != data->set.infilesize) &&
       (data->set.infilesize != *ftp->bytecountp) &&
       !data->set.crlf &&
       !ftp->no_transfer) {
      failf(data, "Uploaded unaligned file size (%" FORMAT_OFF_T
            " out of %" FORMAT_OFF_T " bytes)",
            *ftp->bytecountp, data->set.infilesize);
      conn->bits.close = TRUE; /* close this connection since we don't
                                  know what state this error leaves us in */
      return CURLE_PARTIAL_FILE;
    }
  }
  else {
    if((-1 != conn->size) && (conn->size != *ftp->bytecountp) &&
       (conn->maxdownload != *ftp->bytecountp)) {
      failf(data, "Received only partial file: %" FORMAT_OFF_T " bytes",
            *ftp->bytecountp);
      conn->bits.close = TRUE; /* close this connection since we don't
                                  know what state this error leaves us in */
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

  switch(status) {
  case CURLE_BAD_DOWNLOAD_RESUME:
  case CURLE_FTP_WEIRD_PASV_REPLY:
  case CURLE_FTP_PORT_FAILED:
  case CURLE_FTP_COULDNT_SET_BINARY:
  case CURLE_FTP_COULDNT_RETR_FILE:
  case CURLE_FTP_ACCESS_DENIED:
    /* the connection stays alive fine even though this happened */
    /* fall-through */
  case CURLE_OK: /* doesn't affect the control connection's status */
    ftp->ctl_valid = was_ctl_valid;
    break;
  default:       /* by default, an error means the control connection is
                    wedged and should not be used anymore */
    ftp->ctl_valid = FALSE;
    break;
  }

#ifdef HAVE_KRB4
  Curl_sec_fflush_fd(conn, conn->sock[SECONDARYSOCKET]);
#endif

  /* shut down the socket to inform the server we're done */

#ifdef _WIN32_WCE
  shutdown(conn->sock[SECONDARYSOCKET],2);  /* SD_BOTH */
#endif

  sclose(conn->sock[SECONDARYSOCKET]);

  conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;

  if(!ftp->no_transfer && !status) {
    /* Let's see what the server says about the transfer we just performed,
     * but lower the timeout as sometimes this connection has died while the
     * data has been transfered. This happens when doing through NATs etc that
     * abandon old silent connections.
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

  if (!result && conn->sec_conn) {   /* 3rd party transfer */
    /* "done" with the secondary connection */
    result = Curl_ftp_done(conn->sec_conn, status);
  }

  /* Send any post-transfer QUOTE strings? */
  if(!status && !result && data->set.postquote)
    result = ftp_sendquote(conn, data->set.postquote);

  return result;
}