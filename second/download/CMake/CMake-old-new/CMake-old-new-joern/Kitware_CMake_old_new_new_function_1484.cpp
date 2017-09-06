char *curl_version(void)
{
  static char version[200];
  char *ptr;
  long num;
  strcpy(version, LIBCURL_NAME "/" LIBCURL_VERSION );
  ptr=strchr(version, '\0');

#ifdef USE_SSLEAY
  getssl_version(ptr, &num);
  ptr=strchr(version, '\0');
#else
  (void)num; /* no compiler warning please */
#endif

#ifdef KRB4
  sprintf(ptr, " krb4");
  ptr += strlen(ptr);
#endif
#ifdef ENABLE_IPV6
  sprintf(ptr, " ipv6");
  ptr += strlen(ptr);
#endif
#ifdef HAVE_LIBZ
  sprintf(ptr, " zlib/%s", zlibVersion());
  ptr += strlen(ptr);
#endif

  return version;
}