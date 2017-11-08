CURL *curl_easy_duphandle(CURL *incurl)
{
  bool fail = TRUE;
  struct SessionHandle *data=(struct SessionHandle *)incurl;

  struct SessionHandle *outcurl = (struct SessionHandle *)
    calloc(sizeof(struct SessionHandle), 1);

  if(NULL == outcurl)
    return NULL; /* failure */

  do {

    /*
     * We setup a few buffers we need. We should probably make them
     * get setup on-demand in the code, as that would probably decrease
     * the likeliness of us forgetting to init a buffer here in the future.
     */
    outcurl->state.headerbuff=(char*)malloc(HEADERSIZE);
    if(!outcurl->state.headerbuff) {
      break;
    }
    outcurl->state.headersize=HEADERSIZE;

    /* copy all userdefined values */
    outcurl->set = data->set;
    outcurl->state.numconnects = data->state.numconnects;
    outcurl->state.connects = (struct connectdata **)
      malloc(sizeof(struct connectdata *) * outcurl->state.numconnects);

    if(!outcurl->state.connects) {
      break;
    }

    memset(outcurl->state.connects, 0,
           sizeof(struct connectdata *)*outcurl->state.numconnects);

    outcurl->progress.flags    = data->progress.flags;
    outcurl->progress.callback = data->progress.callback;

#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
    if(data->cookies) {
      /* If cookies are enabled in the parent handle, we enable them
         in the clone as well! */
      outcurl->cookies = Curl_cookie_init(data,
                                            data->cookies->filename,
                                            outcurl->cookies,
                                            data->set.cookiesession);
      if(!outcurl->cookies) {
        break;
      }
    }
#endif   /* CURL_DISABLE_HTTP */

    /* duplicate all values in 'change' */
    if(data->change.url) {
      outcurl->change.url = strdup(data->change.url);
      if(!outcurl->change.url)
        break;
      outcurl->change.url_alloc = TRUE;
    }
    if(data->change.proxy) {
      outcurl->change.proxy = strdup(data->change.proxy);
      if(!outcurl->change.proxy)
        break;
      outcurl->change.proxy_alloc = TRUE;
    }
    if(data->change.referer) {
      outcurl->change.referer = strdup(data->change.referer);
      if(!outcurl->change.referer)
        break;
      outcurl->change.referer_alloc = TRUE;
    }

#ifdef USE_ARES
    /* If we use ares, we setup a new ares channel for the new handle */
    if(ARES_SUCCESS != ares_init(&outcurl->state.areschannel))
      break;
#endif

    fail = FALSE; /* we reach this point and thus we are OK */

  } while(0);

  if(fail) {
    if(outcurl) {
      if(outcurl->state.connects)
        free(outcurl->state.connects);
      if(outcurl->state.headerbuff)
        free(outcurl->state.headerbuff);
      if(outcurl->change.proxy)
        free(outcurl->change.proxy);
      if(outcurl->change.url)
        free(outcurl->change.url);
      if(outcurl->change.referer)
        free(outcurl->change.referer);
      free(outcurl); /* free the memory again */
      outcurl = NULL;
    }
  }

  return outcurl;
}