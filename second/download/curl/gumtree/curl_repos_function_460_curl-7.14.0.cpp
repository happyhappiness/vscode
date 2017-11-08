CURLSHcode
curl_share_cleanup(CURLSH *sh)
{
  struct Curl_share *share = (struct Curl_share *)sh;

  if (share == NULL)
    return CURLSHE_INVALID;

  if(share->lockfunc)
    share->lockfunc(NULL, CURL_LOCK_DATA_SHARE, CURL_LOCK_ACCESS_SINGLE,
                    share->clientdata);

  if (share->dirty) {
    if(share->unlockfunc)
      share->unlockfunc(NULL, CURL_LOCK_DATA_SHARE, share->clientdata);
    return CURLSHE_IN_USE;
  }

  if(share->hostcache)
    Curl_hash_destroy(share->hostcache);

#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
  if(share->cookies)
    Curl_cookie_cleanup(share->cookies);
#endif   /* CURL_DISABLE_HTTP */

  if(share->unlockfunc)
    share->unlockfunc(NULL, CURL_LOCK_DATA_SHARE, share->clientdata);
  free(share);

  return CURLSHE_OK;
}