CURLcode curl_global_init(long flags)
{
  if (initialized)
    return CURLE_OK;

  if (flags & CURL_GLOBAL_SSL)
    Curl_SSL_init();

  if (flags & CURL_GLOBAL_WIN32)
    if (win32_init() != CURLE_OK)
      return CURLE_FAILED_INIT;

  initialized = 1;
  init_flags  = flags;
  
  return CURLE_OK;
}