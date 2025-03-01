static char *get_line(char *buf, int len, FILE *input)
{
  bool partial = FALSE;
  while(1) {
    char *b = fgets(buf, len, input);
    if(b) {
      size_t rlen = strlen(b);
      if(rlen && (b[rlen-1] == '\n')) {
        if(partial) {
          partial = FALSE;
          continue;
        }
        return b;
      }
      /* read a partial, discard the next piece that ends with newline */
      partial = TRUE;
    }
    else
      break;
  }
  return NULL;
}