GlobCode glob_word(URLGlob *glob, char *pattern, int pos, int *amount)
{
  /* processes a literal string component of a URL
     special characters '{' and '[' branch to set/range processing functions
   */ 
  char* buf = glob->glob_buffer;
  int litindex;

  *amount = 1; /* default is one single string */

  while (*pattern != '\0' && *pattern != '{' && *pattern != '[') {
    if (*pattern == '}' || *pattern == ']') {
      return GLOB_ERROR;
    }
    if (*pattern == '\\') {		/* escape character, skip '\' */
      ++pattern;
      ++pos;
      if (*pattern == '\0') {		/* but no escaping of '\0'! */
	return GLOB_ERROR;
      }
    }
    *buf++ = *pattern++;		/* copy character to literal */
    ++pos;
  }
  *buf = '\0';
  litindex = glob->size / 2;
  /* literals 0,1,2,... correspond to size=0,2,4,... */
  glob->literal[litindex] = strdup(glob->glob_buffer);
  ++glob->size;

  switch (*pattern) {
  case '\0':
    return GLOB_OK;			/* singular URL processed  */

  case '{':
    /* process set pattern */
    return glob_set(glob, ++pattern, ++pos, amount);

  case '[':
    /* process range pattern */
    return glob_range(glob, ++pattern, ++pos, amount);
  }

  return GLOB_ERROR; /* something got wrong */
}