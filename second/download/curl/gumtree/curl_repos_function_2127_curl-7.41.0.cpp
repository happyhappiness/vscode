size_t Curl_ossl_version(char *buffer, size_t size)
{
#ifdef YASSL_VERSION
  /* yassl provides an OpenSSL API compatibility layer so it looks identical
     to OpenSSL in all other aspects */
  return snprintf(buffer, size, "yassl/%s", YASSL_VERSION);
#else /* YASSL_VERSION */
#ifdef OPENSSL_IS_BORINGSSL
  return snprintf(buffer, size, "BoringSSL");
#else /* OPENSSL_IS_BORINGSSL */

#if(SSLEAY_VERSION_NUMBER >= 0x905000)
  {
    char sub[3];
    unsigned long ssleay_value;
    sub[2]='\0';
    sub[1]='\0';
    ssleay_value=SSLeay();
    if(ssleay_value < 0x906000) {
      ssleay_value=SSLEAY_VERSION_NUMBER;
      sub[0]='\0';
    }
    else {
      if(ssleay_value&0xff0) {
        int minor_ver = (ssleay_value >> 4) & 0xff;
        if(minor_ver > 26) {
          /* handle extended version introduced for 0.9.8za */
          sub[1] = (char) ((minor_ver - 1) % 26 + 'a' + 1);
          sub[0] = 'z';
        }
        else {
          sub[0]=(char)(((ssleay_value>>4)&0xff) + 'a' -1);
        }
      }
      else
        sub[0]='\0';
    }

    return snprintf(buffer, size, "%s/%lx.%lx.%lx%s",
#ifdef LIBRESSL_VERSION_NUMBER
                    "LibreSSL"
#else
                    "OpenSSL"
#endif
                    , (ssleay_value>>28)&0xf,
                    (ssleay_value>>20)&0xff,
                    (ssleay_value>>12)&0xff,
                    sub);
  }

#else /* SSLEAY_VERSION_NUMBER is less than 0.9.5 */

#if(SSLEAY_VERSION_NUMBER >= 0x900000)
  return snprintf(buffer, size, "OpenSSL/%lx.%lx.%lx",
                  (SSLEAY_VERSION_NUMBER>>28)&0xff,
                  (SSLEAY_VERSION_NUMBER>>20)&0xff,
                  (SSLEAY_VERSION_NUMBER>>12)&0xf);

#else /* (SSLEAY_VERSION_NUMBER >= 0x900000) */
  {
    char sub[2];
    sub[1]='\0';
    if(SSLEAY_VERSION_NUMBER&0x0f) {
      sub[0]=(SSLEAY_VERSION_NUMBER&0x0f) + 'a' -1;
    }
    else
      sub[0]='\0';

    return snprintf(buffer, size, "SSL/%x.%x.%x%s",
                    (SSLEAY_VERSION_NUMBER>>12)&0xff,
                    (SSLEAY_VERSION_NUMBER>>8)&0xf,
                    (SSLEAY_VERSION_NUMBER>>4)&0xf, sub);
  }
#endif /* (SSLEAY_VERSION_NUMBER >= 0x900000) */
#endif /* SSLEAY_VERSION_NUMBER is less than 0.9.5 */

#endif /* OPENSSL_IS_BORINGSSL */
#endif /* YASSL_VERSION */
}