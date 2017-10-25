int glob_word(char *pattern, int pos) {
  /* processes a literal string component of a URL
     special characters '{' and '[' branch to set/range processing functions
   */ 
  char* buf = glob_buffer;
  int litindex;

  while (*pattern != '\0' && *pattern != '{' && *pattern != '[') {
    if (*pattern == '}' || *pattern == ']') {
      printf("illegal character at position %d\n", pos);
      exit (CURLE_URL_MALFORMAT);
    }
    if (*pattern == '\\') {		/* escape character, skip '\' */
      ++pattern;
      ++pos;
      if (*pattern == '\0') {		/* but no escaping of '\0'! */
	printf("illegal character at position %d\n", pos);
	exit (CURLE_URL_MALFORMAT);
      }
    }
    *buf++ = *pattern++;		/* copy character to literal */
    ++pos;
  }
  *buf = '\0';
  litindex = glob_expand->size / 2;
  /* literals 0,1,2,... correspond to size=0,2,4,... */
  glob_expand->literal[litindex] = strdup(glob_buffer);
  ++glob_expand->size;
  if (*pattern == '\0')
    return 1;				/* singular URL processed  */
  if (*pattern == '{') {
    return glob_set(++pattern, ++pos);	/* process set pattern */
  }
  if (*pattern == '[') {
    return glob_range(++pattern, ++pos);/* process range pattern */
  }
  printf("internal error\n");
  exit (CURLE_FAILED_INIT);
}