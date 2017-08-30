  if(result)

    return result;



  if((data->state.authhost.multi || data->state.authproxy.multi) &&

     (httpreq != HTTPREQ_GET) &&

     (httpreq != HTTPREQ_HEAD)) {

    /* Auth is required and we are not authenticated yet. Make a PUT or POST

       with content-length zero as a "probe". */

    conn->bits.authneg = TRUE;

  }

  else

    conn->bits.authneg = FALSE;



  Curl_safefree(conn->allocptr.ref);

  if(data->change.referer && !checkheaders(data, "Referer:"))

    conn->allocptr.ref = aprintf("Referer: %s\r\n", data->change.referer);

  else

    conn->allocptr.ref = NULL;



  if(data->set.cookie && !checkheaders(data, "Cookie:"))

    addcookies = data->set.cookie;



  if(!checkheaders(data, "Accept-Encoding:") &&

     data->set.encoding) {

    Curl_safefree(conn->allocptr.accept_encoding);

    conn->allocptr.accept_encoding =

      aprintf("Accept-Encoding: %s\r\n", data->set.encoding);

    if(!conn->allocptr.accept_encoding)

      return CURLE_OUT_OF_MEMORY;

  }



  ptr = checkheaders(data, "Transfer-Encoding:");

  if(ptr) {

    /* Some kind of TE is requested, check if 'chunked' is chosen */

    conn->bits.upload_chunky =

      Curl_compareheader(ptr, "Transfer-Encoding:", "chunked");

  }

  else {

    if (httpreq == HTTPREQ_GET)

      conn->bits.upload_chunky = FALSE;

    if(conn->bits.upload_chunky)

      te = "Transfer-Encoding: chunked\r\n";

  }



  Curl_safefree(conn->allocptr.host);



  ptr = checkheaders(data, "Host:");

  if(ptr && (!data->state.this_is_a_follow ||

             curl_strequal(data->state.first_host, conn->host.name))) {

#if !defined(CURL_DISABLE_COOKIES)

    /* If we have a given custom Host: header, we extract the host name in

       order to possibly use it for cookie reasons later on. We only allow the

       custom Host: header if this is NOT a redirect, as setting Host: in the

       redirected request is being out on thin ice. Except if the host name

       is the same as the first one! */

    char *start = ptr+strlen("Host:");

    while(*start && ISSPACE(*start ))

      start++;

    ptr = start; /* start host-scanning here */



    /* scan through the string to find the end (space or colon) */

    while(*ptr && !ISSPACE(*ptr) && !(':'==*ptr))

      ptr++;



    if(ptr != start) {

      size_t len=ptr-start;

      Curl_safefree(conn->allocptr.cookiehost);

      conn->allocptr.cookiehost = malloc(len+1);

      if(!conn->allocptr.cookiehost)

        return CURLE_OUT_OF_MEMORY;

      memcpy(conn->allocptr.cookiehost, start, len);

      conn->allocptr.cookiehost[len]=0;

    }

#endif



    conn->allocptr.host = NULL;

  }

