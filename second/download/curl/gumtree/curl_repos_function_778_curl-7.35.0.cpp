static GlobCode glob_parse(URLGlob *glob, char *pattern,
                           size_t pos, unsigned long *amount)
{
  /* processes a literal string component of a URL
     special characters '{' and '[' branch to set/range processing functions
   */
  GlobCode res = GLOB_OK;
  int globindex = 0; /* count "actual" globs */

  *amount = 1;

  while(*pattern && !res) {
    char *buf = glob->glob_buffer;
    int sublen = 0;
    while(*pattern && *pattern != '{' && *pattern != '[') {
      if(*pattern == '}' || *pattern == ']')
        return GLOBERROR("unmatched close brace/bracket", pos, GLOB_ERROR);

      /* only allow \ to escape known "special letters" */
      if(*pattern == '\\' &&
         (*(pattern+1) == '{' || *(pattern+1) == '[' ||
          *(pattern+1) == '}' || *(pattern+1) == ']') ) {

        /* escape character, skip '\' */
        ++pattern;
        ++pos;
      }
      *buf++ = *pattern++; /* copy character to literal */
      ++pos;
      sublen++;
    }
    if(sublen) {
      /* we got a literal string, add it as a single-item list */
      *buf = '\0';
      res = glob_fixed(glob, glob->glob_buffer, sublen);
    }
    else {
      switch (*pattern) {
      case '\0': /* done  */
        break;

      case '{':
        /* process set pattern */
        pattern++;
        pos++;
        res = glob_set(glob, &pattern, &pos, amount, globindex++);
        break;

      case '[':
        /* process range pattern */
        pattern++;
        pos++;
        res = glob_range(glob, &pattern, &pos, amount, globindex++);
        break;
      }
    }

    if(++glob->size > GLOB_PATTERN_NUM)
      return GLOBERROR("too many globs", pos, GLOB_ERROR);
  }
  return res;
}