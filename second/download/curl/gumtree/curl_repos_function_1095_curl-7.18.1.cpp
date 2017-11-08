CURLcode curl_global_init(long flags)
{
  if(initialized++)
    return CURLE_OK;

  /* Setup the default memory functions here (again) */
  Curl_cmalloc = (curl_malloc_callback)malloc;
  Curl_cfree = (curl_free_callback)free;
  Curl_crealloc = (curl_realloc_callback)realloc;
  Curl_cstrdup = (curl_strdup_callback)system_strdup;
  Curl_ccalloc = (curl_calloc_callback)calloc;

  if(flags & CURL_GLOBAL_SSL)
    if(!Curl_ssl_init()) {
      DEBUGF(fprintf(stderr, "Error: Curl_ssl_init failed\n"));
      return CURLE_FAILED_INIT;
    }

  if(flags & CURL_GLOBAL_WIN32)
    if(win32_init() != CURLE_OK) {
      DEBUGF(fprintf(stderr, "Error: win32_init failed\n"));
      return CURLE_FAILED_INIT;
    }

#ifdef __AMIGA__
  if(!amiga_init()) {
    DEBUGF(fprintf(stderr, "Error: amiga_init failed\n"));
    return CURLE_FAILED_INIT;
  }
#endif

#ifdef NETWARE
  if(netware_init()) {
    DEBUGF(fprintf(stderr, "Warning: LONG namespace not available\n"));
  }
#endif

#ifdef USE_LIBIDN
  idna_init();
#endif

  init_flags  = flags;

  return CURLE_OK;
}