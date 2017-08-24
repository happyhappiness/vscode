{
    if(proxyptr[0]=='/')
      /* If the first character in the proxy string is a slash, fail
         immediately. The following code will otherwise clear the string which
         will lead to code running as if no proxy was set! */
      return CURLE_COULDNT_RESOLVE_PROXY;

    /* without a port number after the host name, some people seem to use
       a slash so we strip everything from the first slash */
    atsign = strchr(proxyptr, '/');
    if(atsign)
      *atsign = '\0'; /* cut off path part from host name */

    if(data->set.proxyport)
      /* None given in the proxy string, then get the default one if it is
         given */
      port = data->set.proxyport;
    else {
      if(proxytype == CURLPROXY_HTTPS)
        port = CURL_DEFAULT_HTTPS_PROXY_PORT;
      else
        port = CURL_DEFAULT_PROXY_PORT;
    }
  }