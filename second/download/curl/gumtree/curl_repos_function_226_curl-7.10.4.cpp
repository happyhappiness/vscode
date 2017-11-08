CURLcode Curl_close(struct SessionHandle *data)
{
  /* Loop through all open connections and kill them one by one */
  while(-1 != ConnectionKillOne(data));

#ifdef USE_SSLEAY
  /* Close down all open SSL info and sessions */
  Curl_SSL_Close_All(data);
#endif

  /* No longer a dirty share, if it exists */
  if (data->share)
    data->share->dirty--;

  if(data->change.cookielist) /* clean up list if any */
    curl_slist_free_all(data->change.cookielist);

  if(data->state.auth_host)
    free(data->state.auth_host);

  if(data->state.scratch)
    free(data->state.scratch);

  if(data->change.proxy_alloc)
    free(data->change.proxy);

  if(data->change.referer_alloc)
    free(data->change.referer);

  if(data->change.url_alloc)
    free(data->change.url);

  if(data->state.headerbuff)
    free(data->state.headerbuff);

#ifndef CURL_DISABLE_HTTP
  if(data->set.cookiejar)
    /* we have a "destination" for all the cookies to get dumped to */
    Curl_cookie_output(data->cookies, data->set.cookiejar);

  Curl_cookie_cleanup(data->cookies);
#endif

  /* free the connection cache */
  free(data->state.connects);

  if(data->info.contenttype)
    free(data->info.contenttype);

  free(data);
  return CURLE_OK;
}