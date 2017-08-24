{
  if(share == NULL)
    return CURLSHE_INVALID;

  if(share->lockfunc)
    share->lockfunc(NULL, CURL_LOCK_DATA_SHARE, CURL_LOCK_ACCESS_SINGLE,
                    share->clientdata);

  if(share->dirty) {
    if(share->unlockfunc)
      share->unlockfunc(NULL, CURL_LOCK_DATA_SHARE, share->clientdata);
    return CURLSHE_IN_USE;
  }

  Curl_hash_destroy(&share->hostcache);

#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
  Curl_cookie_cleanup(share->cookies);
#endif

#ifdef USE_SSL
  if(share->sslsession) {
    size_t i;
    for(i = 0; i < share->max_ssl_sessions; i++)
      Curl_ssl_kill_session(&(share->sslsession[i]));
    free(share->sslsession);
  }
#endif

  if(share->unlockfunc)
    share->unlockfunc(NULL, CURL_LOCK_DATA_SHARE, share->clientdata);
  free(share);

  return CURLSHE_OK;
}