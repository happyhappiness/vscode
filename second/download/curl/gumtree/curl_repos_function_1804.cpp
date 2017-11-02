static CURLcode ftp_setup_connection(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  char *type;
  char command;
  struct FTP *ftp;

  if(conn->bits.httpproxy && !data->set.tunnel_thru_httpproxy) {
    /* Unless we have asked to tunnel ftp operations through the proxy, we
       switch and use HTTP operations only */
#ifndef CURL_DISABLE_HTTP
    if(conn->handler == &Curl_handler_ftp)
      conn->handler = &Curl_handler_ftp_proxy;
    else {
#ifdef USE_SSL
      conn->handler = &Curl_handler_ftps_proxy;
#else
      failf(data, "FTPS not supported!");
      return CURLE_UNSUPPORTED_PROTOCOL;
#endif
    }
    /* set it up as a HTTP connection instead */
    return conn->handler->setup_connection(conn);
#else
    failf(data, "FTP over http proxy requires HTTP support built-in!");
    return CURLE_UNSUPPORTED_PROTOCOL;
#endif
  }

  conn->data->req.protop = ftp = malloc(sizeof(struct FTP));
  if(NULL == ftp)
    return CURLE_OUT_OF_MEMORY;

  data->state.path++;   /* don't include the initial slash */
  data->state.slash_removed = TRUE; /* we've skipped the slash */

  /* FTP URLs support an extension like ";type=<typecode>" that
   * we'll try to get now! */
  type = strstr(data->state.path, ";type=");

  if(!type)
    type = strstr(conn->host.rawalloc, ";type=");

  if(type) {
    *type = 0;                     /* it was in the middle of the hostname */
    command = Curl_raw_toupper(type[6]);
    conn->bits.type_set = TRUE;

    switch (command) {
    case 'A': /* ASCII mode */
      data->set.prefer_ascii = TRUE;
      break;

    case 'D': /* directory mode */
      data->set.ftp_list_only = TRUE;
      break;

    case 'I': /* binary mode */
    default:
      /* switch off ASCII */
      data->set.prefer_ascii = FALSE;
      break;
    }
  }

  /* get some initial data into the ftp struct */
  ftp->bytecountp = &conn->data->req.bytecount;
  ftp->transfer = FTPTRANSFER_BODY;
  ftp->downloadsize = 0;

  /* No need to duplicate user+password, the connectdata struct won't change
     during a session, but we re-init them here since on subsequent inits
     since the conn struct may have changed or been replaced.
  */
  ftp->user = conn->user;
  ftp->passwd = conn->passwd;
  if(isBadFtpString(ftp->user))
    return CURLE_URL_MALFORMAT;
  if(isBadFtpString(ftp->passwd))
    return CURLE_URL_MALFORMAT;

  conn->proto.ftpc.known_filesize = -1; /* unknown size for now */

  return CURLE_OK;
}