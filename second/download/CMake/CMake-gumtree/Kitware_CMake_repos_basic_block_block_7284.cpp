f(!(b & 0x80))
    len = b;
  else if(!(b &= 0x7F)) {
    /* Unspecified length. Since we have all the data, we can determine the
       effective length by skipping element until an end element is found. */
    if(!elem->constructed)
      return (const char *) NULL;
    elem->beg = beg;
    while(beg < end && *beg) {
      beg = Curl_getASN1Element(&lelem, beg, end);
      if(!beg)
        return (const char *) NULL;
    }
    if(beg >= end)
      return (const char *) NULL;
    elem->end = beg;
    return beg + 1;
  }
  else if((unsigned)b > (size_t)(end - beg))
    return (const char *) NULL; /* Does not fit in source. */
  else {
    /* Get long length. */
    len = 0;
    do {
      if(len & 0xFF000000L)
        return (const char *) NULL;  /* Lengths > 32 bits are not supported. */
      len = (len << 8) | (unsigned char) *beg++;
    } while(--b);
  }