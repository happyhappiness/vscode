{
  unsigned char b;
  unsigned long len;
  curl_asn1Element lelem;

  /* Get a single ASN.1 element into `elem', parse ASN.1 string at `beg'
     ending at `end'.
     Returns a pointer in source string after the parsed element, or NULL
     if an error occurs. */
  if(!beg || !end || beg >= end || !*beg ||
     (size_t)(end - beg) > CURL_ASN1_MAX)
    return (const char *) NULL;

  /* Process header byte. */
  elem->header = beg;
  b = (unsigned char) *beg++;
  elem->constructed = (b & 0x20) != 0;
  elem->class = (b >> 6) & 3;
  b &= 0x1F;
  if(b == 0x1F)
    return (const char *) NULL; /* Long tag values not supported here. */
  elem->tag = b;

  /* Process length. */
  if(beg >= end)
    return (const char *) NULL;
  b = (unsigned char) *beg++;
  if(!(b & 0x80))
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
  if(len > (size_t)(end - beg))
    return (const char *) NULL;  /* Element data does not fit in source. */
  elem->beg = beg;
  elem->end = beg + len;
  return elem->end;
}