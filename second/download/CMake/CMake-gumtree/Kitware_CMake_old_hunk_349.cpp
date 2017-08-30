  left -= len;

  ptr += len;

#endif

#ifdef USE_LIBIDN

  if(stringprep_check_version(LIBIDN_REQUIRED_VERSION)) {

    len = snprintf(ptr, left, " libidn/%s", stringprep_check_version(NULL));

    left -= len;

    ptr += len;

  }

