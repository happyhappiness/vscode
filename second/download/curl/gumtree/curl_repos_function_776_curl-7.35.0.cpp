static GlobCode glob_set(URLGlob *glob, char **patternp,
                         size_t *posp, unsigned long *amount,
                         int globindex)
{
  /* processes a set expression with the point behind the opening '{'
     ','-separated elements are collected until the next closing '}'
  */
  URLPattern *pat;
  bool done = FALSE;
  char *buf = glob->glob_buffer;
  char *pattern = *patternp;
  char *opattern = pattern;
  size_t opos = *posp-1;

  pat = &glob->pattern[glob->size];
  /* patterns 0,1,2,... correspond to size=1,3,5,... */
  pat->type = UPTSet;
  pat->content.Set.size = 0;
  pat->content.Set.ptr_s = 0;
  pat->content.Set.elements = NULL;
  pat->globindex = globindex;

  while(!done) {
    switch (*pattern) {
    case '\0':                  /* URL ended while set was still open */
      return GLOBERROR("unmatched brace", opos, GLOB_ERROR);

    case '{':
    case '[':                   /* no nested expressions at this time */
      return GLOBERROR("nested brace", *posp, GLOB_ERROR);

    case '}':                           /* set element completed */
      if(opattern == pattern)
        return GLOBERROR("empty string within braces", *posp, GLOB_ERROR);

      /* add 1 to size since it'll be incremented below */
      if(multiply(amount, pat->content.Set.size+1))
        return GLOBERROR("range overflow", 0, GLOB_ERROR);

      /* fall-through */
    case ',':

      *buf = '\0';
      if(pat->content.Set.elements) {
        char **new_arr = realloc(pat->content.Set.elements,
                                 (pat->content.Set.size + 1) * sizeof(char*));
        if(!new_arr)
          return GLOBERROR("out of memory", 0, GLOB_NO_MEM);

        pat->content.Set.elements = new_arr;
      }
      else
        pat->content.Set.elements = malloc(sizeof(char*));

      if(!pat->content.Set.elements)
        return GLOBERROR("out of memory", 0, GLOB_NO_MEM);

      pat->content.Set.elements[pat->content.Set.size] =
        strdup(glob->glob_buffer);
      if(!pat->content.Set.elements[pat->content.Set.size])
        return GLOBERROR("out of memory", 0, GLOB_NO_MEM);
      ++pat->content.Set.size;

      if(*pattern == '}') {
        pattern++; /* pass the closing brace */
        done = TRUE;
        continue;
      }

      buf = glob->glob_buffer;
      ++pattern;
      ++(*posp);
      break;

    case ']':                           /* illegal closing bracket */
      return GLOBERROR("unexpected close bracket", *posp, GLOB_ERROR);

    case '\\':                          /* escaped character, skip '\' */
      if(pattern[1]) {
        ++pattern;
        ++(*posp);
      }
      /* intentional fallthrough */
    default:
      *buf++ = *pattern++;              /* copy character to set element */
      ++(*posp);
    }
  }

  *patternp = pattern; /* return with the new position */
  return GLOB_OK;
}