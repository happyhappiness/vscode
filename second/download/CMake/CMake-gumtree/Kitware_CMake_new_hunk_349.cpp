  left -= len;

  ptr += len;

#endif

#ifdef USE_LIBIDN2

  if(idn2_check_version(IDN2_VERSION)) {

    len = snprintf(ptr, left, " libidn2/%s", idn2_check_version(NULL));

    left -= len;

    ptr += len;

  }

