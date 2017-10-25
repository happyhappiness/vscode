int glob_range(char *pattern, int pos) {
  /* processes a range expression with the point behind the opening '['
     - char range: e.g. "a-z]", "B-Q]"
     - num range: e.g. "0-9]", "17-2000]"
     - num range with leading zeros: e.g. "001-999]"
     expression is checked for well-formedness and collected until the next ']'
  */
  URLPattern *pat;
  char *c;
  
  pat = (URLPattern*)&glob_expand->pattern[glob_expand->size / 2];
  /* patterns 0,1,2,... correspond to size=1,3,5,... */
  ++glob_expand->size;

  if (isalpha((int)*pattern)) {		/* character range detected */
    pat->type = UPTCharRange;
    if (sscanf(pattern, "%c-%c]", &pat->content.CharRange.min_c, &pat->content.CharRange.max_c) != 2 ||
	pat->content.CharRange.min_c >= pat->content.CharRange.max_c ||
	pat->content.CharRange.max_c - pat->content.CharRange.min_c > 'z' - 'a') {
      /* the pattern is not well-formed */ 
      printf("error: illegal pattern or range specification after pos %d\n", pos);
      exit (CURLE_URL_MALFORMAT);
    }
    pat->content.CharRange.ptr_c = pat->content.CharRange.min_c;
    /* always check for a literal (may be "") between patterns */
    return (pat->content.CharRange.max_c - pat->content.CharRange.min_c + 1) *
      glob_word(pattern + 4, pos + 4);
  }
  if (isdigit((int)*pattern)) {		/* numeric range detected */
    pat->type = UPTNumRange;
    pat->content.NumRange.padlength = 0;
    if (sscanf(pattern, "%d-%d]", &pat->content.NumRange.min_n, &pat->content.NumRange.max_n) != 2 ||
	pat->content.NumRange.min_n >= pat->content.NumRange.max_n) {
      /* the pattern is not well-formed */ 
      printf("error: illegal pattern or range specification after pos %d\n", pos);
      exit (CURLE_URL_MALFORMAT);
    }
    if (*pattern == '0') {		/* leading zero specified */
      c = pattern;  
      while (isdigit((int)*c++))
	++pat->content.NumRange.padlength;	/* padding length is set for all instances
						   of this pattern */
    }
    pat->content.NumRange.ptr_n = pat->content.NumRange.min_n;
    c = (char*)(strchr(pattern, ']') + 1);	/* continue after next ']' */
    /* always check for a literal (may be "") between patterns */
    return (pat->content.NumRange.max_n - pat->content.NumRange.min_n + 1) *
      glob_word(c, pos + (c - pattern));
  }
  printf("error: illegal character in range specification at pos %d\n", pos);
  exit (CURLE_URL_MALFORMAT);
}