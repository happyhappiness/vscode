                            addr,
                            connectport,
                            &conn->secondarysocket,
                            &conninfo);
  
  if((CURLE_OK == result) &&       
     data->set.verbose)
    /* this just dumps information about this second connection */
    ftp_pasv_verbose(conn, conninfo, newhost, connectport);
  
  if(CURLE_OK != result)
    return result;

  if (data->set.tunnel_thru_httpproxy) {
    /* We want "seamless" FTP operations through HTTP proxy tunnel */
    result = Curl_ConnectHTTPProxyTunnel(conn, conn->secondarysocket,
                                         newhost, newport);
    if(CURLE_OK != result)
      return result;
  }

  return CURLE_OK;
}

/***********************************************************************
 *
 * ftp_perform()
 *
 * This is the actual DO function for FTP. Get a file/directory according to
 * the options previously setup.
 */

static
CURLcode ftp_perform(struct connectdata *conn)
{
  /* this is FTP and no proxy */
  ssize_t nread;
  CURLcode result;
  struct SessionHandle *data=conn->data;
  char *buf = data->state.buffer; /* this is our buffer */

  /* the ftp struct is already inited in ftp_connect() */
  struct FTP *ftp = conn->proto.ftp;

  long *bytecountp = ftp->bytecountp;
  int ftpcode; /* for ftp status */

  /* Send any QUOTE strings? */
  if(data->set.quote) {
    if ((result = ftp_sendquote(conn, data->set.quote)) != CURLE_OK)
      return result;
  }
    
  /* This is a re-used connection. Since we change directory to where the
     transfer is taking place, we must now get back to the original dir
     where we ended up after login: */
  if (conn->bits.reuse) {
    if ((result = ftp_cwd(conn, ftp->entrypath)) != CURLE_OK)
      return result;
  }

  /* change directory first! */
  if(ftp->dir && ftp->dir[0]) {
    if ((result = ftp_cwd(conn, ftp->dir)) != CURLE_OK)
        return result;
  }

  /* Requested time of file? */
  if(data->set.get_filetime && ftp->file) {
    result = ftp_getfiletime(conn, ftp->file);
    if(result)
      return result;
  }

  /* If we have selected NOBODY and HEADER, it means that we only want file
     information. Which in FTP can't be much more than the file size and
     date. */
  if(data->set.no_body && data->set.include_header) {
    /* The SIZE command is _not_ RFC 959 specified, and therefor many servers
       may not support it! It is however the only way we have to get a file's
       size! */
    ssize_t filesize;

    /* Some servers return different sizes for different modes, and thus we
       must set the proper type before we check the size */
    result = ftp_transfertype(conn, data->set.ftp_ascii);
    if(result)
      return result;

    /* failing to get size is not a serious error */
    result = ftp_getsize(conn, ftp->file, &filesize);

    if(CURLE_OK == result) {
      sprintf(buf, "Content-Length: %d\r\n", filesize);
      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
      if(result)
        return result;
    }

    /* If we asked for a time of the file and we actually got one as
       well, we "emulate" a HTTP-style header in our output. */

#ifdef HAVE_STRFTIME
    if(data->set.get_filetime && data->info.filetime) {
      struct tm *tm;
#ifdef HAVE_LOCALTIME_R
      struct tm buffer;
      tm = (struct tm *)localtime_r(&data->info.filetime, &buffer);
#else
      tm = localtime((unsigned long *)&data->info.filetime);
#endif
      /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
      strftime(buf, BUFSIZE-1, "Last-Modified: %a, %d %b %Y %H:%M:%S %Z\r\n",
               tm);
      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
      if(result)
        return result;
    }
#endif

    return CURLE_OK;
  }

  if(data->set.no_body)
    /* don't transfer the data */
    ;
  /* Get us a second connection up and connected */
  else if(data->set.ftp_use_port) {
    /* We have chosen to use the PORT command */
    result = ftp_use_port(conn);
    if(CURLE_OK == result)
      /* we have the data connection ready */
      infof(data, "Connected the data stream with PORT!\n");
  }
  else {
    /* We have chosen (this is default) to use the PASV command */
    result = ftp_use_pasv(conn);
    if(CURLE_OK == result)
      infof(data, "Connected the data stream with PASV!\n");
  }
  
  if(result)
    return result;

  if(data->set.upload) {

