static CURLcode ftp_done(struct connectdata *conn, CURLcode status,
                              bool premature)
{
  struct SessionHandle *data = conn->data;
  struct FTP *ftp = data->state.proto.ftp;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  ssize_t nread;
  int ftpcode;
  CURLcode result=CURLE_OK;
  bool was_ctl_valid = ftpc->ctl_valid;
  char *path;
  char *path_to_use = data->state.path;

  if(!ftp)
    /* When the easy handle is removed from the multi while libcurl is still
     * trying to resolve the host name, it seems that the ftp struct is not
     * yet initialized, but the removal action calls Curl_done() which calls
     * this function. So we simply return success if no ftp pointer is set.
     */
    return CURLE_OK;

  switch(status) {
  case CURLE_BAD_DOWNLOAD_RESUME:
  case CURLE_FTP_WEIRD_PASV_REPLY:
  case CURLE_FTP_PORT_FAILED:
  case CURLE_FTP_COULDNT_SET_TYPE:
  case CURLE_FTP_COULDNT_RETR_FILE:
  case CURLE_UPLOAD_FAILED:
  case CURLE_REMOTE_ACCESS_DENIED:
  case CURLE_FILESIZE_EXCEEDED:
    /* the connection stays alive fine even though this happened */
    /* fall-through */
  case CURLE_OK: /* doesn't affect the control connection's status */
    if(!premature) {
      ftpc->ctl_valid = was_ctl_valid;
      break;
    }
    /* until we cope better with prematurely ended requests, let them
     * fallback as if in complete failure */
  default:       /* by default, an error means the control connection is
                    wedged and should not be used anymore */
    ftpc->ctl_valid = FALSE;
    ftpc->cwdfail = TRUE; /* set this TRUE to prevent us to remember the
                             current path, as this connection is going */
    conn->bits.close = TRUE; /* marked for closure */
    break;
  }

  /* now store a copy of the directory we are in */
  if(ftpc->prevpath)
    free(ftpc->prevpath);

  /* get the "raw" path */
  path = curl_easy_unescape(data, path_to_use, 0, NULL);
  if(!path) {
    /* out of memory, but we can limp along anyway (and should try to
     * since we're in the out of memory cleanup path) */
    ftpc->prevpath = NULL; /* no path */

  } else {
    size_t flen = ftpc->file?strlen(ftpc->file):0; /* file is "raw" already */
    size_t dlen = strlen(path)-flen;
    if(!ftpc->cwdfail) {
      if(dlen && (data->set.ftp_filemethod != FTPFILE_NOCWD)) {
        ftpc->prevpath = path;
        if(flen)
          /* if 'path' is not the whole string */
          ftpc->prevpath[dlen]=0; /* terminate */
      }
      else {
        /* we never changed dir */
        ftpc->prevpath=strdup("");
        free(path);
      }
      infof(data, "Remembering we are in dir \"%s\"\n", ftpc->prevpath);
    }
    else {
      ftpc->prevpath = NULL; /* no path */
      free(path);
    }
  }
  /* free the dir tree and file parts */
  freedirs(ftpc);

#if defined(HAVE_KRB4) || defined(HAVE_GSSAPI)
  Curl_sec_fflush_fd(conn, conn->sock[SECONDARYSOCKET]);
#endif

  /* shut down the socket to inform the server we're done */

#ifdef _WIN32_WCE
  shutdown(conn->sock[SECONDARYSOCKET],2);  /* SD_BOTH */
#endif

  if(conn->ssl[SECONDARYSOCKET].use) {
    /* The secondary socket is using SSL so we must close down that part first
       before we close the socket for real */
    Curl_ssl_close(conn, SECONDARYSOCKET);

    /* Note that we keep "use" set to TRUE since that (next) connection is
       still requested to use SSL */
  }
  sclose(conn->sock[SECONDARYSOCKET]);

  conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;

  if((ftp->transfer == FTPTRANSFER_BODY) && !status && !premature) {
    /*
     * Let's see what the server says about the transfer we just performed,
     * but lower the timeout as sometimes this connection has died while the
     * data has been transfered. This happens when doing through NATs etc that
     * abandon old silent connections.
     */
    long old_time = ftpc->response_time;

    ftpc->response_time = 60000; /* give it only a minute for now */

    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);

    ftpc->response_time = old_time; /* set this back to previous value */

    if(!nread && (CURLE_OPERATION_TIMEDOUT == result)) {
      failf(data, "control connection looks dead");
      ftpc->ctl_valid = FALSE; /* mark control connection as bad */
      conn->bits.close = TRUE; /* mark for closure */
    }

    if(result)
      return result;

    if(!ftpc->dont_check) {
      /* 226 Transfer complete, 250 Requested file action okay, completed. */
      if((ftpcode != 226) && (ftpcode != 250)) {
        failf(data, "server did not report OK, got %d", ftpcode);
        result = CURLE_PARTIAL_FILE;
      }
    }
  }

  if(result || premature)
    /* the response code from the transfer showed an error already so no
       use checking further */
    ;
  else if(data->set.upload) {
    if((-1 != data->set.infilesize) &&
       (data->set.infilesize != *ftp->bytecountp) &&
       !data->set.crlf &&
       (ftp->transfer == FTPTRANSFER_BODY)) {
      failf(data, "Uploaded unaligned file size (%" FORMAT_OFF_T
            " out of %" FORMAT_OFF_T " bytes)",
            *ftp->bytecountp, data->set.infilesize);
      result = CURLE_PARTIAL_FILE;
    }
  }
  else {
    if((-1 != data->req.size) &&
       (data->req.size != *ftp->bytecountp) &&
#ifdef CURL_DO_LINEEND_CONV
       /* Most FTP servers don't adjust their file SIZE response for CRLFs, so
        * we'll check to see if the discrepancy can be explained by the number
        * of CRLFs we've changed to LFs.
        */
       ((data->req.size + data->state.crlf_conversions) !=
        *ftp->bytecountp) &&
#endif /* CURL_DO_LINEEND_CONV */
       (data->req.maxdownload != *ftp->bytecountp)) {
      failf(data, "Received only partial file: %" FORMAT_OFF_T " bytes",
            *ftp->bytecountp);
      result = CURLE_PARTIAL_FILE;
    }
    else if(!ftpc->dont_check &&
            !*ftp->bytecountp &&
            (data->req.size>0)) {
      failf(data, "No data was received!");
      result = CURLE_FTP_COULDNT_RETR_FILE;
    }
  }

  /* clear these for next connection */
  ftp->transfer = FTPTRANSFER_BODY;
  ftpc->dont_check = FALSE;

  /* Send any post-transfer QUOTE strings? */
  if(!status && !result && !premature && data->set.postquote)
    result = ftp_sendquote(conn, data->set.postquote);

  return result;
}