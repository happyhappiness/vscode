char *glob_next_url(URLGlob *glob)
{
  char *buf = glob->glob_buffer;
  URLPattern *pat;
  char *lit;
  size_t i;
  size_t j;
  size_t buflen = glob->urllen+1;
  size_t len;

  if (!glob->beenhere)
    glob->beenhere = 1;
  else {
    bool carry = TRUE;

    /* implement a counter over the index ranges of all patterns,
       starting with the rightmost pattern */
    for (i = glob->size / 2 - 1; carry && i < glob->size; --i) {
      carry = FALSE;
      pat = &glob->pattern[i];
      switch (pat->type) {
      case UPTSet:
        if (++pat->content.Set.ptr_s == pat->content.Set.size) {
          pat->content.Set.ptr_s = 0;
          carry = TRUE;
        }
        break;
      case UPTCharRange:
        pat->content.CharRange.ptr_c = (char)(pat->content.CharRange.step +
                           (int)((unsigned char)pat->content.CharRange.ptr_c));
        if (pat->content.CharRange.ptr_c > pat->content.CharRange.max_c) {
          pat->content.CharRange.ptr_c = pat->content.CharRange.min_c;
          carry = TRUE;
        }
        break;
      case UPTNumRange:
        pat->content.NumRange.ptr_n += pat->content.NumRange.step;
        if (pat->content.NumRange.ptr_n > pat->content.NumRange.max_n) {
          pat->content.NumRange.ptr_n = pat->content.NumRange.min_n;
          carry = TRUE;
        }
        break;
      default:
        printf("internal error: invalid pattern type (%d)\n", (int)pat->type);
        exit (CURLE_FAILED_INIT);
      }
    }
    if (carry)          /* first pattern ptr has run into overflow, done! */
      return NULL;
  }

  for (j = 0; j < glob->size; ++j) {
    if (!(j&1)) {              /* every other term (j even) is a literal */
      lit = glob->literal[j/2];
      len = snprintf(buf, buflen, "%s", lit);
      buf += len;
      buflen -= len;
    }
    else {                              /* the rest (i odd) are patterns */
      pat = &glob->pattern[j/2];
      switch(pat->type) {
      case UPTSet:
        len = strlen(pat->content.Set.elements[pat->content.Set.ptr_s]);
        snprintf(buf, buflen, "%s",
                 pat->content.Set.elements[pat->content.Set.ptr_s]);
        buf += len;
        buflen -= len;
        break;
      case UPTCharRange:
        *buf++ = pat->content.CharRange.ptr_c;
        break;
      case UPTNumRange:
        len = snprintf(buf, buflen, "%0*d",
                       pat->content.NumRange.padlength,
                       pat->content.NumRange.ptr_n);
        buf += len;
        buflen -= len;
        break;
      default:
        printf("internal error: invalid pattern type (%d)\n", (int)pat->type);
        exit (CURLE_FAILED_INIT);
      }
    }
  }
  *buf = '\0';
  return strdup(glob->glob_buffer);
}