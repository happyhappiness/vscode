f(ptr, " (SSL %lx.%lx.%lx)",
          (SSLEAY_VERSION_NUMBER>>28)&0xff,
          (SSLEAY_VERSION_NUMBER>>20)&0xff,
          (SSLEAY_VERSION_NUMBER>>12)&0xf);