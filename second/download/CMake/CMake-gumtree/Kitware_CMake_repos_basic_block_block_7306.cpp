f(type == CURL_ASN1_UTF8_STRING) {
    /* Just copy. */
    outlength = inlength;
    if(outlength)
      memcpy(buf, from, outlength);
  }
  else {
    for(outlength = 0; from < end;) {
      wc = 0;
      switch(size) {
      case 4:
        wc = (wc << 8) | *(const unsigned char *) from++;
        wc = (wc << 8) | *(const unsigned char *) from++;
        /* fallthrough */
      case 2:
        wc = (wc << 8) | *(const unsigned char *) from++;
        /* fallthrough */
      default: /* case 1: */
        wc = (wc << 8) | *(const unsigned char *) from++;
      }
      charsize = 1;
      if(wc >= 0x00000080) {
        if(wc >= 0x00000800) {
          if(wc >= 0x00010000) {
            if(wc >= 0x00200000) {
              free(buf);
              return -1;        /* Invalid char. size for target encoding. */
            }
            buf[outlength + 3] = (char) (0x80 | (wc & 0x3F));
            wc = (wc >> 6) | 0x00010000;
            charsize++;
          }
          buf[outlength + 2] = (char) (0x80 | (wc & 0x3F));
          wc = (wc >> 6) | 0x00000800;
          charsize++;
        }
        buf[outlength + 1] = (char) (0x80 | (wc & 0x3F));
        wc = (wc >> 6) | 0x000000C0;
        charsize++;
      }
      buf[outlength] = (char) wc;
      outlength += charsize;
    }
  }