char *curl_version(void)
{
  static char version[200];
  char *ptr=version;
  size_t len;
  size_t left = sizeof(version);
  strcpy(ptr, LIBCURL_NAME "/" LIBCURL_VERSION );
  ptr=strchr(ptr, '\0');
  left -= strlen(ptr);

  len = Curl_ssl_version(ptr, left);
  left -= len;
  ptr += len;

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

  return version;
}