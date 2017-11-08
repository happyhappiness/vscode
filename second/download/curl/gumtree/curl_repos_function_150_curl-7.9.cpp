CURLcode Curl_close(struct SessionHandle *data)
{
  /* Loop through all open connections and kill them one by one */
  while(-1 != ConnectionKillOne(data));

#ifdef USE_SSLEAY
  /* Close down all open info open SSL and sessions */
  Curl_SSL_Close_All(data);
#endif

  if(data->state.auth_host)
    free(data->state.auth_host);

  if(data->change.proxy_alloc)
    free(data->change.proxy);

  if(data->change.referer_alloc)
    free(data->change.referer);

  if(data->change.url_alloc)
    free(data->change.url);

  if(data->state.headerbuff)
    free(data->state.headerbuff);

  if(data->set.cookiejar)
    /* we have a "destination" for all the cookies to get dumped to */
    Curl_cookie_output(data->cookies, data->set.cookiejar);
    
  Curl_cookie_cleanup(data->cookies);

  /* free the connection cache */
  free(data->state.connects);

  free(data);
  return CURLE_OK;
}