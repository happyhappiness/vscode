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
  char sep;
  char sep2;
  int step;
  int rc;

  pat = (URLPattern*)&glob->pattern[glob->size / 2];
  /* patterns 0,1,2,... correspond to size=1,3,5,... */
  ++glob->size;

  if (ISALPHA(*pattern)) {         /* character range detected */
    char min_c;
    char max_c;

    pat->type = UPTCharRange;
    rc = sscanf(pattern, "%c-%c%c%d%c", &min_c, &max_c, &sep, &step, &sep2);
    if ((rc < 3) || (min_c >= max_c) || ((max_c - min_c) > ('z' - 'a'))) {
      /* the pattern is not well-formed */
      snprintf(glob->errormsg, sizeof(glob->errormsg),
               "error: bad range specification after pos %d\n", pos);
      return GLOB_ERROR;
    }

    /* check the (first) separating character */
    if((sep != ']') && (sep != ':')) {
      snprintf(glob->errormsg, sizeof(glob->errormsg),
               "error: unsupported character (%c) after range at pos %d\n",
               sep, pos);
      return GLOB_ERROR;
    }

    /* if there was a ":[num]" thing, use that as step or else use 1 */
    pat->content.CharRange.step =
      ((sep == ':') && (rc == 5) && (sep2 == ']'))?step:1;

    pat->content.CharRange.ptr_c = pat->content.CharRange.min_c = min_c;
    pat->content.CharRange.max_c = max_c;
  }
  else if (ISDIGIT(*pattern)) { /* numeric range detected */
    int min_n;
    int max_n;

    pat->type = UPTNumRange;
    pat->content.NumRange.padlength = 0;

    rc = sscanf(pattern, "%d-%d%c%d%c", &min_n, &max_n, &sep, &step, &sep2);

    if ((rc < 2) || (min_n > max_n)) {
      /* the pattern is not well-formed */
      snprintf(glob->errormsg, sizeof(glob->errormsg),
               "error: bad range specification after pos %d\n", pos);
      return GLOB_ERROR;
    }
    pat->content.NumRange.ptr_n =  pat->content.NumRange.min_n = min_n;
    pat->content.NumRange.max_n = max_n;

    /* if there was a ":[num]" thing, use that as step or else use 1 */
    pat->content.NumRange.step =
      ((sep == ':') && (rc == 5) && (sep2 == ']'))?step:1;

    if (*pattern == '0') {              /* leading zero specified */
      c = pattern;
      while (ISDIGIT(*c)) {
        c++;
        ++pat->content.NumRange.padlength; /* padding length is set for all
                                              instances of this pattern */
      }
    }

  }
  else {
    snprintf(glob->errormsg, sizeof(glob->errormsg),
             "illegal character in range specification at pos %d\n", pos);
    return GLOB_ERROR;
  }

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

  if(pat->type == UPTCharRange)
    *amount = (pat->content.CharRange.max_c -
               pat->content.CharRange.min_c + 1) *
      wordamount;
  else
    *amount = (pat->content.NumRange.max_n -
               pat->content.NumRange.min_n + 1) * wordamount;

  return GLOB_OK;
}