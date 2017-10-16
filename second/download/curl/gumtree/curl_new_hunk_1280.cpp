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

/* Append slist item and return -1 if failed. */
static int slist_append(struct curl_slist **plist, const char *data)
{
  struct curl_slist *s = curl_slist_append(*plist, data);

  if(!s)
    return -1;

  *plist = s;
  return 0;
}

/* Read headers from a file and append to list. */
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

static int get_param_part(struct OperationConfig *config, char **str,
                          char **pdata, char **ptype, char **pfilename,
                          char **pencoder, struct curl_slist **pheaders)
{
  char *p = *str;
  char *type = NULL;
  char *filename = NULL;
  char *encoder = NULL;
  char *endpos;
  char *tp;
  char sep;
  char type_major[128] = "";
  char type_minor[128] = "";
  char *endct = NULL;
  struct curl_slist *headers = NULL;

  if(ptype)
    *ptype = NULL;
  if(pfilename)
    *pfilename = NULL;
  if(pheaders)
    *pheaders = NULL;
  if(pencoder)
    *pencoder = NULL;
  while(ISSPACE(*p))
    p++;
  tp = p;
  *pdata = get_param_word(&p, &endpos);
  /* If not quoted, strip trailing spaces. */
  if(*pdata == tp)
    while(endpos > *pdata && ISSPACE(endpos[-1]))
      endpos--;
  sep = *p;
  *endpos = '\0';
  while(sep == ';') {
    while(ISSPACE(*++p))
      ;

    if(!endct && checkprefix("type=", p)) {
      for(p += 5; ISSPACE(*p); p++)
        ;
      /* set type pointer */
      type = p;

      /* verify that this is a fine type specifier */
      if(2 != sscanf(type, "%127[^/ ]/%127[^;, \n]", type_major, type_minor)) {
        warnf(config->global, "Illegally formatted content-type field!\n");
        curl_slist_free_all(headers);
        return -1; /* illegal content-type syntax! */
      }

      /* now point beyond the content-type specifier */
      endpos = type + strlen(type_major) + strlen(type_minor) + 1;
      for(p = endpos; ISSPACE(*p); p++)
        ;
      while(*p && *p != ';' && *p != ',')
        p++;
      endct = p;
      sep = *p;
    }
    else if(checkprefix("filename=", p)) {
      if(endct) {
        *endct = '\0';
        endct = NULL;
      }
      for(p += 9; ISSPACE(*p); p++)
        ;
      tp = p;
      filename = get_param_word(&p, &endpos);
      /* If not quoted, strip trailing spaces. */
      if(filename == tp)
        while(endpos > filename && ISSPACE(endpos[-1]))
          endpos--;
      sep = *p;
      *endpos = '\0';
    }
    else if(checkprefix("headers=", p)) {
      if(endct) {
        *endct = '\0';
        endct = NULL;
      }
      p += 8;
      if(*p == '@' || *p == '<') {
        char *hdrfile;
        FILE *fp;
        /* Read headers from a file. */

        do {
          p++;
        } while(ISSPACE(*p));
        tp = p;
        hdrfile = get_param_word(&p, &endpos);
        /* If not quoted, strip trailing spaces. */
        if(hdrfile == tp)
          while(endpos > hdrfile && ISSPACE(endpos[-1]))
            endpos--;
        sep = *p;
        *endpos = '\0';
        /* TODO: maybe special fopen for VMS? */
        fp = fopen(hdrfile, FOPEN_READTEXT);
        if(!fp)
          warnf(config->global, "Cannot read from %s: %s\n", hdrfile,
                strerror(errno));
        else {
          int i = read_field_headers(config, hdrfile, fp, &headers);

          fclose(fp);
          if(i) {
            curl_slist_free_all(headers);
            return -1;
          }
        }
      }
      else {
        char *hdr;

        while(ISSPACE(*p))
          p++;
        tp = p;
        hdr = get_param_word(&p, &endpos);
        /* If not quoted, strip trailing spaces. */
        if(hdr == tp)
          while(endpos > hdr && ISSPACE(endpos[-1]))
            endpos--;
        sep = *p;
        *endpos = '\0';
        if(slist_append(&headers, hdr)) {
          fprintf(config->global->errors, "Out of memory for field header!\n");
          curl_slist_free_all(headers);
          return -1;
        }
      }
    }
    else if(checkprefix("encoder=", p)) {
      if(endct) {
        *endct = '\0';
        endct = NULL;
      }
      for(p += 8; ISSPACE(*p); p++)
        ;
      tp = p;
      encoder = get_param_word(&p, &endpos);
      /* If not quoted, strip trailing spaces. */
      if(encoder == tp)
        while(endpos > encoder && ISSPACE(endpos[-1]))
          endpos--;
      sep = *p;
      *endpos = '\0';
    }
    else {
      /* unknown prefix, skip to next block */
      char *unknown = get_param_word(&p, &endpos);

      sep = *p;
      if(endct)
        endct = p;
      else {
        *endpos = '\0';
         if(*unknown)
           warnf(config->global, "skip unknown form field: %s\n", unknown);
      }
    }
  }

  /* Terminate and strip content type. */
  if(type) {
    if(!endct)
      endct = type + strlen(type);
    while(endct > type && ISSPACE(endct[-1]))
      endct--;
    *endct = '\0';
  }

  if(ptype)
    *ptype = type;
  else if(type)
    warnf(config->global, "Field content type not allowed here: %s\n", type);

  if(pfilename)
    *pfilename = filename;
  else if(filename)
    warnf(config->global,
          "Field file name not allowed here: %s\n", filename);

  if(pencoder)
    *pencoder = encoder;
  else if(encoder)
    warnf(config->global,
          "Field encoder not allowed here: %s\n", encoder);

  if(pheaders)
    *pheaders = headers;
  else if(headers) {
    warnf(config->global,
          "Field headers not allowed here: %s\n", headers->data);
    curl_slist_free_all(headers);
  }

  *str = p;
  return sep & 0xFF;
}

/* Check if file is "-". If so, use a callback to read OUR stdin (to
 * workaround Windows DLL file handle caveat).
 * Else use curl_mime_filedata(). */
static CURLcode file_or_stdin(curl_mimepart *part, const char *file)
{
  if(strcmp(file, "-"))
    return curl_mime_filedata(part, file);

  return curl_mime_data_cb(part, -1, (curl_read_callback) fread,
                           (curl_seek_callback) fseek, NULL, stdin);
}


/***************************************************************************
 *
 * formparse()
 *
 * Reads a 'name=value' parameter and builds the appropriate linked list.
 *
