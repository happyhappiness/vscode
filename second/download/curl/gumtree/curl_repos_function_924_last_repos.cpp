static char *c_escape(const char *str, size_t len)
{
  const char *s;
  unsigned char c;
  char *escaped, *e;

  if(len == CURL_ZERO_TERMINATED)
    len = strlen(str);

  /* Check for possible overflow. */
  if(len > (~(size_t) 0) / 4)
    return NULL;

  /* Allocate space based on worst-case */
  escaped = malloc(4 * len + 1);
  if(!escaped)
    return NULL;

  e = escaped;
  for(s = str; (c = *s) != '\0'; s++) {
    if(c == '\n') {
      strcpy(e, "\\n");
      e += 2;
    }
    else if(c == '\r') {
      strcpy(e, "\\r");
      e += 2;
    }
    else if(c == '\t') {
      strcpy(e, "\\t");
      e += 2;
    }
    else if(c == '\\') {
      strcpy(e, "\\\\");
      e += 2;
    }
    else if(c == '"') {
      strcpy(e, "\\\"");
      e += 2;
    }
    else if(! isprint(c)) {
      snprintf(e, 5, "\\%03o", (unsigned)c);
      e += 4;
    }
    else
      *e++ = c;
  }
  *e = '\0';
  return escaped;
}