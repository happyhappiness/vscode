curl_version_info_data *curl_version_info(CURLversion stamp)
{
#ifdef USE_SSL
  static char ssl_buffer[80];
  Curl_ssl_version(ssl_buffer, sizeof(ssl_buffer));
  version_info.ssl_version = ssl_buffer;
#endif

#ifdef HAVE_LIBZ
  version_info.libz_version = zlibVersion();
  /* libz left NULL if non-existing */
#endif
#ifdef USE_ARES
  {
    int aresnum;
    version_info.ares = ares_version(&aresnum);
    version_info.ares_num = aresnum;
  }
#endif
#ifdef USE_LIBIDN
  /* This returns a version string if we use the given version or later,
     otherwise it returns NULL */
  version_info.libidn = stringprep_check_version(LIBIDN_REQUIRED_VERSION);
  if(version_info.libidn)
    version_info.features |= CURL_VERSION_IDN;
#endif
  (void)stamp; /* avoid compiler warnings, we don't use this */

  return &version_info;
}