char *curl_version(void)
{
  static char version[200];
  char *ptr=version;
  size_t len;
  size_t left = sizeof(version);
  strcpy(ptr, LIBCURL_NAME "/" LIBCURL_VERSION );
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
#ifdef USE_LIBIDN
  if(stringprep_check_version(LIBIDN_REQUIRED_VERSION)) {
    len = snprintf(ptr, left, " libidn/%s", stringprep_check_version(NULL));
    left -= len;
    ptr += len;
  }
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
  len = snprintf(ptr, left, " libssh2/%s", LIBSSH2_VERSION);
  left -= len;
  ptr += len;
#endif

  return version;
}