CURLcode Curl_follow(struct SessionHandle *data,
                     char *newurl, /* this 'newurl' is the Location: string,
                                      and it must be malloc()ed before passed
                                      here */
                     followtype type) /* see transfer.h */
{
#ifdef CURL_DISABLE_HTTP
  (void)data;
  (void)newurl;
  (void)type;
  /* Location: following will not happen when HTTP is disabled */
  return CURLE_TOO_MANY_REDIRECTS;
#else

  /* Location: redirect */
  bool disallowport = FALSE;

  if(type == FOLLOW_REDIR) {
    if((data->set.maxredirs != -1) &&
        (data->set.followlocation >= data->set.maxredirs)) {
      failf(data,"Maximum (%ld) redirects followed", data->set.maxredirs);
      return CURLE_TOO_MANY_REDIRECTS;
    }

    /* mark the next request as a followed location: */
    data->state.this_is_a_follow = TRUE;

    data->set.followlocation++; /* count location-followers */

    if(data->set.http_auto_referer) {
      /* We are asked to automatically set the previous URL as the referer
         when we get the next URL. We pick the ->url field, which may or may
         not be 100% correct */

      if(data->change.referer_alloc) {
        Curl_safefree(data->change.referer);
        data->change.referer_alloc = FALSE;
      }

      data->change.referer = strdup(data->change.url);
      if(!data->change.referer)
        return CURLE_OUT_OF_MEMORY;
      data->change.referer_alloc = TRUE; /* yes, free this later */
    }
  }

  if(!is_absolute_url(newurl))  {
    /***
     *DANG* this is an RFC 2068 violation. The URL is supposed
     to be absolute and this doesn't seem to be that!
     */
    char *absolute = concat_url(data->change.url, newurl);
    if(!absolute)
      return CURLE_OUT_OF_MEMORY;
    free(newurl);
    newurl = absolute;
  }
  else {
    /* This is an absolute URL, don't allow the custom port number */
    disallowport = TRUE;

    if(strchr(newurl, ' ')) {
      /* This new URL contains at least one space, this is a mighty stupid
         redirect but we still make an effort to do "right". */
      char *newest;
      size_t newlen = strlen_url(newurl);

      newest = malloc(newlen+1); /* get memory for this */
      if(!newest)
        return CURLE_OUT_OF_MEMORY;
      strcpy_url(newest, newurl); /* create a space-free URL */

      free(newurl); /* that was no good */
      newurl = newest; /* use this instead now */
    }

  }

  if(type == FOLLOW_FAKE) {
    /* we're only figuring out the new url if we would've followed locations
       but now we're done so we can get out! */
    data->info.wouldredirect = newurl;
    return CURLE_OK;
  }

  if(disallowport)
    data->state.allow_port = FALSE;

  if(data->change.url_alloc) {
    Curl_safefree(data->change.url);
    data->change.url_alloc = FALSE;
  }

  data->change.url = newurl;
  data->change.url_alloc = TRUE;
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
    /* 401 - Act on a WWW-Authenticate, we keep on moving and do the
       Authorization: XXXX header in the HTTP request code snippet */
    /* 407 - Act on a Proxy-Authenticate, we keep on moving and do the
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
     * When automatically redirecting a POST request after receiving a 301
     * status code, some existing HTTP/1.0 user agents will erroneously change
     * it into a GET request.
     *
     * ----
     *
     * As most of the important user agents do this obvious RFC2616 violation,
     * many webservers expect this. So these servers often answers to a POST
     * request with an error page.  To be sure that libcurl gets the page that
     * most user agents would get, libcurl has to force GET.
     *
     * This behavior can be overridden with CURLOPT_POSTREDIR.
     */
    if((data->set.httpreq == HTTPREQ_POST
        || data->set.httpreq == HTTPREQ_POST_FORM)
       && !(data->set.keep_post & CURL_REDIR_POST_301)) {
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

    This behavior can be overridden with CURLOPT_POSTREDIR
    */
    if((data->set.httpreq == HTTPREQ_POST
        || data->set.httpreq == HTTPREQ_POST_FORM)
       && !(data->set.keep_post & CURL_REDIR_POST_302)) {
      infof(data,
            "Violate RFC 2616/10.3.3 and switch from POST to GET\n");
      data->set.httpreq = HTTPREQ_GET;
    }
    break;

  case 303: /* See Other */
    /* Disable both types of POSTs, unless the user explicitely
       asks for POST after POST */
    if(data->set.httpreq != HTTPREQ_GET
      && !(data->set.keep_post & CURL_REDIR_POST_303)) {
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
  Curl_pgrsResetTimesSizes(data);

  return CURLE_OK;
#endif /* CURL_DISABLE_HTTP */
}