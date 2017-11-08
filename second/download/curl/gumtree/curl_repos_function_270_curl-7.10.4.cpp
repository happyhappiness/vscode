CURLSHcode
curl_share_setopt(CURLSH *sh, CURLSHoption option, ...)
{
  struct Curl_share *share = (struct Curl_share *)sh;
  va_list param;
  int type;
  curl_lock_function lockfunc;
  curl_unlock_function unlockfunc;
  void *ptr;

  if (share->dirty)
    /* don't allow setting options while one or more handles are already
       using this share */
    return CURLSHE_IN_USE;

  va_start(param, option);

  switch(option) {
  case CURLSHOPT_SHARE:
    /* this is a type this share will share */
    type = va_arg(param, int);
    share->specifier |= (1<<type);
    switch( type )
    {
      case CURL_LOCK_DATA_DNS:
        if (!share->hostcache) {
          share->hostcache = Curl_hash_alloc(7, Curl_freednsinfo);
        }
        break;

      case CURL_LOCK_DATA_COOKIE:
        break;

      case CURL_LOCK_DATA_SSL_SESSION:
        break;

      case CURL_LOCK_DATA_CONNECT:
        break;

      default:
        return CURLSHE_BAD_OPTION;
    }
    break;

  case CURLSHOPT_UNSHARE:
    /* this is a type this share will no longer share */
    type = va_arg(param, int);
    share->specifier &= ~(1<<type);
    switch( type )
    {
      case CURL_LOCK_DATA_DNS:
        if (share->hostcache) {
          Curl_hash_destroy(share->hostcache);
          share->hostcache = NULL;
        }
        break;

      case CURL_LOCK_DATA_COOKIE:
        break;

      case CURL_LOCK_DATA_SSL_SESSION:
        break;

      case CURL_LOCK_DATA_CONNECT:
        break;

      default:
        return CURLSHE_BAD_OPTION;
    }
    break;

  case CURLSHOPT_LOCKFUNC:
    lockfunc = va_arg(param, curl_lock_function);
    share->lockfunc = lockfunc;
    break;

  case CURLSHOPT_UNLOCKFUNC:
    unlockfunc = va_arg(param, curl_unlock_function);
    share->unlockfunc = unlockfunc;    
    break;

  case CURLSHOPT_USERDATA:
    ptr = va_arg(param, void *);
    share->clientdata = ptr;
    break;

  default:
    return CURLSHE_BAD_OPTION;
  }

  return CURLSHE_OK;
}