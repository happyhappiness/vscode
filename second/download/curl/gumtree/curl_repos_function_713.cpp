CURLcode curl_global_init(long flags)
{
  if (initialized)
    return CURLE_OK;

  /* Setup the default memory functions here (again) */
  Curl_cmalloc = (curl_malloc_callback)malloc;
  Curl_cfree = (curl_free_callback)free;
  Curl_crealloc = (curl_realloc_callback)realloc;
  Curl_cstrdup = (curl_strdup_callback)strdup;
  Curl_ccalloc = (curl_calloc_callback)calloc;

  if (flags & CURL_GLOBAL_SSL)
    if (!Curl_ssl_init())
      return CURLE_FAILED_INIT;

  if (flags & CURL_GLOBAL_WIN32)
    if (win32_init() != CURLE_OK)
      return CURLE_FAILED_INIT;

#ifdef _AMIGASF
  if(!amiga_init())
    return CURLE_FAILED_INIT;
#endif

#ifdef USE_LIBIDN
  idna_init();
#endif

  initialized = 1;
  init_flags  = flags;

  return CURLE_OK;
}