struct CookieInfo *Curl_cookie_init(char *file, struct CookieInfo *inc)
{
  char line[MAX_COOKIE_LINE];
  struct CookieInfo *c;
  FILE *fp;
  bool fromfile=TRUE;
  
  if(NULL == inc) {
    /* we didn't get a struct, create one */
    c = (struct CookieInfo *)malloc(sizeof(struct CookieInfo));
    if(!c)
      return NULL; /* failed to get memory */
    memset(c, 0, sizeof(struct CookieInfo));
    c->filename = strdup(file?file:"none"); /* copy the name just in case */
  }
  else {
    /* we got an already existing one, use that */
    c = inc;
  }
  c->running = FALSE; /* this is not running, this is init */

  if(strequal(file, "-")) {
    fp = stdin;
    fromfile=FALSE;
  }
  else
    fp = file?fopen(file, "r"):NULL;

  if(fp) {
    char *lineptr;
    bool headerline;
    while(fgets(line, MAX_COOKIE_LINE, fp)) {
      if(strnequal("Set-Cookie:", line, 11)) {
        /* This is a cookie line, get it! */
        lineptr=&line[11];
        headerline=TRUE;
      }
      else {
        lineptr=line;
        headerline=FALSE;
      }
      while(*lineptr && isspace((int)*lineptr))
        lineptr++;

      Curl_cookie_add(c, headerline, lineptr);
    }
    if(fromfile)
      fclose(fp);
  }

  c->running = TRUE; /* now, we're running */

  return c;
}