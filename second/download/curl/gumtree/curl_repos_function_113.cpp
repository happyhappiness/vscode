char *curl_version(void)
{
  static char version[200];
  char *ptr;
#if defined(USE_SSLEAY)
  static char sub[2];
#endif
  strcpy(version, LIBCURL_NAME " " LIBCURL_VERSION );
  ptr=strchr(version, '\0');

#ifdef USE_SSLEAY

#if (SSLEAY_VERSION_NUMBER >= 0x900000)
  sprintf(ptr, " (SSL %lx.%lx.%lx)",
          (SSLEAY_VERSION_NUMBER>>28)&0xff,
          (SSLEAY_VERSION_NUMBER>>20)&0xff,
          (SSLEAY_VERSION_NUMBER>>12)&0xf);
#else
  if(SSLEAY_VERSION_NUMBER&0x0f) {
    sub[0]=(SSLEAY_VERSION_NUMBER&0x0f) + 'a' -1;
  }
  else
    sub[0]=0;

  sprintf(ptr, " (SSL %x.%x.%x%s)",
          (SSLEAY_VERSION_NUMBER>>12)&0xff,
          (SSLEAY_VERSION_NUMBER>>8)&0xf,
          (SSLEAY_VERSION_NUMBER>>4)&0xf, sub);

#endif
  ptr=strchr(ptr, '\0');
#endif

#ifdef USE_ZLIB
  sprintf(ptr, " (zlib %s)", zlibVersion());
#endif

  return version;
}