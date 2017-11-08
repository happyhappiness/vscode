int ProcessRequest(char *request)
{
  char *line=request;
  unsigned long contentlength=0;
  char chunked=FALSE;

#define END_OF_HEADERS "\r\n\r\n"

  char *end;
  end = strstr(request, END_OF_HEADERS);

  if(!end)
    /* we don't have a complete request yet! */
    return 0;

  /* **** Persistancy ****
   *
   * If the request is a HTTP/1.0 one, we close the connection unconditionally
   * when we're done.
   *
   * If the request is a HTTP/1.1 one, we MUST check for a "Connection:"
   * header that might say "close". If it does, we close a connection when
   * this request is processed. Otherwise, we keep the connection alive for X
   * seconds.
   */

  do {
    if(!strncasecmp("Content-Length:", line, 15)) {
      contentlength = strtol(line+15, &line, 10);
      break;
    }
    else if(!strncasecmp("Transfer-Encoding: chunked", line,
                         strlen("Transfer-Encoding: chunked"))) {
      /* chunked data coming in */
      chunked = TRUE;
    }

    if(chunked) {
      if(strstr(request, "\r\n0\r\n"))
        /* end of chunks reached */
        return 1; /* done */
      else
        return 0; /* not done */
    }

    line = strchr(line, '\n');
    if(line)
      line++;
  } while(line);

  if(contentlength > 0 ) {
    if(contentlength <= strlen(end+strlen(END_OF_HEADERS)))
      return 1; /* done */
    else
      return 0; /* not complete yet */
  }
  return 1; /* done */
}