f(mutual_auth) {
    *outptr = strdup("");
    if(!*outptr)
      result = CURLE_OUT_OF_MEMORY;
  }