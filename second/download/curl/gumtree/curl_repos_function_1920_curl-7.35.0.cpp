void curl_global_cleanup(void)
{
  if(!initialized)
    return;

  if(--initialized)
    return;

  Curl_global_host_cache_dtor();

  if(init_flags & CURL_GLOBAL_SSL)
    Curl_ssl_cleanup();

  Curl_resolver_global_cleanup();

  if(init_flags & CURL_GLOBAL_WIN32)
    win32_cleanup();

  Curl_amiga_cleanup();

#if defined(USE_LIBSSH2) && defined(HAVE_LIBSSH2_EXIT)
  (void)libssh2_exit();
#endif

  init_flags  = 0;
}