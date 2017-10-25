struct CookieInfo *cookie_init(char *file)
{
  char line[MAX_COOKIE_LINE];
  struct CookieInfo *c;
  FILE *fp;
  bool fromfile=TRUE;
  
  c = (struct CookieInfo *)malloc(sizeof(struct CookieInfo));
  if(!c)
    return NULL; /* failed to get memory */
  memset(c, 0, sizeof(struct CookieInfo));
  c->filename = strdup(file?file:"none"); /* copy the name just in case */

  if(strequal(file, "-")) {
    fp = stdin;
    fromfile=FALSE;
  }
  else
    fp = file?fopen(file, "r"):NULL;

  if(fp) {
    while(fgets(line, MAX_COOKIE_LINE, fp)) {
      if(strnequal("Set-Cookie:", line, 11)) {
        /* This is a cookie line, get it! */
        char *lineptr=&line[11];
        while(*lineptr && isspace((int)*lineptr))
          lineptr++;

        cookie_add(c, TRUE, lineptr);
      }
      else {
        /* This might be a netscape cookie-file line, get it! */
        char *lineptr=line;
        while(*lineptr && isspace((int)*lineptr))
          lineptr++;

        cookie_add(c, FALSE, lineptr);
      }
    }
    if(fromfile)
      fclose(fp);
  }

  return c;
}