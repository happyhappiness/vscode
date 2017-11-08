curl_version_info_data *curl_version_info(CURLversion stamp)
{
#ifdef USE_SSLEAY
  static char ssl_buffer[80];
  long num;
  getssl_version(ssl_buffer, &num);

  version_info.ssl_version = ssl_buffer;
  version_info.ssl_version_num = num;
  /* SSL stuff is left zero if undefined */
#endif

#ifdef HAVE_LIBZ
  version_info.libz_version = zlibVersion();
  /* libz left NULL if non-existing */
#endif
  (void)stamp; /* avoid compiler warnings, we don't use this */

  return &version_info;
}