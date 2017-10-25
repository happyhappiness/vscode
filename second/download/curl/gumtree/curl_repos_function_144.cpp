char *glob_next_url(URLGlob *glob)
{
  char *buf = glob->glob_buffer;
  URLPattern *pat;
  char *lit;
  size_t i;
  size_t j;
  int carry;

  if (!glob->beenhere)
    glob->beenhere = 1;
  else {
    carry = 1;

    /* implement a counter over the index ranges of all patterns,
       starting with the rightmost pattern */
    for (i = glob->size / 2 - 1; carry && i < glob->size; --i) {
      carry = 0;
      pat = &glob->pattern[i];
      switch (pat->type) {
      case UPTSet:
        if (++pat->content.Set.ptr_s == pat->content.Set.size) {
          pat->content.Set.ptr_s = 0;
          carry = 1;
        }
        break;
      case UPTCharRange:
        if (++pat->content.CharRange.ptr_c > pat->content.CharRange.max_c) {
          pat->content.CharRange.ptr_c = pat->content.CharRange.min_c;
          carry = 1;
        }
        break;
      case UPTNumRange:
        if (++pat->content.NumRange.ptr_n > pat->content.NumRange.max_n) {
          pat->content.NumRange.ptr_n = pat->content.NumRange.min_n;
          carry = 1;
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
      strcpy(buf, lit);
      buf += strlen(lit);
    }
    else {                              /* the rest (i odd) are patterns */
      pat = &glob->pattern[j/2];
      switch(pat->type) {
      case UPTSet:
        strcpy(buf, pat->content.Set.elements[pat->content.Set.ptr_s]);
        buf += strlen(pat->content.Set.elements[pat->content.Set.ptr_s]);
        break;
      case UPTCharRange:
        *buf++ = pat->content.CharRange.ptr_c;
        break;
      case UPTNumRange:
        sprintf(buf, "%0*d",
                pat->content.NumRange.padlength, pat->content.NumRange.ptr_n);
        buf += strlen(buf); /* make no sprint() return code assumptions */
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