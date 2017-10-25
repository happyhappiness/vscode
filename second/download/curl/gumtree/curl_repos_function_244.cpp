CURLcode Curl_pretransfer(struct SessionHandle *data)
{
  CURLcode res;
  if(!data->change.url)
    /* we can't do anything wihout URL */
    return CURLE_URL_MALFORMAT;

  /* Init the SSL session ID cache here. We do it here since we want to do it
     after the *_setopt() calls (that could change the size of the cache) but
     before any transfer takes place. */
  res = Curl_ssl_initsessions(data, data->set.ssl.numsessions);
  if(res)
    return res;

  data->set.followlocation=0; /* reset the location-follow counter */
  data->state.this_is_a_follow = FALSE; /* reset this */
  data->state.errorbuf = FALSE; /* no error has occurred */

  data->state.authproblem = FALSE;
  data->state.authhost.want = data->set.httpauth;
  data->state.authproxy.want = data->set.proxyauth;

#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
  /* If there was a list of cookie files to read and we haven't done it before,
     do it now! */
  if(data->change.cookielist) {
    struct curl_slist *list = data->change.cookielist;
    Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
    while(list) {
      data->cookies = Curl_cookie_init(data,
                                       list->data,
                                       data->cookies,
                                       data->set.cookiesession);
      list = list->next;
    }
    Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
    curl_slist_free_all(data->change.cookielist); /* clean up list */
    data->change.cookielist = NULL; /* don't do this again! */
  }
#endif   /* CURL_DISABLE_HTTP */


 /* Allow data->set.use_port to set which port to use. This needs to be
  * disabled for example when we follow Location: headers to URLs using
  * different ports! */
  data->state.allow_port = TRUE;

#if defined(HAVE_SIGNAL) && defined(SIGPIPE) && !defined(HAVE_MSG_NOSIGNAL)
  /*************************************************************
   * Tell signal handler to ignore SIGPIPE
   *************************************************************/
  if(!data->set.no_signal)
    data->state.prev_signal = signal(SIGPIPE, SIG_IGN);
#endif

  Curl_initinfo(data); /* reset session-specific information "variables" */
  Curl_pgrsStartNow(data);

  return CURLE_OK;
}