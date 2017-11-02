static char *
dynconvert(int dccsid, const char * s, int slen, int sccsid)

{
  char * d;
  char * cp;
  size_t dlen;
  int l;
  static const char nullbyte = 0;

  /* Like convert, but the destination is allocated and returned. */

  dlen = (size_t) (slen < 0? strlen(s): slen) + 1;
  dlen *= MAX_CONV_EXPANSION;           /* Allow some expansion. */
  d = malloc(dlen);

  if(!d)
    return (char *) NULL;

  l = convert(d, dlen, dccsid, s, slen, sccsid);

  if(l < 0) {
    free(d);
    return (char *) NULL;
    }

  if(slen < 0) {
    /* Need to null-terminate even when source length is given.
       Since destination code size is unknown, use a conversion to generate
       terminator. */

    int l2 = convert(d + l, dlen - l, dccsid, &nullbyte, -1, ASCII_CCSID);

    if(l2 < 0) {
      free(d);
      return (char *) NULL;
      }

    l += l2;
    }

  if((size_t) l < dlen) {
    cp = realloc(d, l);         /* Shorten to minimum needed. */

    if(cp)
      d = cp;
    }

  return d;
}