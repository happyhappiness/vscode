{
    dest[2 * i] = (unsigned char)(Curl_raw_toupper(src[i]));
    dest[2 * i + 1] = '\0';
  }