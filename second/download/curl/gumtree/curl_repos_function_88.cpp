CURLcode http(struct connectdata *conn)
{
  struct UrlData *data=conn->data;
  char *buf = data->buffer; /* this is a short cut to the buffer */
  CURLcode result=CURLE_OK;
  struct HTTP *http;
  struct Cookie *co=NULL; /* no cookies from start */
  char *ppath = conn->ppath; /* three previous function arguments */
  char *host = conn->name;
  long *bytecount = &conn->bytecount;

  http = (struct HTTP *)malloc(sizeof(struct HTTP));
  if(!http)
    return CURLE_OUT_OF_MEMORY;
  memset(http, 0, sizeof(struct HTTP));
  data->proto.http = http;

  if ( (conn->protocol&(PROT_HTTP|PROT_FTP)) &&
       data->bits.upload) {
    data->bits.http_put=1;
  }
  
  /* The User-Agent string has been built in url.c already, because it might
     have been used in the proxy connect, but if we have got a header with
     the user-agent string specified, we erase the previously made string
     here. */
  if(checkheaders(data, "User-Agent:") && data->ptr_uagent) {
    free(data->ptr_uagent);
    data->ptr_uagent=NULL;
  }

  if((data->bits.user_passwd) && !checkheaders(data, "Authorization:")) {
    char authorization[512];

    /* To prevent the user+password to get sent to other than the original
       host due to a location-follow, we do some weirdo checks here */
    if(!data->bits.this_is_a_follow ||
       !data->auth_host ||
       strequal(data->auth_host, data->hostname)) {
      sprintf(data->buffer, "%s:%s", data->user, data->passwd);
      base64Encode(data->buffer, authorization);
      data->ptr_userpwd = maprintf( "Authorization: Basic %s\015\012",
                                    authorization);
    }
  }
  if((data->bits.set_range) && !checkheaders(data, "Range:")) {
    data->ptr_rangeline = maprintf("Range: bytes=%s\015\012", data->range);
  }
  if((data->bits.http_set_referer) && !checkheaders(data, "Referer:")) {
    data->ptr_ref = maprintf("Referer: %s\015\012", data->referer);
  }
  if(data->cookie && !checkheaders(data, "Cookie:")) {
    data->ptr_cookie = maprintf("Cookie: %s\015\012", data->cookie);
  }

  if(data->cookies) {
    co = cookie_getlist(data->cookies,
                        host,
                        ppath,
                        conn->protocol&PROT_HTTPS?TRUE:FALSE);
  }
  if ((data->bits.httpproxy) && !(conn->protocol&PROT_HTTPS))  {
    /* The path sent to the proxy is in fact the entire URL */
    strncpy(ppath, data->url, URL_MAX_LENGTH-1);
  }
  if(data->bits.http_formpost) {
    /* we must build the whole darned post sequence first, so that we have
       a size of the whole shebang before we start to send it */
    http->sendit = getFormData(data->httppost, &http->postsize);
  }

  if(!checkheaders(data, "Host:")) {
    data->ptr_host = maprintf("Host: %s:%d\r\n", host, data->remote_port);
  }

  if(!checkheaders(data, "Pragma:"))
    http->p_pragma = "Pragma: no-cache\r\n";

  if(!checkheaders(data, "Accept:"))
    http->p_accept = "Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, */*\r\n";

  do {
    struct curl_slist *headers=data->headers;
    sendf(data->firstsocket, data,
          "%s " /* GET/HEAD/POST/PUT */
          "%s HTTP/1.0\r\n" /* path */
          "%s" /* proxyuserpwd */
          "%s" /* userpwd */
          "%s" /* range */
          "%s" /* user agent */
          "%s" /* cookie */
          "%s" /* host */
          "%s" /* pragma */
          "%s" /* accept */
          "%s", /* referer */

          data->customrequest?data->customrequest:
          (data->bits.no_body?"HEAD":
           (data->bits.http_post || data->bits.http_formpost)?"POST":
           (data->bits.http_put)?"PUT":"GET"),
          ppath,
          (data->bits.proxy_user_passwd && data->ptr_proxyuserpwd)?data->ptr_proxyuserpwd:"",
          (data->bits.user_passwd && data->ptr_userpwd)?data->ptr_userpwd:"",
          (data->bits.set_range && data->ptr_rangeline)?data->ptr_rangeline:"",
          (data->useragent && *data->useragent && data->ptr_uagent)?data->ptr_uagent:"",
          (data->ptr_cookie?data->ptr_cookie:""), /* Cookie: <data> */
          (data->ptr_host?data->ptr_host:""), /* Host: host */
          http->p_pragma?http->p_pragma:"",
          http->p_accept?http->p_accept:"",
          (data->bits.http_set_referer && data->ptr_ref)?data->ptr_ref:"" /* Referer: <data> <CRLF> */
          );

    if(co) {
      int count=0;
      /* now loop through all cookies that matched */
      while(co) {
        if(co->value && strlen(co->value)) {
          if(0 == count) {
            sendf(data->firstsocket, data,
                  "Cookie:");
          }
          sendf(data->firstsocket, data,
                "%s%s=%s", count?"; ":"", co->name,
                co->value);
          count++;
        }
        co = co->next; /* next cookie please */
      }
      if(count) {
        sendf(data->firstsocket, data,
              "\r\n");
      }
      cookie_freelist(co); /* free the cookie list */
      co=NULL;
    }

    if(data->timecondition) {
      struct tm *thistime;

#ifdef HAVE_LOCALTIME_R
      /* thread-safe version */
      struct tm keeptime;
      thistime = localtime_r(&data->timevalue, &keeptime);
#else
      thistime = localtime(&data->timevalue);
#endif
      if(NULL == thistime) {
        failf(data, "localtime() failed!");
        return CURLE_OUT_OF_MEMORY;
      }

#ifdef HAVE_STRFTIME
      /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
      strftime(buf, BUFSIZE-1, "%a, %d %b %Y %H:%M:%S %Z", thistime);
#else
      /* TODO: Right, we *could* write a replacement here */
      strcpy(buf, "no strftime() support");
#endif
      switch(data->timecondition) {
      case TIMECOND_IFMODSINCE:
      default:
        sendf(data->firstsocket, data,
              "If-Modified-Since: %s\r\n", buf);
        break;
      case TIMECOND_IFUNMODSINCE:
        sendf(data->firstsocket, data,
              "If-Unmodified-Since: %s\r\n", buf);
        break;
      case TIMECOND_LASTMOD:
        sendf(data->firstsocket, data,
              "Last-Modified: %s\r\n", buf);
        break;
      }
    }

    while(headers) {
      char *ptr = strchr(headers->data, ':');
      if(ptr) {
        /* we require a colon for this to be a true header */

        ptr++; /* pass the colon */
        while(*ptr && isspace(*ptr))
          ptr++;

        if(*ptr) {
          /* only send this if the contents was non-blank */

          sendf(data->firstsocket, data,
                "%s\015\012",
                headers->data);
        }
      }
      headers = headers->next;
    }

    if(data->bits.http_formpost) {
      if(FormInit(&http->form, http->sendit)) {
        failf(data, "Internal HTTP POST error!\n");
        return CURLE_HTTP_POST_ERROR;
      }

      http->storefread = data->fread; /* backup */
      http->in = data->in; /* backup */
          
      data->fread =
        (size_t (*)(char *, size_t, size_t, FILE *))
        FormReader; /* set the read function to read from the
                       generated form data */
      data->in = (FILE *)&http->form;

      sendf(data->firstsocket, data,
            "Content-Length: %d\r\n",
            http->postsize-2);

      pgrsSetUploadSize(data, http->postsize);

      result = Transfer(conn, data->firstsocket, -1, TRUE,
                        &http->readbytecount,
                          data->firstsocket,
                        &http->writebytecount);
      if(result) {
        FormFree(http->sendit); /* free that whole lot */
        return result;
      }
    }
    else if(data->bits.http_put) {
      /* Let's PUT the data to the server! */

      if(data->infilesize>0) {
        sendf(data->firstsocket, data,
              "Content-Length: %d\r\n\r\n", /* file size */
              data->infilesize );
      }
      else
        sendf(data->firstsocket, data,
              "\015\012");

      pgrsSetUploadSize(data, data->infilesize);

      result = Transfer(conn, data->firstsocket, -1, TRUE,
                        &http->readbytecount,
                        data->firstsocket,
                        &http->writebytecount);
      if(result)
        return result;
      
    }
    else {
      if(data->bits.http_post) {
        /* this is the simple POST, using x-www-form-urlencoded style */

        if(!checkheaders(data, "Content-Length:"))
          /* we allow replacing this header, although it isn't very wise to
             actually set your own */
          sendf(data->firstsocket, data,
                "Content-Length: %d\r\n",
                strlen(data->postfields));

        if(!checkheaders(data, "Content-Type:"))
          sendf(data->firstsocket, data,
                "Content-Type: application/x-www-form-urlencoded\r\n");

        /* and here comes the actual data */
        sendf(data->firstsocket, data,
              "\r\n"
              "%s\r\n",
              data->postfields );
      }
      else
        sendf(data->firstsocket, data, "\r\n");

      /* HTTP GET/HEAD download: */
      result = Transfer(conn, data->firstsocket, -1, TRUE, bytecount,
                        -1, NULL); /* nothing to upload */
    }
    if(result)
      return result;
  } while (0); /* this is just a left-over from the multiple document download
                  attempts */

  return CURLE_OK;
}