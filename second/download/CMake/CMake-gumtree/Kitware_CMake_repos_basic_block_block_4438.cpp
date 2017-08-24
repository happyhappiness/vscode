{
  static const char xdigits_l[] = "0123456789abcdef",
    xdigits_u[] = "0123456789ABCDEF";
  unsigned char tmp[IN6ADDRSZ], *tp, *endp, *colonp;
  const char *xdigits, *curtok;
  int ch, saw_xdigit;
  size_t val;

  memset((tp = tmp), 0, IN6ADDRSZ);
  endp = tp + IN6ADDRSZ;
  colonp = NULL;
  /* Leading :: requires some special handling. */
  if(*src == ':')
    if(*++src != ':')
      return (0);
  curtok = src;
  saw_xdigit = 0;
  val = 0;
  while((ch = *src++) != '\0') {
    const char *pch;

    pch = strchr((xdigits = xdigits_l), ch);
    if(!pch)
      pch = strchr((xdigits = xdigits_u), ch);
    if(pch != NULL) {
      val <<= 4;
      val |= (pch - xdigits);
      if(++saw_xdigit > 4)
        return (0);
      continue;
    }
    if(ch == ':') {
      curtok = src;
      if(!saw_xdigit) {
        if(colonp)
          return (0);
        colonp = tp;
        continue;
      }
      if(tp + INT16SZ > endp)
        return (0);
      *tp++ = (unsigned char) ((val >> 8) & 0xff);
      *tp++ = (unsigned char) (val & 0xff);
      saw_xdigit = 0;
      val = 0;
      continue;
    }
    if(ch == '.' && ((tp + INADDRSZ) <= endp) &&
        inet_pton4(curtok, tp) > 0) {
      tp += INADDRSZ;
      saw_xdigit = 0;
      break;    /* '\0' was seen by inet_pton4(). */
    }
    return (0);
  }
  if(saw_xdigit) {
    if(tp + INT16SZ > endp)
      return (0);
    *tp++ = (unsigned char) ((val >> 8) & 0xff);
    *tp++ = (unsigned char) (val & 0xff);
  }
  if(colonp != NULL) {
    /*
     * Since some memmove()'s erroneously fail to handle
     * overlapping regions, we'll do the shift by hand.
     */
    const ssize_t n = tp - colonp;
    ssize_t i;

    if(tp == endp)
      return (0);
    for(i = 1; i <= n; i++) {
      *(endp - i) = *(colonp + n - i);
      *(colonp + n - i) = 0;
    }
    tp = endp;
  }
  if(tp != endp)
    return (0);
  memcpy(dst, tmp, IN6ADDRSZ);
  return (1);
}