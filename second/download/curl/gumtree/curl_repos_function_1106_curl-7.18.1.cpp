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
    if(Curl_dupset(outcurl, data) != CURLE_OK)
      break;

    if(data->state.used_interface == Curl_if_multi)
      outcurl->state.connc = data->state.connc;
    else
      outcurl->state.connc = Curl_mk_connc(CONNCACHE_PRIVATE, -1);

    if(!outcurl->state.connc)
      break;

    outcurl->state.lastconnect = -1;

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

#if defined(CURL_DOES_CONVERSIONS) && defined(HAVE_ICONV)
    outcurl->inbound_cd = iconv_open(CURL_ICONV_CODESET_OF_HOST,
                                     CURL_ICONV_CODESET_OF_NETWORK);
    outcurl->outbound_cd = iconv_open(CURL_ICONV_CODESET_OF_NETWORK,
                                      CURL_ICONV_CODESET_OF_HOST);
    outcurl->utf8_cd = iconv_open(CURL_ICONV_CODESET_OF_HOST,
                                  CURL_ICONV_CODESET_FOR_UTF8);
#endif

    Curl_easy_initHandleData(outcurl);

    outcurl->magic = CURLEASY_MAGIC_NUMBER;

    fail = FALSE; /* we reach this point and thus we are OK */

  } while(0);

  if(fail) {
    if(outcurl) {
      if(outcurl->state.connc &&
         (outcurl->state.connc->type == CONNCACHE_PRIVATE))
        Curl_rm_connc(outcurl->state.connc);
      if(outcurl->state.headerbuff)
        free(outcurl->state.headerbuff);
      if(outcurl->change.url)
        free(outcurl->change.url);
      if(outcurl->change.referer)
        free(outcurl->change.referer);
      Curl_freeset(outcurl);
      free(outcurl); /* free the memory again */
      outcurl = NULL;
    }
  }

  return outcurl;
}