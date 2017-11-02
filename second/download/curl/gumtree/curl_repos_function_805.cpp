static char *c_escape(const char *str)
{
  size_t len = 0;
  const char *s;
  unsigned char c;
  char *escaped, *e;
  /* Allocate space based on worst-case */
  len = strlen(str);
  escaped = malloc(4 * len + 1);
  if(!escaped)
    return NULL;

  e = escaped;
  for(s=str; (c=*s) != '\0'; s++) {
    if(c=='\n') {
      strcpy(e, "\\n");
      e += 2;
    }
    else if(c=='\r') {
      strcpy(e, "\\r");
      e += 2;
    }
    else if(c=='\t') {
      strcpy(e, "\\t");
      e += 2;
    }
    else if(c=='\\') {
      strcpy(e, "\\\\");
      e += 2;
    }
    else if(c=='"') {
      strcpy(e, "\\\"");
      e += 2;
    }
    else if(! isprint(c)) {
      snprintf(e, 4, "\\%03o", c);
      e += 4;
    }
    else
      *e++ = c;
  }
  *e = '\0';
  return escaped;
}