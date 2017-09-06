static void getssl_version(char *ptr, long *num)
{

#if (SSLEAY_VERSION_NUMBER >= 0x905000)
  {
    char sub[2];
    unsigned long ssleay_value;
    sub[1]='\0';
    ssleay_value=SSLeay();
    *num = ssleay_value;
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

    sprintf(ptr, " OpenSSL/%lx.%lx.%lx%s",
            (ssleay_value>>28)&0xf,
            (ssleay_value>>20)&0xff,
            (ssleay_value>>12)&0xff,
            sub);
  }

#else
  *num = SSLEAY_VERSION_NUMBER;
#if (SSLEAY_VERSION_NUMBER >= 0x900000)
  sprintf(ptr, " OpenSSL/%lx.%lx.%lx",
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

    sprintf(ptr, " SSL/%x.%x.%x%s",
            (SSLEAY_VERSION_NUMBER>>12)&0xff,
            (SSLEAY_VERSION_NUMBER>>8)&0xf,
            (SSLEAY_VERSION_NUMBER>>4)&0xf, sub);
  }
#endif
#endif
}