CURLcode Curl_follow(struct SessionHandle *data,
                     char *newurl, /* this 'newurl' is the Location: string,
                                      and it must be malloc()ed before passed
                                      here */
                     bool retry) /* set TRUE if this is a request retry as
                                    opposed to a real redirect following */
{
  /* Location: redirect */
  char prot[16]; /* URL protocol string storage */
  char letter;   /* used for a silly sscanf */
  size_t newlen;
  char *newest;

  if (data->set.maxredirs &&
      (data->set.followlocation >= data->set.maxredirs)) {
    failf(data,"Maximum (%d) redirects followed", data->set.maxredirs);
    return CURLE_TOO_MANY_REDIRECTS;
  }

  if(!retry)
    /* mark the next request as a followed location: */
    data->state.this_is_a_follow = TRUE;

  data->set.followlocation++; /* count location-followers */

  if(data->set.http_auto_referer) {
    /* We are asked to automatically set the previous URL as the
       referer when we get the next URL. We pick the ->url field,
       which may or may not be 100% correct */

    if(data->change.referer_alloc)
      /* If we already have an allocated referer, free this first */
      free(data->change.referer);

    data->change.referer = strdup(data->change.url);
    data->change.referer_alloc = TRUE; /* yes, free this later */
  }

  if(2 != sscanf(newurl, "%15[^?&/:]://%c", prot, &letter)) {
    /***
     *DANG* this is an RFC 2068 violation. The URL is supposed
     to be absolute and this doesn't seem to be that!
     ***
     Instead, we have to TRY to append this new path to the old URL
     to the right of the host part. Oh crap, this is doomed to cause
     problems in the future...
    */
    char *protsep;
    char *pathsep;

    char *useurl = newurl;
    size_t urllen;

    /* we must make our own copy of the URL to play with, as it may
       point to read-only data */
    char *url_clone=strdup(data->change.url);

    if(!url_clone)
      return CURLE_OUT_OF_MEMORY; /* skip out of this NOW */

    /* protsep points to the start of the host name */
    protsep=strstr(url_clone, "//");
    if(!protsep)
      protsep=url_clone;
    else
      protsep+=2; /* pass the slashes */

    if('/' != newurl[0]) {
      int level=0;

      /* First we need to find out if there's a ?-letter in the URL,
         and cut it and the right-side of that off */
      pathsep = strrchr(protsep, '?');
      if(pathsep)
        *pathsep=0;

      /* we have a relative path to append to the last slash if
         there's one available */
      pathsep = strrchr(protsep, '/');
      if(pathsep)
        *pathsep=0;

      /* Check if there's any slash after the host name, and if so,
         remember that position instead */
      pathsep = strchr(protsep, '/');
      if(pathsep)
        protsep = pathsep+1;
      else
        protsep = NULL;

      /* now deal with one "./" or any amount of "../" in the newurl
         and act accordingly */

      if((useurl[0] == '.') && (useurl[1] == '/'))
        useurl+=2; /* just skip the "./" */

      while((useurl[0] == '.') &&
            (useurl[1] == '.') &&
            (useurl[2] == '/')) {
        level++;
        useurl+=3; /* pass the "../" */
      }

      if(protsep) {
        while(level--) {
          /* cut off one more level from the right of the original URL */
          pathsep = strrchr(protsep, '/');
          if(pathsep)
            *pathsep=0;
          else {
            *protsep=0;
            break;
          }
        }
      }
    }
    else {
      /* We got a new absolute path for this server, cut off from the
         first slash */
      pathsep = strchr(protsep, '/');
      if(pathsep) {
        /* When people use badly formatted URLs, such as
           "http://www.url.com?dir=/home/daniel" we must not use the first
           slash, if there's a ?-letter before it! */
        char *sep = strchr(protsep, '?');
        if(sep && (sep < pathsep))
          pathsep = sep;
        *pathsep=0;
      }
      else {
        /* There was no slash. Now, since we might be operating on a badly
           formatted URL, such as "http://www.url.com?id=2380" which doesn't
           use a slash separator as it is supposed to, we need to check for a
           ?-letter as well! */
        pathsep = strchr(protsep, '?');
        if(pathsep)
          *pathsep=0;
      }
    }

    /* If the new part contains a space, this is a mighty stupid redirect
       but we still make an effort to do "right". To the left of a '?'
       letter we replace each space with %20 while it is replaced with '+'
       on the right side of the '?' letter.
    */
    newlen = strlen_url(useurl);

    urllen = strlen(url_clone);

    newest=(char *)malloc( urllen + 1 + /* possible slash */
                           newlen + 1 /* zero byte */);

    if(!newest) {
      free(url_clone); /* don't leak this */
      return CURLE_OUT_OF_MEMORY; /* go out from this */
    }

    /* copy over the root url part */
    memcpy(newest, url_clone, urllen);

    /* check if we need to append a slash */
    if(('/' == useurl[0]) || (protsep && !*protsep))
      ;
    else
      newest[urllen++]='/';

    /* then append the new piece on the right side */
    strcpy_url(&newest[urllen], useurl);

    free(newurl); /* newurl is the allocated pointer */
    free(url_clone);
    newurl = newest;
  }
  else {
    /* This is an absolute URL, don't allow the custom port number */
    data->state.allow_port = FALSE;

    if(strchr(newurl, ' ')) {
      /* This new URL contains at least one space, this is a mighty stupid
         redirect but we still make an effort to do "right". */
      newlen = strlen_url(newurl);

      newest = malloc(newlen+1); /* get memory for this */
      if(newest) {
        strcpy_url(newest, newurl); /* create a space-free URL */

        free(newurl); /* that was no good */
        newurl = newest; /* use this instead now */
      }
    }

  }

  if(data->change.url_alloc)
    free(data->change.url);
  else
    data->change.url_alloc = TRUE; /* the URL is allocated */

  data->change.url = newurl;
  newurl = NULL; /* don't free! */

  infof(data, "Issue another request to this URL: '%s'\n", data->change.url);

  /*
   * We get here when the HTTP code is 300-399 (and 401). We need to perform
   * differently based on exactly what return code there was.
   *
   * News from 7.10.6: we can also get here on a 401 or 407, in case we act on
   * a HTTP (proxy-) authentication scheme other than Basic.
   */
  switch(data->info.httpcode) {
    /* 401 - Act on a www-authentication, we keep on moving and do the
       Authorization: XXXX header in the HTTP request code snippet */
    /* 407 - Act on a proxy-authentication, we keep on moving and do the
       Proxy-Authorization: XXXX header in the HTTP request code snippet */
    /* 300 - Multiple Choices */
    /* 306 - Not used */
    /* 307 - Temporary Redirect */
  default:  /* for all above (and the unknown ones) */
    /* Some codes are explicitly mentioned since I've checked RFC2616 and they
     * seem to be OK to POST to.
     */
    break;
  case 301: /* Moved Permanently */
    /* (quote from RFC2616, section 10.3.2):
     *
     * Note: When automatically redirecting a POST request after receiving a
     * 301 status code, some existing HTTP/1.0 user agents will erroneously
     * change it into a GET request.
     *
     * ----
     *
     * Warning: Because most of importants user agents do this obvious RFC2616
     * violation, many webservers expect this misbehavior. So these servers
     * often answers to a POST request with an error page.  To be sure that
     * libcurl gets the page that most user agents would get, libcurl has to
     * force GET:
     */
    if( data->set.httpreq == HTTPREQ_POST
        || data->set.httpreq == HTTPREQ_POST_FORM) {
      infof(data,
            "Violate RFC 2616/10.3.2 and switch from POST to GET\n");
      data->set.httpreq = HTTPREQ_GET;
    }
    break;
  case 302: /* Found */
    /* (From 10.3.3)

    Note: RFC 1945 and RFC 2068 specify that the client is not allowed
    to change the method on the redirected request.  However, most
    existing user agent implementations treat 302 as if it were a 303
    response, performing a GET on the Location field-value regardless
    of the original request method. The status codes 303 and 307 have
    been added for servers that wish to make unambiguously clear which
    kind of reaction is expected of the client.

    (From 10.3.4)

    Note: Many pre-HTTP/1.1 user agents do not understand the 303
    status. When interoperability with such clients is a concern, the
    302 status code may be used instead, since most user agents react
    to a 302 response as described here for 303.
    */
  case 303: /* See Other */
    /* Disable both types of POSTs, since doing a second POST when
     * following isn't what anyone would want! */
    if(data->set.httpreq != HTTPREQ_GET) {
      data->set.httpreq = HTTPREQ_GET; /* enforce GET request */
      infof(data, "Disables POST, goes with %s\n",
            data->set.opt_no_body?"HEAD":"GET");
    }
    break;
  case 304: /* Not Modified */
    /* 304 means we did a conditional request and it was "Not modified".
     * We shouldn't get any Location: header in this response!
     */
    break;
  case 305: /* Use Proxy */
    /* (quote from RFC2616, section 10.3.6):
     * "The requested resource MUST be accessed through the proxy given
     * by the Location field. The Location field gives the URI of the
     * proxy.  The recipient is expected to repeat this single request
     * via the proxy. 305 responses MUST only be generated by origin
     * servers."
     */
    break;
  }
  Curl_pgrsTime(data, TIMER_REDIRECT);
  Curl_pgrsResetTimes(data);

  return CURLE_OK;
}