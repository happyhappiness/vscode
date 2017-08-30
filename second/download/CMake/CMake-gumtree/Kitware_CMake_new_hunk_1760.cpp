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

