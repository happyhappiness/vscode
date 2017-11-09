static size_t Curl_ossl_version(char *buffer, size_t size)
{
#ifdef OPENSSL_IS_BORINGSSL
  return snprintf(buffer, size, OSSL_PACKAGE);
#else /* OPENSSL_IS_BORINGSSL */
  char sub[3];
  unsigned long ssleay_value;
  sub[2]='\0';
  sub[1]='\0';
  ssleay_value = OpenSSL_version_num();
  if(ssleay_value < 0x906000) {
    ssleay_value = SSLEAY_VERSION_NUMBER;
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
        sub[0] = (char) (minor_ver + 'a' - 1);
      }
    }
    else
      sub[0]='\0';
  }

  return snprintf(buffer, size, "%s/%lx.%lx.%lx%s",
                  OSSL_PACKAGE,
                  (ssleay_value>>28)&0xf,
                  (ssleay_value>>20)&0xff,
                  (ssleay_value>>12)&0xff,
                  sub);
#endif /* OPENSSL_IS_BORINGSSL */
}