static GlobCode glob_set(URLGlob *glob, char *pattern,
                         size_t pos, int *amount)
{
  /* processes a set expression with the point behind the opening '{'
     ','-separated elements are collected until the next closing '}'
  */
  char* buf = glob->glob_buffer;
  URLPattern *pat;

  pat = (URLPattern*)&glob->pattern[glob->size / 2];
  /* patterns 0,1,2,... correspond to size=1,3,5,... */
  pat->type = UPTSet;
  pat->content.Set.size = 0;
  pat->content.Set.ptr_s = 0;
  pat->content.Set.elements = (char**)malloc(0);
  ++glob->size;

  while (1) {
    bool skip;

    switch (*pattern) {
    case '\0':                  /* URL ended while set was still open */
      snprintf(glob->errormsg, sizeof(glob->errormsg),
               "unmatched brace at pos %d\n", (int)pos);
      return GLOB_ERROR;

    case '{':
    case '[':                   /* no nested expressions at this time */
      snprintf(glob->errormsg, sizeof(glob->errormsg),
               "nested braces not supported at pos %d\n", (int)pos);
      return GLOB_ERROR;

    case ',':
    case '}':                           /* set element completed */
      *buf = '\0';
      pat->content.Set.elements =
        realloc(pat->content.Set.elements,
                (pat->content.Set.size + 1) * sizeof(char*));
      if (!pat->content.Set.elements) {
        snprintf(glob->errormsg, sizeof(glob->errormsg), "out of memory");
        return GLOB_ERROR;
      }
      pat->content.Set.elements[pat->content.Set.size] =
        strdup(glob->glob_buffer);
      ++pat->content.Set.size;

      if (*pattern == '}') {
        /* entire set pattern completed */
        int wordamount;

        /* always check for a literal (may be "") between patterns */
        if(GLOB_ERROR == glob_word(glob, ++pattern, ++pos, &wordamount))
          wordamount=1;
        *amount = pat->content.Set.size * wordamount;

        return GLOB_OK;
      }

      buf = glob->glob_buffer;
      ++pattern;
      ++pos;
      break;

    case ']':                           /* illegal closing bracket */
      snprintf(glob->errormsg, sizeof(glob->errormsg),
               "illegal pattern at pos %d\n", (int)pos);
      return GLOB_ERROR;

    case '\\':                          /* escaped character, skip '\' */
      switch(pattern[1]) {
      case '[':
      case ']':
      case '{':
      case '}':
      case ',':
        skip = TRUE;
        break;
      default:
        skip = FALSE;
        break;
      }
      if(skip) {
        if (*(buf+1) == '\0') {           /* but no escaping of '\0'! */
          snprintf(glob->errormsg, sizeof(glob->errormsg),
                   "illegal pattern at pos %d\n", (int)pos);
          return GLOB_ERROR;
        }
        ++pattern;
        ++pos;
      }
      /* intentional fallthrough */
    default:
      *buf++ = *pattern++;              /* copy character to set element */
      ++pos;
    }
  }
  /* we never reach this point */
}