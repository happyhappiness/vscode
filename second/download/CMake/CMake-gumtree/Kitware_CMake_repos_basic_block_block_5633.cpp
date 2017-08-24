do {
    *dest++ = Curl_raw_toupper(*src);
  } while(*src++ && --n);