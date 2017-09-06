static
CURLcode ftp_perform(struct connectdata *conn,
                     bool *connected)  /* for the TCP connect status after
                                          PASV / PORT */
{
  /* this is FTP and no proxy */
  CURLcode result=CURLE_OK;
  struct SessionHandle *data=conn->data;
  char *buf = data->state.buffer; /* this is our buffer */

  /* the ftp struct is already inited in Curl_ftp_connect() */
  struct FTP *ftp = conn->proto.ftp;

  /* Send any QUOTE strings? */
  if(data->set.quote) {
    if ((result = ftp_sendquote(conn, data->set.quote)) != CURLE_OK)
      return result;
  }

  /* This is a re-used connection. Since we change directory to where the
     transfer is taking place, we must now get back to the original dir
     where we ended up after login: */
  if (conn->bits.reuse && ftp->entrypath) {
    if ((result = ftp_cwd_and_mkd(conn, ftp->entrypath)) != CURLE_OK)
      return result;
  }

  {
    int i; /* counter for loop */
    for (i=0; i < ftp->dirdepth; i++) {
      /* RFC 1738 says empty components should be respected too, but
         that is plain stupid since CWD can't be used with an empty argument */
      if ((result = ftp_cwd_and_mkd(conn, ftp->dirs[i])) != CURLE_OK)
        return result;
    }
  }

  /* Requested time of file or time-depended transfer? */
  if((data->set.get_filetime || data->set.timecondition) &&
     ftp->file) {
    result = ftp_getfiletime(conn, ftp->file);
    switch( result )
      {
      case CURLE_FTP_COULDNT_RETR_FILE:
      case CURLE_OK:
        if(data->set.timecondition) {
          if((data->info.filetime > 0) && (data->set.timevalue > 0)) {
            switch(data->set.timecondition) {
            case CURL_TIMECOND_IFMODSINCE:
            default:
              if(data->info.filetime < data->set.timevalue) {
                infof(data, "The requested document is not new enough\n");
                ftp->no_transfer = TRUE; /* mark this to not transfer data */
                return CURLE_OK;
              }
              break;
            case CURL_TIMECOND_IFUNMODSINCE:
              if(data->info.filetime > data->set.timevalue) {
                infof(data, "The requested document is not old enough\n");
                ftp->no_transfer = TRUE; /* mark this to not transfer data */
                return CURLE_OK;
              }
              break;
            } /* switch */
          }
          else {
            infof(data, "Skipping time comparison\n");
          }
        }
        break;
      default:
        return result;
      } /* switch */
  }

  /* If we have selected NOBODY and HEADER, it means that we only want file
     information. Which in FTP can't be much more than the file size and
     date. */
  if(conn->bits.no_body && data->set.include_header && ftp->file) {
    /* The SIZE command is _not_ RFC 959 specified, and therefor many servers
       may not support it! It is however the only way we have to get a file's
       size! */
    curl_off_t filesize;
    ssize_t nread;
    int ftpcode;

    ftp->no_transfer = TRUE; /* this means no actual transfer is made */

    /* Some servers return different sizes for different modes, and thus we
       must set the proper type before we check the size */
    result = ftp_transfertype(conn, data->set.ftp_ascii);
    if(result)
      return result;

    /* failing to get size is not a serious error */
    result = ftp_getsize(conn, ftp->file, &filesize);

    if(CURLE_OK == result) {
      snprintf(buf, sizeof(data->state.buffer),
               "Content-Length: %" FORMAT_OFF_T "\r\n", filesize);
      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
      if(result)
        return result;
    }

    /* Determine if server can respond to REST command and therefore
       whether it can do a range */
    FTPSENDF(conn, "REST 0", NULL);
    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);

    if ((CURLE_OK == result) && (ftpcode == 350)) {
      result = Curl_client_write(data, CLIENTWRITE_BOTH,
                                 (char *)"Accept-ranges: bytes\r\n", 0);
      if(result)
        return result;
    }

    /* If we asked for a time of the file and we actually got one as
       well, we "emulate" a HTTP-style header in our output. */

#ifdef HAVE_STRFTIME
    if(data->set.get_filetime && (data->info.filetime>=0) ) {
      struct tm *tm;
      time_t clock = (time_t)data->info.filetime;
#ifdef HAVE_GMTIME_R
      struct tm buffer;
      tm = (struct tm *)gmtime_r(&clock, &buffer);
#else
      tm = gmtime(&clock);
#endif
      /* format: "Tue, 15 Nov 1994 12:45:26" */
      strftime(buf, BUFSIZE-1, "Last-Modified: %a, %d %b %Y %H:%M:%S GMT\r\n",
               tm);
      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
      if(result)
        return result;
    }
#endif

    return CURLE_OK;
  }

  if(conn->bits.no_body)
    /* doesn't really transfer any data */
    ftp->no_transfer = TRUE;
  /* Get us a second connection up and connected */
  else if(data->set.ftp_use_port) {
    /* We have chosen to use the PORT command */
    result = ftp_use_port(conn);
    if(CURLE_OK == result) {
      /* we have the data connection ready */
      infof(data, "Ordered connect of the data stream with PORT!\n");
      *connected = TRUE; /* mark us "still connected" */
    }
  }
  else {
    /* We have chosen (this is default) to use the PASV command */
    result = ftp_use_pasv(conn, connected);
    if(CURLE_OK == result && *connected)
      infof(data, "Connected the data stream with PASV!\n");
  }

  return result;
}