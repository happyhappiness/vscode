static GlobCode glob_word(URLGlob *glob, char *pattern,
                          size_t pos, int *amount)
{
  /* processes a literal string component of a URL
     special characters '{' and '[' branch to set/range processing functions
   */
  char* buf = glob->glob_buffer;
  size_t litindex;
  GlobCode res = GLOB_OK;

  *amount = 1; /* default is one single string */

  while (*pattern != '\0' && *pattern != '{' && *pattern != '[') {
    if (*pattern == '}' || *pattern == ']')
      return GLOB_ERROR;

    /* only allow \ to escape known "special letters" */
    if (*pattern == '\\' &&
        (*(pattern+1) == '{' || *(pattern+1) == '[' ||
         *(pattern+1) == '}' || *(pattern+1) == ']') ) {

      /* escape character, skip '\' */
      ++pattern;
      ++pos;
      if (*pattern == '\0')             /* but no escaping of '\0'! */
        return GLOB_ERROR;
    }
    *buf++ = *pattern++;                /* copy character to literal */
    ++pos;
  }
  *buf = '\0';
  litindex = glob->size / 2;
  /* literals 0,1,2,... correspond to size=0,2,4,... */
  glob->literal[litindex] = strdup(glob->glob_buffer);
  if(!glob->literal[litindex])
    return GLOB_ERROR;
  ++glob->size;

  switch (*pattern) {
  case '\0':
    break;                      /* singular URL processed  */

  case '{':
    /* process set pattern */
    res = glob_set(glob, ++pattern, ++pos, amount);
    break;

  case '[':
    /* process range pattern */
    res= glob_range(glob, ++pattern, ++pos, amount);
    break;
  }

  if(GLOB_OK != res)
    /* free that strdup'ed string again */
    free(glob->literal[litindex]);

  return res; /* something got wrong */
}