int glob_set(char *pattern, int pos) {
  /* processes a set expression with the point behind the opening '{'
     ','-separated elements are collected until the next closing '}'
  */
  char* buf = glob_buffer;
  URLPattern *pat;

  pat = (URLPattern*)&glob_expand->pattern[glob_expand->size / 2];
  /* patterns 0,1,2,... correspond to size=1,3,5,... */
  pat->type = UPTSet;
  pat->content.Set.size = 0;
  pat->content.Set.ptr_s = 0;
  pat->content.Set.elements = (char**)malloc(0);
  ++glob_expand->size;

  while (1) {
    switch (*pattern) {
    case '\0':				/* URL ended while set was still open */
      printf("error: unmatched brace at pos %d\n", pos);
      exit (CURLE_URL_MALFORMAT);
    case '{':
    case '[':				/* no nested expressions at this time */
      printf("error: nested braces not supported %d\n", pos);
      exit (CURLE_URL_MALFORMAT);
    case ',':
    case '}':				/* set element completed */
      *buf = '\0';
      pat->content.Set.elements = realloc(pat->content.Set.elements, (pat->content.Set.size + 1) * sizeof(char*));
      if (!pat->content.Set.elements) {
	printf("out of memory in set pattern\n");
	exit(CURLE_OUT_OF_MEMORY);
      }
      pat->content.Set.elements[pat->content.Set.size] = strdup(glob_buffer);
      ++pat->content.Set.size;

      if (*pattern == '}')		/* entire set pattern completed */
	/* always check for a literal (may be "") between patterns */
	return pat->content.Set.size * glob_word(++pattern, ++pos);

      buf = glob_buffer;
      ++pattern;
      ++pos;
      break;
    case ']':				/* illegal closing bracket */
      printf("error: illegal pattern at pos %d\n", pos);
      exit (CURLE_URL_MALFORMAT);
    case '\\':				/* escaped character, skip '\' */
      if (*(buf+1) == '\0') {		/* but no escaping of '\0'! */
	printf("error: illegal pattern at pos %d\n", pos);
	exit (CURLE_URL_MALFORMAT);
      }
      ++pattern;
      ++pos;				/* intentional fallthrough */
    default:
      *buf++ = *pattern++;		/* copy character to set element */
      ++pos;
    }
  }
  exit (CURLE_FAILED_INIT);
}