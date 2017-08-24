    return CURLE_FAILED_INIT;
  }

  (void)Curl_ipv6works();

#if defined(USE_LIBSSH2) && defined(HAVE_LIBSSH2_INIT)
  if(libssh2_init(0)) {
    DEBUGF(fprintf(stderr, "Error: libssh2_init failed\n"));
