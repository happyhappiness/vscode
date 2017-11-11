static GlobCode glob_range(URLGlob *glob, char *pattern,
                           size_t pos, int *amount)
{
  /* processes a range expression with the point behind the opening '['
     - char range: e.g. "a-z]", "B-Q]"
     - num range: e.g. "0-9]", "17-2000]"
     - num range with leading zeros: e.g. "001-999]"
     expression is checked for well-formedness and collected until the next ']'
  */
  URLPattern *pat;
  char *c;
  int wordamount=1;

  pat = (URLPattern*)&glob->pattern[glob->size / 2];
  /* patterns 0,1,2,... correspond to size=1,3,5,... */
  ++glob->size;

  if (isalpha((int)*pattern)) {         /* character range detected */
    pat->type = UPTCharRange;
    if (sscanf(pattern, "%c-%c]", &pat->content.CharRange.min_c,
               &pat->content.CharRange.max_c) != 2 ||
        pat->content.CharRange.min_c >= pat->content.CharRange.max_c ||
        pat->content.CharRange.max_c - pat->content.CharRange.min_c > 'z' - 'a') {
      /* the pattern is not well-formed */
      snprintf(glob->errormsg, sizeof(glob->errormsg),
               "illegal pattern or range specification after pos %d\n", pos);
      return GLOB_ERROR;
    }
    pat->content.CharRange.ptr_c = pat->content.CharRange.min_c;
    /* always check for a literal (may be "") between patterns */

    if(GLOB_ERROR == glob_word(glob, pattern + 4, pos + 4, &wordamount))
      wordamount=1;

    *amount = (pat->content.CharRange.max_c -
               pat->content.CharRange.min_c + 1) *
      wordamount;

    return GLOB_OK;
  }

  if (isdigit((int)*pattern)) { /* numeric range detected */

    pat->type = UPTNumRange;
    pat->content.NumRange.padlength = 0;
    if (sscanf(pattern, "%d-%d]",
               &pat->content.NumRange.min_n,
               &pat->content.NumRange.max_n) != 2 ||
        pat->content.NumRange.min_n >= pat->content.NumRange.max_n) {
      /* the pattern is not well-formed */
      snprintf(glob->errormsg, sizeof(glob->errormsg),
               "error: illegal pattern or range specification after pos %d\n",
               pos);
      return GLOB_ERROR;
    }
    if (*pattern == '0') {              /* leading zero specified */
      c = pattern;
      while (isdigit((int)*c++))
        ++pat->content.NumRange.padlength; /* padding length is set for all
                                              instances of this pattern */
    }
    pat->content.NumRange.ptr_n = pat->content.NumRange.min_n;
    c = (char*)strchr(pattern, ']'); /* continue after next ']' */
    if(c)
      c++;
    else {
      snprintf(glob->errormsg, sizeof(glob->errormsg), "missing ']'");
      return GLOB_ERROR; /* missing ']' */
    }

    /* always check for a literal (may be "") between patterns */

    if(GLOB_ERROR == glob_word(glob, c, pos + (c - pattern), &wordamount))
      wordamount = 1;

    *amount = (pat->content.NumRange.max_n -
               pat->content.NumRange.min_n + 1) *
      wordamount;

    return GLOB_OK;
  }
  snprintf(glob->errormsg, sizeof(glob->errormsg),
           "illegal character in range specification at pos %d\n", pos);
  return GLOB_ERROR;
}