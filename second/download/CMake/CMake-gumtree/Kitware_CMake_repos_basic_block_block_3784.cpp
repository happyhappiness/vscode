{
    char *lineptr;
    bool headerline;

    line = malloc(MAX_COOKIE_LINE);
    if(!line)
      goto fail;
    while(get_line(line, MAX_COOKIE_LINE, fp)) {
      if(checkprefix("Set-Cookie:", line)) {
        /* This is a cookie line, get it! */
        lineptr=&line[11];
        headerline=TRUE;
      }
      else {
        lineptr=line;
        headerline=FALSE;
      }
      while(*lineptr && ISBLANK(*lineptr))
        lineptr++;

      Curl_cookie_add(data, c, headerline, lineptr, NULL, NULL);
    }
    free(line); /* free the line buffer */

    if(fromfile)
      fclose(fp);
  }