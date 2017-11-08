static CURLcode ftp_setup_connection(struct connectdata * conn)
{
  struct SessionHandle *data = conn->data;
  char * type;
  char command;

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

#else
    failf(data, "FTP over http proxy requires HTTP support built-in!");
    return CURLE_UNSUPPORTED_PROTOCOL;
#endif
  }

  data->state.path++;   /* don't include the initial slash */

  /* FTP URLs support an extension like ";type=<typecode>" that
   * we'll try to get now! */
  type = strstr(data->state.path, ";type=");

  if(!type)
    type = strstr(conn->host.rawalloc, ";type=");

  if(type) {
    *type = 0;                     /* it was in the middle of the hostname */
    command = (char) toupper((int) type[6]);

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

  return CURLE_OK;
}