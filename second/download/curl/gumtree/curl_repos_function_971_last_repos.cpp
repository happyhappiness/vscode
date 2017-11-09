static char *get_param_word(char **str, char **end_pos)
{
  char *ptr = *str;
  char *word_begin = NULL;
  char *ptr2;
  char *escape = NULL;
  const char *end_chars = ";,";

  /* the first non-space char is here */
  word_begin = ptr;
  if(*ptr == '"') {
    ++ptr;
    while(*ptr) {
      if(*ptr == '\\') {
        if(ptr[1] == '\\' || ptr[1] == '"') {
          /* remember the first escape position */
          if(!escape)
            escape = ptr;
          /* skip escape of back-slash or double-quote */
          ptr += 2;
          continue;
        }
      }
      if(*ptr == '"') {
        *end_pos = ptr;
        if(escape) {
          /* has escape, we restore the unescaped string here */
          ptr = ptr2 = escape;
          do {
            if(*ptr == '\\' && (ptr[1] == '\\' || ptr[1] == '"'))
              ++ptr;
            *ptr2++ = *ptr++;
          }
          while(ptr < *end_pos);
          *end_pos = ptr2;
        }
        while(*ptr && NULL == strchr(end_chars, *ptr))
          ++ptr;
        *str = ptr;
        return word_begin + 1;
      }
      ++ptr;
    }
    /* end quote is missing, treat it as non-quoted. */
    ptr = word_begin;
  }

  while(*ptr && NULL == strchr(end_chars, *ptr))
    ++ptr;
  *str = *end_pos = ptr;
  return word_begin;
}