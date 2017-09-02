CURLcode Curl_http(struct connectdata *conn, bool *done)
{
  struct SessionHandle *data=conn->data;
  char *buf = data->state.buffer; /* this is a short cut to the buffer */
  CURLcode result=CURLE_OK;
  struct HTTP *http;
  char *ppath = data->reqdata.path;
  char *host = conn->host.name;
  const char *te = ""; /* transfer-encoding */
  char *ptr;
  char *request;
  Curl_HttpReq httpreq = data->set.httpreq;
  char *addcookies = NULL;
  curl_off_t included_body = 0;

  /* Always consider the DO phase done after this function call, even if there
     may be parts of the request that is not yet sent, since we can deal with
     the rest of the request in the PERFORM phase. */
  *done = TRUE;

  if(!data->reqdata.proto.http) {
    /* Only allocate this struct if we don't already have it! */

    http = (struct HTTP *)malloc(sizeof(struct HTTP));
    if(!http)
      return CURLE_OUT_OF_MEMORY;
    memset(http, 0, sizeof(struct HTTP));
    data->reqdata.proto.http = http;
  }
  else
    http = data->reqdata.proto.http;

  /* We default to persistent connections */
  conn->bits.close = FALSE;

  if ( (conn->protocol&(PROT_HTTP|PROT_FTP)) &&
       data->set.upload) {
    httpreq = HTTPREQ_PUT;
  }

  /* Now set the 'request' pointer to the proper request string */
  if(data->set.customrequest)
    request = data->set.customrequest;
  else {
    if(conn->bits.no_body)
      request = (char *)"HEAD";
    else {
      curlassert((httpreq > HTTPREQ_NONE) && (httpreq < HTTPREQ_LAST));
      switch(httpreq) {
      case HTTPREQ_POST:
      case HTTPREQ_POST_FORM:
        request = (char *)"POST";
        break;
      case HTTPREQ_PUT:
        request = (char *)"PUT";
        break;
      default: /* this should never happen */
      case HTTPREQ_GET:
        request = (char *)"GET";
        break;
      case HTTPREQ_HEAD:
        request = (char *)"HEAD";
        break;
      }
    }
  }

  /* The User-Agent string might have been allocated in url.c already, because
     it might have been used in the proxy connect, but if we have got a header
     with the user-agent string specified, we erase the previously made string
     here. */
  if(checkheaders(data, "User-Agent:") && conn->allocptr.uagent) {
    free(conn->allocptr.uagent);
    conn->allocptr.uagent=NULL;
  }

  /* setup the authentication headers */
  result = Curl_http_output_auth(conn, request, ppath, FALSE);
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
  else {
    /* When building Host: headers, we must put the host name within
       [brackets] if the host name is a plain IPv6-address. RFC2732-style. */

    if(((conn->protocol&PROT_HTTPS) && (conn->remote_port == PORT_HTTPS)) ||
       (!(conn->protocol&PROT_HTTPS) && (conn->remote_port == PORT_HTTP)) )
      /* If (HTTPS on port 443) OR (non-HTTPS on port 80) then don't include
         the port number in the host string */
      conn->allocptr.host = aprintf("Host: %s%s%s\r\n",
                                    conn->bits.ipv6_ip?"[":"",
                                    host,
                                    conn->bits.ipv6_ip?"]":"");
    else
      conn->allocptr.host = aprintf("Host: %s%s%s:%d\r\n",
                                    conn->bits.ipv6_ip?"[":"",
                                    host,
                                    conn->bits.ipv6_ip?"]":"",
                                    conn->remote_port);

    if(!conn->allocptr.host)
      /* without Host: we can't make a nice request */
      return CURLE_OUT_OF_MEMORY;
  }

  if (conn->bits.httpproxy && !conn->bits.tunnel_proxy)  {
    /* Using a proxy but does not tunnel through it */

    /* The path sent to the proxy is in fact the entire URL. But if the remote
       host is a IDN-name, we must make sure that the request we produce only
       uses the encoded host name! */
    if(conn->host.dispname != conn->host.name) {
      char *url = data->change.url;
      ptr = strstr(url, conn->host.dispname);
      if(ptr) {
        /* This is where the display name starts in the URL, now replace this
           part with the encoded name. TODO: This method of replacing the host
           name is rather crude as I believe there's a slight risk that the
           user has entered a user name or password that contain the host name
           string. */
        size_t currlen = strlen(conn->host.dispname);
        size_t newlen = strlen(conn->host.name);
        size_t urllen = strlen(url);

        char *newurl;

        newurl = malloc(urllen + newlen - currlen + 1);
        if(newurl) {
          /* copy the part before the host name */
          memcpy(newurl, url, ptr - url);
          /* append the new host name instead of the old */
          memcpy(newurl + (ptr - url), conn->host.name, newlen);
          /* append the piece after the host name */
          memcpy(newurl + newlen + (ptr - url),
                 ptr + currlen, /* copy the trailing zero byte too */
                 urllen - (ptr-url) - currlen + 1);
          if(data->change.url_alloc)
            free(data->change.url);
          data->change.url = newurl;
          data->change.url_alloc = TRUE;
        }
        else
          return CURLE_OUT_OF_MEMORY;
      }
    }
    ppath = data->change.url;
  }
  if(HTTPREQ_POST_FORM == httpreq) {
    /* we must build the whole darned post sequence first, so that we have
       a size of the whole shebang before we start to send it */
     result = Curl_getFormData(&http->sendit, data->set.httppost,
                               checkheaders(data, "Content-Type:"),
                               &http->postsize);
     if(CURLE_OK != result) {
       /* Curl_getFormData() doesn't use failf() */
       failf(data, "failed creating formpost data");
       return result;
     }
  }


  http->p_pragma =
    (!checkheaders(data, "Pragma:") &&
     (conn->bits.httpproxy && !conn->bits.tunnel_proxy) )?
    "Pragma: no-cache\r\n":NULL;

  if(!checkheaders(data, "Accept:"))
    http->p_accept = "Accept: */*\r\n";

  if(( (HTTPREQ_POST == httpreq) ||
       (HTTPREQ_POST_FORM == httpreq) ||
       (HTTPREQ_PUT == httpreq) ) &&
     data->reqdata.resume_from) {
    /**********************************************************************
     * Resuming upload in HTTP means that we PUT or POST and that we have
     * got a resume_from value set. The resume value has already created
     * a Range: header that will be passed along. We need to "fast forward"
     * the file the given number of bytes and decrease the assume upload
     * file size before we continue this venture in the dark lands of HTTP.
     *********************************************************************/

    if(data->reqdata.resume_from < 0 ) {
      /*
       * This is meant to get the size of the present remote-file by itself.
       * We don't support this now. Bail out!
       */
       data->reqdata.resume_from = 0;
    }

    if(data->reqdata.resume_from) {
      /* do we still game? */
      curl_off_t passed=0;

      /* Now, let's read off the proper amount of bytes from the
         input. If we knew it was a proper file we could've just
         fseek()ed but we only have a stream here */
      do {
        size_t readthisamountnow = (size_t)(data->reqdata.resume_from - passed);
        size_t actuallyread;

        if(readthisamountnow > BUFSIZE)
          readthisamountnow = BUFSIZE;

        actuallyread =
          data->set.fread(data->state.buffer, 1, (size_t)readthisamountnow,
                          data->set.in);

        passed += actuallyread;
        if(actuallyread != readthisamountnow) {
          failf(data, "Could only read %" FORMAT_OFF_T
                " bytes from the input",
                passed);
          return CURLE_READ_ERROR;
        }
      } while(passed != data->reqdata.resume_from); /* loop until done */

      /* now, decrease the size of the read */
      if(data->set.infilesize>0) {
        data->set.infilesize -= data->reqdata.resume_from;

        if(data->set.infilesize <= 0) {
          failf(data, "File already completely uploaded");
          return CURLE_PARTIAL_FILE;
        }
      }
      /* we've passed, proceed as normal */
    }
  }
  if(data->reqdata.use_range) {
    /*
     * A range is selected. We use different headers whether we're downloading
     * or uploading and we always let customized headers override our internal
     * ones if any such are specified.
     */
    if((httpreq == HTTPREQ_GET) &&
       !checkheaders(data, "Range:")) {
      /* if a line like this was already allocated, free the previous one */
      if(conn->allocptr.rangeline)
        free(conn->allocptr.rangeline);
      conn->allocptr.rangeline = aprintf("Range: bytes=%s\r\n", data->reqdata.range);
    }
    else if((httpreq != HTTPREQ_GET) &&
            !checkheaders(data, "Content-Range:")) {

      if(data->reqdata.resume_from) {
        /* This is because "resume" was selected */
        curl_off_t total_expected_size=
          data->reqdata.resume_from + data->set.infilesize;
        conn->allocptr.rangeline =
            aprintf("Content-Range: bytes %s%" FORMAT_OFF_T
                    "/%" FORMAT_OFF_T "\r\n",
                    data->reqdata.range, total_expected_size-1,
                    total_expected_size);
      }
      else {
        /* Range was selected and then we just pass the incoming range and
           append total size */
        conn->allocptr.rangeline =
            aprintf("Content-Range: bytes %s/%" FORMAT_OFF_T "\r\n",
                    data->reqdata.range, data->set.infilesize);
      }
    }
  }

  {
    /* Use 1.1 unless the use specificly asked for 1.0 */
    const char *httpstring=
      data->set.httpversion==CURL_HTTP_VERSION_1_0?"1.0":"1.1";

    send_buffer *req_buffer;
    curl_off_t postsize; /* off_t type to be able to hold a large file size */

    /* initialize a dynamic send-buffer */
    req_buffer = add_buffer_init();

    if(!req_buffer)
      return CURLE_OUT_OF_MEMORY;

    /* add the main request stuff */
    result =
      add_bufferf(req_buffer,
                  "%s " /* GET/HEAD/POST/PUT */
                  "%s HTTP/%s\r\n" /* path + HTTP version */
                  "%s" /* proxyuserpwd */
                  "%s" /* userpwd */
                  "%s" /* range */
                  "%s" /* user agent */
                  "%s" /* host */
                  "%s" /* pragma */
                  "%s" /* accept */
                  "%s" /* accept-encoding */
                  "%s" /* referer */
                  "%s" /* Proxy-Connection */
                  "%s",/* transfer-encoding */

                request,
                ppath,
                httpstring,
                conn->allocptr.proxyuserpwd?
                conn->allocptr.proxyuserpwd:"",
                conn->allocptr.userpwd?conn->allocptr.userpwd:"",
                (data->reqdata.use_range && conn->allocptr.rangeline)?
                conn->allocptr.rangeline:"",
                (data->set.useragent && *data->set.useragent && conn->allocptr.uagent)?
                conn->allocptr.uagent:"",
                (conn->allocptr.host?conn->allocptr.host:""), /* Host: host */
                http->p_pragma?http->p_pragma:"",
                http->p_accept?http->p_accept:"",
                (data->set.encoding && *data->set.encoding && conn->allocptr.accept_encoding)?
                conn->allocptr.accept_encoding:"",
                (data->change.referer && conn->allocptr.ref)?conn->allocptr.ref:"" /* Referer: <data> */,
                (conn->bits.httpproxy &&
                 !conn->bits.tunnel_proxy &&
                 !checkheaders(data, "Proxy-Connection:"))?
                  "Proxy-Connection: Keep-Alive\r\n":"",
                te
                );

    if(result)
      return result;

#if !defined(CURL_DISABLE_COOKIES)
    if(data->cookies || addcookies) {
      struct Cookie *co=NULL; /* no cookies from start */
      int count=0;

      if(data->cookies) {
        Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
        co = Curl_cookie_getlist(data->cookies,
                                 conn->allocptr.cookiehost?
                                 conn->allocptr.cookiehost:host, data->reqdata.path,
                                 (bool)(conn->protocol&PROT_HTTPS?TRUE:FALSE));
        Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
      }
      if(co) {
        struct Cookie *store=co;
        /* now loop through all cookies that matched */
        while(co) {
          if(co->value) {
            if(0 == count) {
              result = add_bufferf(req_buffer, "Cookie: ");
              if(result)
                break;
            }
            result = add_bufferf(req_buffer,
                                 "%s%s=%s", count?"; ":"",
                                 co->name, co->value);
            if(result)
              break;
            count++;
          }
          co = co->next; /* next cookie please */
        }
        Curl_cookie_freelist(store); /* free the cookie list */
      }
      if(addcookies && (CURLE_OK == result)) {
        if(!count)
          result = add_bufferf(req_buffer, "Cookie: ");
        if(CURLE_OK == result) {
          result = add_bufferf(req_buffer, "%s%s",
                               count?"; ":"",
                               addcookies);
          count++;
        }
      }
      if(count && (CURLE_OK == result))
        result = add_buffer(req_buffer, "\r\n", 2);

      if(result)
        return result;
    }
#endif

    if(data->set.timecondition) {
      struct tm *tm;

      /* Phil Karn (Fri, 13 Apr 2001) pointed out that the If-Modified-Since
       * header family should have their times set in GMT as RFC2616 defines:
       * "All HTTP date/time stamps MUST be represented in Greenwich Mean Time
       * (GMT), without exception. For the purposes of HTTP, GMT is exactly
       * equal to UTC (Coordinated Universal Time)." (see page 20 of RFC2616).
       */

#ifdef HAVE_GMTIME_R
      /* thread-safe version */
      struct tm keeptime;
      tm = (struct tm *)gmtime_r(&data->set.timevalue, &keeptime);
#else
      tm = gmtime(&data->set.timevalue);
#endif

      /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
      snprintf(buf, BUFSIZE-1,
               "%s, %02d %s %4d %02d:%02d:%02d GMT",
               Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
               tm->tm_mday,
               Curl_month[tm->tm_mon],
               tm->tm_year + 1900,
               tm->tm_hour,
               tm->tm_min,
               tm->tm_sec);

      switch(data->set.timecondition) {
      case CURL_TIMECOND_IFMODSINCE:
      default:
        result = add_bufferf(req_buffer,
                             "If-Modified-Since: %s\r\n", buf);
        break;
      case CURL_TIMECOND_IFUNMODSINCE:
        result = add_bufferf(req_buffer,
                             "If-Unmodified-Since: %s\r\n", buf);
        break;
      case CURL_TIMECOND_LASTMOD:
        result = add_bufferf(req_buffer,
                             "Last-Modified: %s\r\n", buf);
        break;
      }
      if(result)
        return result;
    }

    result = add_custom_headers(conn, req_buffer);
    if(result)
      return result;

    http->postdata = NULL;  /* nothing to post at this point */
    Curl_pgrsSetUploadSize(data, 0); /* upload size is 0 atm */

    /* If 'authdone' is FALSE, we must not set the write socket index to the
       Curl_transfer() call below, as we're not ready to actually upload any
       data yet. */

    switch(httpreq) {

    case HTTPREQ_POST_FORM:
      if(!http->sendit || conn->bits.authneg) {
        /* nothing to post! */
        result = add_bufferf(req_buffer, "Content-Length: 0\r\n\r\n");
        if(result)
          return result;

        result = add_buffer_send(req_buffer, conn,
                                 &data->info.request_size, 0, FIRSTSOCKET);
        if(result)
          failf(data, "Failed sending POST request");
        else
          /* setup variables for the upcoming transfer */
          result = Curl_setup_transfer(conn, FIRSTSOCKET, -1, TRUE,
                                       &http->readbytecount,
                                       -1, NULL);
        break;
      }

      if(Curl_FormInit(&http->form, http->sendit)) {
        failf(data, "Internal HTTP POST error!");
        return CURLE_HTTP_POST_ERROR;
      }

      /* set the read function to read from the generated form data */
      conn->fread = (curl_read_callback)Curl_FormReader;
      conn->fread_in = &http->form;

      http->sending = HTTPSEND_BODY;

      if(!conn->bits.upload_chunky) {
        /* only add Content-Length if not uploading chunked */
        result = add_bufferf(req_buffer,
                             "Content-Length: %" FORMAT_OFF_T "\r\n",
                             http->postsize);
        if(result)
          return result;
      }

      result = expect100(data, req_buffer);
      if(result)
        return result;

      {

        /* Get Content-Type: line from Curl_formpostheader.
        */
        char *contentType;
        size_t linelength=0;
        contentType = Curl_formpostheader((void *)&http->form,
                                          &linelength);
        if(!contentType) {
          failf(data, "Could not get Content-Type header line!");
          return CURLE_HTTP_POST_ERROR;
        }

        result = add_buffer(req_buffer, contentType, linelength);
        if(result)
          return result;
      }

      /* make the request end in a true CRLF */
      result = add_buffer(req_buffer, "\r\n", 2);
      if(result)
        return result;

      /* set upload size to the progress meter */
      Curl_pgrsSetUploadSize(data, http->postsize);

      /* fire away the whole request to the server */
      result = add_buffer_send(req_buffer, conn,
                               &data->info.request_size, 0, FIRSTSOCKET);
      if(result)
        failf(data, "Failed sending POST request");
      else
        /* setup variables for the upcoming transfer */
        result = Curl_setup_transfer(conn, FIRSTSOCKET, -1, TRUE,
                                     &http->readbytecount,
                                     FIRSTSOCKET,
                                     &http->writebytecount);

      if(result) {
        Curl_formclean(&http->sendit); /* free that whole lot */
        return result;
      }
#ifdef CURL_DOES_CONVERSIONS
/* time to convert the form data... */
      result = Curl_formconvert(data, http->sendit);
      if(result) {
        Curl_formclean(&http->sendit); /* free that whole lot */
        return result;
      }
#endif /* CURL_DOES_CONVERSIONS */
      break;

    case HTTPREQ_PUT: /* Let's PUT the data to the server! */

      if(conn->bits.authneg)
        postsize = 0;
      else
        postsize = data->set.infilesize;

      if((postsize != -1) && !conn->bits.upload_chunky) {
        /* only add Content-Length if not uploading chunked */
        result = add_bufferf(req_buffer,
                             "Content-Length: %" FORMAT_OFF_T "\r\n",
                             postsize );
        if(result)
          return result;
      }

      result = expect100(data, req_buffer);
      if(result)
        return result;

      result = add_buffer(req_buffer, "\r\n", 2); /* end of headers */
      if(result)
        return result;

      /* set the upload size to the progress meter */
      Curl_pgrsSetUploadSize(data, postsize);

      /* this sends the buffer and frees all the buffer resources */
      result = add_buffer_send(req_buffer, conn,
                               &data->info.request_size, 0, FIRSTSOCKET);
      if(result)
        failf(data, "Failed sending PUT request");
      else
        /* prepare for transfer */
        result = Curl_setup_transfer(conn, FIRSTSOCKET, -1, TRUE,
                                     &http->readbytecount,
                                     postsize?FIRSTSOCKET:-1,
                                     postsize?&http->writebytecount:NULL);
      if(result)
        return result;
      break;

    case HTTPREQ_POST:
      /* this is the simple POST, using x-www-form-urlencoded style */

      if(conn->bits.authneg)
        postsize = 0;
      else
        /* figure out the size of the postfields */
        postsize = (data->set.postfieldsize != -1)?
          data->set.postfieldsize:
          (data->set.postfields?(curl_off_t)strlen(data->set.postfields):0);

      if(!conn->bits.upload_chunky) {
        /* We only set Content-Length and allow a custom Content-Length if
           we don't upload data chunked, as RFC2616 forbids us to set both
           kinds of headers (Transfer-Encoding: chunked and Content-Length) */

        if(!checkheaders(data, "Content-Length:")) {
          /* we allow replacing this header, although it isn't very wise to
             actually set your own */
          result = add_bufferf(req_buffer,
                               "Content-Length: %" FORMAT_OFF_T"\r\n",
                               postsize);
          if(result)
            return result;
        }
      }

      if(!checkheaders(data, "Content-Type:")) {
        result = add_bufferf(req_buffer,
                             "Content-Type: application/x-www-form-urlencoded\r\n");
        if(result)
          return result;
      }

      if(data->set.postfields) {

        /* for really small posts we don't use Expect: headers at all, and for
           the somewhat bigger ones we allow the app to disable it */
        if(postsize > TINY_INITIAL_POST_SIZE) {
          result = expect100(data, req_buffer);
          if(result)
            return result;
        }
        else
          data->state.expect100header = FALSE;

        if(!data->state.expect100header &&
           (postsize < MAX_INITIAL_POST_SIZE))  {
          /* if we don't use expect:-100  AND
             postsize is less than MAX_INITIAL_POST_SIZE

             then append the post data to the HTTP request header. This limit
             is no magic limit but only set to prevent really huge POSTs to
             get the data duplicated with malloc() and family. */

          result = add_buffer(req_buffer, "\r\n", 2); /* end of headers! */
          if(result)
            return result;

          if(!conn->bits.upload_chunky) {
            /* We're not sending it 'chunked', append it to the request
               already now to reduce the number if send() calls */
            result = add_buffer(req_buffer, data->set.postfields,
                                (size_t)postsize);
            included_body = postsize;
          }
          else {
            /* Append the POST data chunky-style */
            result = add_bufferf(req_buffer, "%x\r\n", (int)postsize);
            if(CURLE_OK == result)
              result = add_buffer(req_buffer, data->set.postfields,
                                  (size_t)postsize);
            if(CURLE_OK == result)
              result = add_buffer(req_buffer,
                                  "\x0d\x0a\x30\x0d\x0a\x0d\x0a", 7);
                                  /* CR  LF   0  CR  LF  CR  LF */
            included_body = postsize + 7;
          }
          if(result)
            return result;
        }
        else {
          /* A huge POST coming up, do data separate from the request */
          http->postsize = postsize;
          http->postdata = data->set.postfields;

          http->sending = HTTPSEND_BODY;

          conn->fread = (curl_read_callback)readmoredata;
          conn->fread_in = (void *)conn;

          /* set the upload size to the progress meter */
          Curl_pgrsSetUploadSize(data, http->postsize);

          add_buffer(req_buffer, "\r\n", 2); /* end of headers! */
        }
      }
      else {
        add_buffer(req_buffer, "\r\n", 2); /* end of headers! */

        if(data->set.postfieldsize) {
          /* set the upload size to the progress meter */
          Curl_pgrsSetUploadSize(data, postsize?postsize:-1);

          /* set the pointer to mark that we will send the post body using
             the read callback */
          http->postdata = (char *)&http->postdata;
        }
      }
      /* issue the request */
      result = add_buffer_send(req_buffer, conn, &data->info.request_size,
                               (size_t)included_body, FIRSTSOCKET);

      if(result)
        failf(data, "Failed sending HTTP POST request");
      else
        result =
          Curl_setup_transfer(conn, FIRSTSOCKET, -1, TRUE,
                        &http->readbytecount,
                        http->postdata?FIRSTSOCKET:-1,
                        http->postdata?&http->writebytecount:NULL);
      break;

    default:
      add_buffer(req_buffer, "\r\n", 2);

      /* issue the request */
      result = add_buffer_send(req_buffer, conn,
                               &data->info.request_size, 0, FIRSTSOCKET);

      if(result)
        failf(data, "Failed sending HTTP request");
      else
        /* HTTP GET/HEAD download: */
        result = Curl_setup_transfer(conn, FIRSTSOCKET, -1, TRUE,
                               &http->readbytecount,
                               http->postdata?FIRSTSOCKET:-1,
                               http->postdata?&http->writebytecount:NULL);
    }
    if(result)
      return result;
  }

  return CURLE_OK;
}