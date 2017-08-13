curl_version_info_data *curl_version_info(CURLversion stamp)
{
  static bool initialized;
#ifdef USE_LIBSSH2
  static char ssh_buffer[80];
#endif
#ifdef USE_SSL
  static char ssl_buffer[80];
#endif

  if(initialized)
    return &version_info;

#ifdef USE_SSL
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
#ifdef USE_LIBIDN2
  /* This returns a version string if we use the given version or later,
     otherwise it returns NULL */
  version_info.libidn = idn2_check_version(IDN2_VERSION);
  if(version_info.libidn)
    version_info.features |= CURL_VERSION_IDN;
#elif defined(USE_WIN32_IDN)
  version_info.features |= CURL_VERSION_IDN;
#endif

#if defined(HAVE_ICONV) && defined(CURL_DOES_CONVERSIONS)
#ifdef _LIBICONV_VERSION
  version_info.iconv_ver_num = _LIBICONV_VERSION;
#else
  /* version unknown */
  version_info.iconv_ver_num = -1;
#endif /* _LIBICONV_VERSION */
#endif

#ifdef USE_LIBSSH2
  snprintf(ssh_buffer, sizeof(ssh_buffer), "libssh2/%s", LIBSSH2_VERSION);
  version_info.libssh_version = ssh_buffer;
#endif

  (void)stamp; /* avoid compiler warnings, we don't use this */

  initialized = true;
  return &version_info;
}