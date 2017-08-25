{
  struct SessionHandle *data=conn->data;
  char *buf = data->state.buffer; /* this is a short cut to the buffer */
  CURLcode result;
  struct HTTP *http;
  char *ppath = conn->path;
  char *host = conn->host.name;
  const char *te = ""; /* tranfer-encoding */
  char *ptr;
  char *request;
  Curl_HttpReq httpreq = data->set.httpreq;
  char *addcookies = NULL;

  if(!conn->proto.http) {
    /* Only allocate this struct if we don't already have it! */

    http = (struct HTTP *)malloc(sizeof(struct HTTP));
    if(!http)
      return CURLE_OUT_OF_MEMORY;
    memset(http, 0, sizeof(struct HTTP));
    conn->proto.http = http;
  }
  else
    http = conn->proto.http;

  /* We default to persistant connections */
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
      char *iPtr = strstr(url, conn->host.dispname);
      if(iPtr) {
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
          memcpy(newurl, url, iPtr - url);
          /* append the new host name instead of the old */
          memcpy(newurl + (iPtr - url), conn->host.name, newlen);
          /* append the piece after the host name */
          memcpy(newurl + newlen + (iPtr - url),
                 iPtr + currlen, /* copy the trailing zero byte too */
                 urllen - (iPtr-url) - currlen + 1);
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
                               &http->postsize);
     if(CURLE_OK != result) {
       /* Curl_getFormData() doesn't use failf() */
       failf(data, "failed creating formpost data");
       return result;
     }
  }


  if(!checkheaders(data, "Pragma:"))
    http->p_pragma = "Pragma: no-cache\r\n";

  if(!checkheaders(data, "Accept:"))
    http->p_accept = "Accept: */*\r\n";

  if(( (HTTPREQ_POST == httpreq) ||
       (HTTPREQ_POST_FORM == httpreq) ||
       (HTTPREQ_PUT == httpreq) ) &&
     conn->resume_from) {
    /**********************************************************************
     * Resuming upload in HTTP means that we PUT or POST and that we have
     * got a resume_from value set. The resume value has already created
     * a Range: header that will be passed along. We need to "fast forward"
     * the file the given number of bytes and decrease the assume upload
     * file size before we continue this venture in the dark lands of HTTP.
     *********************************************************************/

    if(conn->resume_from < 0 ) {
      /*
       * This is meant to get the size of the present remote-file by itself.
       * We don't support this now. Bail out!
       */
       conn->resume_from = 0;
    }

    if(conn->resume_from) {
      /* do we still game? */
      curl_off_t passed=0;

      /* Now, let's read off the proper amount of bytes from the
         input. If we knew it was a proper file we could've just
         fseek()ed but we only have a stream here */
      do {
        size_t readthisamountnow = (size_t)(conn->resume_from - passed);
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
      } while(passed != conn->resume_from); /* loop until done */

      /* now, decrease the size of the read */
      if(data->set.infilesize>0) {
        data->set.infilesize -= conn->resume_from;

        if(data->set.infilesize <= 0) {
          failf(data, "File already completely uploaded");
          return CURLE_PARTIAL_FILE;
        }
      }
      /* we've passed, proceed as normal */
    }
  }
  if(conn->bits.use_range) {
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
      conn->allocptr.rangeline = aprintf("Range: bytes=%s\r\n", conn->range);
    }
    else if((httpreq != HTTPREQ_GET) &&
            !checkheaders(data, "Content-Range:")) {

      if(conn->resume_from) {
        /* This is because "resume" was selected */
        curl_off_t total_expected_size=
          conn->resume_from + data->set.infilesize;
        conn->allocptr.rangeline =
            aprintf("Content-Range: bytes %s%" FORMAT_OFF_T
                    "/%" FORMAT_OFF_T "\r\n",
                    conn->range, total_expected_size-1,
                    total_expected_size);
      }
      else {
        /* Range was selected and then we just pass the incoming range and
           append total size */
        conn->allocptr.rangeline =
            aprintf("Content-Range: bytes %s/%" FORMAT_OFF_T "\r\n",
                    conn->range, data->set.infilesize);
      }
    }
  }

  {
    /* Use 1.1 unless the use specificly asked for 1.0 */
    const char *httpstring=
      data->set.httpversion==CURL_HTTP_VERSION_1_0?"1.0":"1.1";

    send_buffer *req_buffer;
    struct curl_slist *headers=data->set.headers;
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
                  "%s",/* transfer-encoding */

                request,
                ppath,
                httpstring,
                conn->allocptr.proxyuserpwd?
                conn->allocptr.proxyuserpwd:"",
                conn->allocptr.userpwd?conn->allocptr.userpwd:"",
                (conn->bits.use_range && conn->allocptr.rangeline)?
                conn->allocptr.rangeline:"",
                (data->set.useragent && *data->set.useragent && conn->allocptr.uagent)?
                conn->allocptr.uagent:"",
                (conn->allocptr.host?conn->allocptr.host:""), /* Host: host */
                http->p_pragma?http->p_pragma:"",
                http->p_accept?http->p_accept:"",
                (data->set.encoding && *data->set.encoding && conn->allocptr.accept_encoding)?
                conn->allocptr.accept_encoding:"",
                (data->change.referer && conn->allocptr.ref)?conn->allocptr.ref:"" /* Referer: <data> */,
                te
                );

    if(result)
      return result;

    if(data->cookies || addcookies) {
      struct Cookie *co=NULL; /* no cookies from start */
      int count=0;

      if(data->cookies) {
        Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
        co = Curl_cookie_getlist(data->cookies,
                                 conn->allocptr.cookiehost?
                                 conn->allocptr.cookiehost:host, ppath,
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

    if(data->set.timecondition) {
      struct tm *thistime;

      /* Phil Karn (Fri, 13 Apr 2001) pointed out that the If-Modified-Since
       * header family should have their times set in GMT as RFC2616 defines:
       * "All HTTP date/time stamps MUST be represented in Greenwich Mean Time
       * (GMT), without exception. For the purposes of HTTP, GMT is exactly
       * equal to UTC (Coordinated Universal Time)." (see page 20 of RFC2616).
       */

#ifdef HAVE_GMTIME_R
      /* thread-safe version */
      struct tm keeptime;
      thistime = (struct tm *)gmtime_r(&data->set.timevalue, &keeptime);
#else
      thistime = gmtime(&data->set.timevalue);
#endif

#ifdef HAVE_STRFTIME
      /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
      strftime(buf, BUFSIZE-1, "%a, %d %b %Y %H:%M:%S GMT", thistime);
#else
      /* TODO: Right, we *could* write a replacement here */
      strcpy(buf, "no strftime() support");
#endif
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

    while(headers) {
      ptr = strchr(headers->data, ':');
      if(ptr) {
        /* we require a colon for this to be a true header */

        ptr++; /* pass the colon */
        while(*ptr && isspace((int)*ptr))
          ptr++;

        if(*ptr) {
          /* only send this if the contents was non-blank */

          result = add_bufferf(req_buffer, "%s\r\n", headers->data);
          if(result)
            return result;
        }
      }
      headers = headers->next;
    }

    http->postdata = NULL;  /* nothing to post at this point */
    Curl_pgrsSetUploadSize(data, 0); /* upload size is 0 atm */

    /* If 'authdone' is FALSE, we must not set the write socket index to the
       Curl_transfer() call below, as we're not ready to actually upload any
       data yet. */

    switch(httpreq) {

    case HTTPREQ_POST_FORM:
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

      if(!checkheaders(data, "Expect:")) {
        /* if not disabled explicitly we add a Expect: 100-continue
           to the headers which actually speeds up post operations (as
           there is one packet coming back from the web server) */
        result = add_bufferf(req_buffer,
                             "Expect: 100-continue\r\n");
        if(result)
          return result;
        data->set.expect100header = TRUE;
      }

      if(!checkheaders(data, "Content-Type:")) {
        /* Get Content-Type: line from Curl_formpostheader.

           The Content-Type header line also contains the MIME boundary
           string etc why disabling this header is likely to not make things
           work, but we support disabling it anyway.
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
                               &data->info.request_size);
      if(result)
        failf(data, "Failed sending POST request");
      else
        /* setup variables for the upcoming transfer */
        result = Curl_Transfer(conn, FIRSTSOCKET, -1, TRUE,
                               &http->readbytecount,
                               FIRSTSOCKET,
                               &http->writebytecount);
      if(result) {
        Curl_formclean(http->sendit); /* free that whole lot */
        return result;
      }
      break;

    case HTTPREQ_PUT: /* Let's PUT the data to the server! */

      if((data->set.infilesize>0) && !conn->bits.upload_chunky) {
        /* only add Content-Length if not uploading chunked */
        result = add_bufferf(req_buffer,
                             "Content-Length: %" FORMAT_OFF_T "\r\n", /* size */
                             data->set.infilesize );
        if(result)
          return result;
      }

      if(!checkheaders(data, "Expect:")) {
        /* if not disabled explicitly we add a Expect: 100-continue
           to the headers which actually speeds up post operations (as
           there is one packet coming back from the web server) */
        result = add_bufferf(req_buffer,
                             "Expect: 100-continue\r\n");
        if(result)
          return result;
        data->set.expect100header = TRUE;
      }

      result = add_buffer(req_buffer, "\r\n", 2); /* end of headers */
      if(result)
        return result;

      /* set the upload size to the progress meter */
      Curl_pgrsSetUploadSize(data, data->set.infilesize);

      /* this sends the buffer and frees all the buffer resources */
      result = add_buffer_send(req_buffer, conn,
                               &data->info.request_size);
      if(result)
        failf(data, "Failed sending POST request");
      else
        /* prepare for transfer */
        result = Curl_Transfer(conn, FIRSTSOCKET, -1, TRUE,
                               &http->readbytecount,
                               FIRSTSOCKET,
                               &http->writebytecount);
      if(result)
        return result;
      break;

    case HTTPREQ_POST:
      /* this is the simple POST, using x-www-form-urlencoded style */

      /* store the size of the postfields */
      postsize = data->set.postfieldsize?
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

        if((data->state.authhost.done || data->state.authproxy.done )
           && (postsize < (100*1024))) {
          /* If we're not done with the authentication phase, we don't expect
             to actually send off any data yet. Hence, we delay the sending of
             the body until we receive that friendly 100-continue response */

          /* The post data is less than 100K, then append it to the header.
             This limit is no magic limit but only set to prevent really huge
             POSTs to get the data duplicated with malloc() and family. */

          result = add_buffer(req_buffer, "\r\n", 2); /* end of headers! */
          if(result)
            return result;

          if(!conn->bits.upload_chunky) {
            /* We're not sending it 'chunked', append it to the request
               already now to reduce the number if send() calls */
            result = add_buffer(req_buffer, data->set.postfields,
                                (size_t)postsize);
          }
          else {
            /* Append the POST data chunky-style */
            result = add_bufferf(req_buffer, "%x\r\n", (int)postsize);
            if(CURLE_OK == result)
              result = add_buffer(req_buffer, data->set.postfields,
                                  (size_t)postsize);
            if(CURLE_OK == result)
              result = add_buffer(req_buffer,
                                  "\r\n0\r\n\r\n", 7); /* end of a chunked
                                                          transfer stream */
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

          if(!checkheaders(data, "Expect:")) {
            /* if not disabled explicitly we add a Expect: 100-continue to the
               headers which actually speeds up post operations (as there is
               one packet coming back from the web server) */
            add_bufferf(req_buffer,
                        "Expect: 100-continue\r\n");
            data->set.expect100header = TRUE;
          }

          add_buffer(req_buffer, "\r\n", 2); /* end of headers! */
        }
      }
      else {
        add_buffer(req_buffer, "\r\n", 2); /* end of headers! */

        /* set the upload size to the progress meter */
        Curl_pgrsSetUploadSize(data, data->set.infilesize);

        /* set the pointer to mark that we will send the post body using
           the read callback */
        http->postdata = (char *)&http->postdata;
      }
      /* issue the request */
      result = add_buffer_send(req_buffer, conn,
                               &data->info.request_size);

      if(result)
        failf(data, "Failed sending HTTP POST request");
      else
        result =
          Curl_Transfer(conn, FIRSTSOCKET, -1, TRUE,
                        &http->readbytecount,
                        http->postdata?FIRSTSOCKET:-1,
                        http->postdata?&http->writebytecount:NULL);
      break;

    default:
      add_buffer(req_buffer, "\r\n", 2);

      /* issue the request */
      result = add_buffer_send(req_buffer, conn,
                               &data->info.request_size);

      if(result)
        failf(data, "Failed sending HTTP request");
      else
        /* HTTP GET/HEAD download: */
        result = Curl_Transfer(conn, FIRSTSOCKET, -1, TRUE,
                               &http->readbytecount,
                               http->postdata?FIRSTSOCKET:-1,
                               http->postdata?&http->writebytecount:NULL);
    }
    if(result)
      return result;
  }

  return CURLE_OK;
}