static int read_field_headers(struct OperationConfig *config,
                              const char *filename, FILE *fp,
                              struct curl_slist **pheaders)
{
  size_t hdrlen = 0;
  size_t pos = 0;
  int c;
  bool incomment = FALSE;
  int lineno = 1;
  char hdrbuf[999]; /* Max. header length + 1. */

  for(;;) {
    c = getc(fp);
    if(c == EOF || (!pos && !ISSPACE(c))) {
      /* Strip and flush the current header. */
      while(hdrlen && ISSPACE(hdrbuf[hdrlen - 1]))
        hdrlen--;
      if(hdrlen) {
        hdrbuf[hdrlen] = '\0';
        if(slist_append(pheaders, hdrbuf)) {
          fprintf(config->global->errors,
                  "Out of memory for field headers!\n");
          return -1;
        }
        hdrlen = 0;
      }
    }

    switch(c) {
    case EOF:
      if(ferror(fp)) {
        fprintf(config->global->errors,
                "Header file %s read error: %s\n", filename, strerror(errno));
        return -1;
      }
      return 0;    /* Done. */
    case '\r':
      continue;    /* Ignore. */
    case '\n':
      pos = 0;
      incomment = FALSE;
      lineno++;
      continue;
    case '#':
      if(!pos)
        incomment = TRUE;
      break;
    }

    pos++;
    if(!incomment) {
      if(hdrlen == sizeof hdrbuf - 1) {
        warnf(config->global, "File %s line %d: header too long (truncated)\n",
              filename, lineno);
        c = ' ';
      }
      if(hdrlen <= sizeof hdrbuf - 1)
        hdrbuf[hdrlen++] = (char) c;
    }
  }
  /* NOTREACHED */
}