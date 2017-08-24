  if(result)
    return result;

  if((!data->state.authhost.done || !data->state.authproxy.done ) &&
     (httpreq != HTTPREQ_GET)) {
    /* Until we are authenticated, we switch over to HEAD. Unless its a GET
       we want to do. The explanation for this is rather long and boring, but
       the point is that it can't be done otherwise without risking having to
       send the POST or PUT data multiple times. */
    httpreq = HTTPREQ_HEAD;
    request = (char *)"HEAD";
    conn->bits.no_body = TRUE;
    conn->bits.authprobe = TRUE; /* this is a request done to probe for
                                    authentication methods */
  }
  else
    conn->bits.authprobe = FALSE;

  Curl_safefree(conn->allocptr.ref);
  if(data->change.referer && !checkheaders(data, "Referer:"))
    conn->allocptr.ref = aprintf("Referer: %s\015\012", data->change.referer);
  else
    conn->allocptr.ref = NULL;

  if(data->set.cookie && !checkheaders(data, "Cookie:"))
    addcookies = data->set.cookie;

  if(!conn->bits.upload_chunky && (httpreq != HTTPREQ_GET)) {
    /* not a chunky transfer yet, but data is to be sent */
    ptr = checkheaders(data, "Transfer-Encoding:");
    if(ptr) {
      /* Some kind of TE is requested, check if 'chunked' is chosen */
      conn->bits.upload_chunky =
        Curl_compareheader(ptr, "Transfer-Encoding:", "chunked");
      te = "";
    }
  }
  else if(conn->bits.upload_chunky) {
    /* RFC2616 section 4.4:
       Messages MUST NOT include both a Content-Length header field and a
       non-identity transfer-coding. If the message does include a non-
       identity transfer-coding, the Content-Length MUST be ignored. */

    if(!checkheaders(data, "Transfer-Encoding:")) {
      te = "Transfer-Encoding: chunked\r\n";
    }
    else {
      te = "";
      conn->bits.upload_chunky = FALSE; /* transfer-encoding was disabled,
                                           so don't chunkify this! */
    }
  }

  Curl_safefree(conn->allocptr.host);

  ptr = checkheaders(data, "Host:");
  if(ptr && !data->state.this_is_a_follow) {
    /* If we have a given custom Host: header, we extract the host name in
       order to possibly use it for cookie reasons later on. We only allow the
       custom Host: header if this is NOT a redirect, as setting Host: in the
       redirected request is being out on thin ice. */
    char *start = ptr+strlen("Host:");
    while(*start && isspace((int)*start ))
      start++;
    ptr = start; /* start host-scanning here */

    /* scan through the string to find the end (space or colon) */
    while(*ptr && !isspace((int)*ptr) && !(':'==*ptr))
      ptr++;

    if(ptr != start) {
      size_t len=ptr-start;
      conn->allocptr.cookiehost = malloc(len+1);
      if(!conn->allocptr.cookiehost)
        return CURLE_OUT_OF_MEMORY;
      memcpy(conn->allocptr.cookiehost, start, len);
      conn->allocptr.cookiehost[len]=0;
    }

    conn->allocptr.host = NULL;
  }
