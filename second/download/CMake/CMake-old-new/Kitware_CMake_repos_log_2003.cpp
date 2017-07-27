return snprintf(buffer, size, "%s/%lx.%lx.%lx%s",
                  OSSL_PACKAGE,
                  (ssleay_value>>28)&0xf,
                  (ssleay_value>>20)&0xff,
                  (ssleay_value>>12)&0xff,
                  sub);