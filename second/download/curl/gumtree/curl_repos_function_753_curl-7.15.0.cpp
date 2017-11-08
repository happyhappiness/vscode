void curl_global_cleanup(void)
{
  if (!initialized)
    return;

  Curl_global_host_cache_dtor();

  if (init_flags & CURL_GLOBAL_SSL)
    Curl_ssl_cleanup();

  if (init_flags & CURL_GLOBAL_WIN32)
    win32_cleanup();

#ifdef _AMIGASF
  amiga_cleanup();
#endif

  initialized = 0;
  init_flags  = 0;
}