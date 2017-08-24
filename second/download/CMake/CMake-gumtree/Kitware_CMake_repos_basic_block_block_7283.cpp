f(!(b &= 0x7F)) {
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