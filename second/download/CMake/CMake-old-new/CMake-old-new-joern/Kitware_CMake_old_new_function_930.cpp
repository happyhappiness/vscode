char *curl_version(void)
{
  static char version[200];
  char *ptr;
  strcpy(version, LIBCURL_NAME " " LIBCURL_VERSION );
  ptr=strchr(version, '\0');

#ifdef USE_SSLEAY

#if (SSLEAY_VERSION_NUMBER >= 0x905000)
  {
    char sub[2];
    unsigned long ssleay_value;
    sub[1]='\0';
    ssleay_value=SSLeay();
    if(ssleay_value < 0x906000) {
      ssleay_value=SSLEAY_VERSION_NUMBER;
      sub[0]='\0';
    }
    else {
      if(ssleay_value&0xff0) {
        sub[0]=((ssleay_value>>4)&0xff) + 'a' -1;
      }
      else
        sub[0]='\0';
    }

    sprintf(ptr, " (OpenSSL %lx.%lx.%lx%s)",
            (ssleay_value>>28)&0xf,
            (ssleay_value>>20)&0xff,
            (ssleay_value>>12)&0xff,
            sub);
  }

#else
#if (SSLEAY_VERSION_NUMBER >= 0x900000)
  sprintf(ptr, " (SSL %lx.%lx.%lx)",
          (SSLEAY_VERSION_NUMBER>>28)&0xff,
          (SSLEAY_VERSION_NUMBER>>20)&0xff,
          (SSLEAY_VERSION_NUMBER>>12)&0xf);
#else
  {
    char sub[2];
    sub[1]='\0';
    if(SSLEAY_VERSION_NUMBER&0x0f) {
      sub[0]=(SSLEAY_VERSION_NUMBER&0x0f) + 'a' -1;
    }
    else
      sub[0]='\0';

    sprintf(ptr, " (SSL %x.%x.%x%s)",
            (SSLEAY_VERSION_NUMBER>>12)&0xff,
            (SSLEAY_VERSION_NUMBER>>8)&0xf,
            (SSLEAY_VERSION_NUMBER>>4)&0xf, sub);
  }
#endif
#endif
  ptr=strchr(ptr, '\0');
#endif

#if defined(KRB4) || defined(ENABLE_IPV6)
  strcat(ptr, " (");
  ptr+=2;
#ifdef KRB4
  sprintf(ptr, "krb4 ");
  ptr += strlen(ptr);
#endif
#ifdef ENABLE_IPV6
  sprintf(ptr, "ipv6 ");
  ptr += strlen(ptr);
#endif
  sprintf(ptr, "enabled)");
  ptr += strlen(ptr);
#endif

#ifdef USE_ZLIB
  sprintf(ptr, " (zlib %s)", zlibVersion());
  ptr += strlen(ptr);
#endif

  return version;
}