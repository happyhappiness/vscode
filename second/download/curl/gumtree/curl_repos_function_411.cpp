CURLcode Curl_close(struct SessionHandle *data)
{
  if(data->multi) {
    /* this handle is still part of a multi handle, take care of this first */
    Curl_multi_rmeasy(data->multi, data);
  }
  /* Loop through all open connections and kill them one by one */
  while(-1 != ConnectionKillOne(data))
    ; /* empty loop */

  if ( ! (data->share && data->share->hostcache) ) {
    if ( !Curl_global_host_cache_use(data)) {
      Curl_hash_destroy(data->hostcache);
    }
  }

  /* Close down all open SSL info and sessions */
  Curl_ssl_close_all(data);
  Curl_safefree(data->state.first_host);
  Curl_safefree(data->state.scratch);

  if(data->change.proxy_alloc)
    free(data->change.proxy);

  if(data->change.referer_alloc)
    free(data->change.referer);

  if(data->change.url_alloc)
    free(data->change.url);

  Curl_safefree(data->state.headerbuff);

#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
  if(data->change.cookielist) /* clean up list if any */
    curl_slist_free_all(data->change.cookielist);

  Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
  if(data->set.cookiejar) {
    /* we have a "destination" for all the cookies to get dumped to */
    if(Curl_cookie_output(data->cookies, data->set.cookiejar))
      infof(data, "WARNING: failed to save cookies in %s\n",
            data->set.cookiejar);
  }

  if( !data->share || (data->cookies != data->share->cookies) ) {
    Curl_cookie_cleanup(data->cookies);
  }
  Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
#endif

#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_CRYPTO_AUTH)
  Curl_digest_cleanup(data);
#endif

  /* free the connection cache */
  free(data->state.connects);

  Curl_safefree(data->info.contenttype);

#ifdef USE_ARES
  /* this destroys the channel and we cannot use it anymore after this */
  ares_destroy(data->state.areschannel);
#endif

  /* No longer a dirty share, if it exists */
  if (data->share)
    data->share->dirty--;

  free(data);
  return CURLE_OK;
}