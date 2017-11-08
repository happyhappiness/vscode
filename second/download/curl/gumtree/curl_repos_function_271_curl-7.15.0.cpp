CURLcode Curl_pretransfer(struct SessionHandle *data)
{
  CURLcode res;
  if(!data->change.url) {
    /* we can't do anything wihout URL */
    failf(data, "No URL set!\n");
    return CURLE_URL_MALFORMAT;
  }

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

  /* If there is a list of cookie files to read, do it now! */
  if(data->change.cookielist)
    Curl_cookie_loadfiles(data);

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