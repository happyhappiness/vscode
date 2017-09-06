static CURLcode global_init(long flags, bool memoryfuncs)
{
  if(initialized++)
    return CURLE_OK;

  if(memoryfuncs) {
    /* Setup the default memory functions here (again) */
    Curl_cmalloc = (curl_malloc_callback)malloc;
    Curl_cfree = (curl_free_callback)free;
    Curl_crealloc = (curl_realloc_callback)realloc;
    Curl_cstrdup = (curl_strdup_callback)system_strdup;
    Curl_ccalloc = (curl_calloc_callback)calloc;
#if defined(WIN32) && defined(UNICODE)
    Curl_cwcsdup = (curl_wcsdup_callback)_wcsdup;
#endif
  }

  if(flags & CURL_GLOBAL_SSL)
    if(!Curl_ssl_init()) {
      DEBUGF(fprintf(stderr, "Error: Curl_ssl_init failed\n"));
      return CURLE_FAILED_INIT;
    }

  if(flags & CURL_GLOBAL_WIN32)
    if(win32_init()) {
      DEBUGF(fprintf(stderr, "Error: win32_init failed\n"));
      return CURLE_FAILED_INIT;
    }

#ifdef __AMIGA__
  if(!Curl_amiga_init()) {
    DEBUGF(fprintf(stderr, "Error: Curl_amiga_init failed\n"));
    return CURLE_FAILED_INIT;
  }
#endif

#ifdef NETWARE
  if(netware_init()) {
    DEBUGF(fprintf(stderr, "Warning: LONG namespace not available\n"));
  }
#endif

  if(Curl_resolver_global_init()) {
    DEBUGF(fprintf(stderr, "Error: resolver_global_init failed\n"));
    return CURLE_FAILED_INIT;
  }

  (void)Curl_ipv6works();

#if defined(USE_LIBSSH2) && defined(HAVE_LIBSSH2_INIT)
  if(libssh2_init(0)) {
    DEBUGF(fprintf(stderr, "Error: libssh2_init failed\n"));
    return CURLE_FAILED_INIT;
  }
#endif

  if(flags & CURL_GLOBAL_ACK_EINTR)
    Curl_ack_eintr = 1;

  init_flags = flags;

  Curl_version_init();

  return CURLE_OK;
}