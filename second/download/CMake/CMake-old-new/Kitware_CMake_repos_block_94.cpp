{
  static bool initialized;
  static char version[200];
  char *ptr = version;
  size_t len;
  size_t left = sizeof(version);

  if(initialized)
    return version;

  strcpy(ptr, LIBCURL_NAME "/" LIBCURL_VERSION);
  len = strlen(ptr);
  left -= len;
  ptr += len;

  if(left > 1) {
    len = Curl_ssl_version(ptr + 1, left - 1);

    if(len > 0) {
      *ptr = ' ';
      left -= ++len;
      ptr += len;
    }
  }

#ifdef HAVE_LIBZ
  len = snprintf(ptr, left, " zlib/%s", zlibVersion());
  left -= len;
  ptr += len;
#endif
#ifdef USE_ARES
  /* this function is only present in c-ares, not in the original ares */
  len = snprintf(ptr, left, " c-ares/%s", ares_version(NULL));
  left -= len;
  ptr += len;
#endif
#ifdef USE_LIBIDN2
  if(idn2_check_version(IDN2_VERSION)) {
    len = snprintf(ptr, left, " libidn2/%s", idn2_check_version(NULL));
    left -= len;
    ptr += len;
  }
#endif
#ifdef USE_LIBPSL
  len = snprintf(ptr, left, " libpsl/%s", psl_get_version());
  left -= len;
  ptr += len;
#endif
#ifdef USE_WIN32_IDN
  len = snprintf(ptr, left, " WinIDN");
  left -= len;
  ptr += len;
#endif
#if defined(HAVE_ICONV) && defined(CURL_DOES_CONVERSIONS)
#ifdef _LIBICONV_VERSION
  len = snprintf(ptr, left, " iconv/%d.%d",
                 _LIBICONV_VERSION >> 8, _LIBICONV_VERSION & 255);
#else
  /* version unknown */
  len = snprintf(ptr, left, " iconv");
#endif /* _LIBICONV_VERSION */
  left -= len;
  ptr += len;
#endif
#ifdef USE_LIBSSH2
  len = snprintf(ptr, left, " libssh2/%s", CURL_LIBSSH2_VERSION);
  left -= len;
  ptr += len;
#endif
#ifdef USE_NGHTTP2
  len = Curl_http2_ver(ptr, left);
  left -= len;
  ptr += len;
#endif
#ifdef USE_LIBRTMP
  {
    char suff[2];
    if(RTMP_LIB_VERSION & 0xff) {
      suff[0] = (RTMP_LIB_VERSION & 0xff) + 'a' - 1;
      suff[1] = '\0';
    }
    else
      suff[0] = '\0';

    snprintf(ptr, left, " librtmp/%d.%d%s",
             RTMP_LIB_VERSION >> 16, (RTMP_LIB_VERSION >> 8) & 0xff,
             suff);
/*
  If another lib version is added below this one, this code would
  also have to do:

    len = what snprintf() returned

    left -= len;
    ptr += len;
*/
  }
#endif

  initialized = true;
  return version;
}