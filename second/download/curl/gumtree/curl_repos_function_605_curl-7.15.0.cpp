static
CURLcode ftp_parse_url_path(struct connectdata *conn)
{
  CURLcode retcode = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct FTP *ftp;
  size_t dlen;

  char *slash_pos;  /* position of the first '/' char in curpos */
  char *cur_pos = conn->path; /* current position in path. point at the begin
                                 of next path component */

  /* the ftp struct is already inited in ftp_connect() */
  ftp = conn->proto.ftp;
  ftp->ctl_valid = FALSE;

  ftp->dirdepth = 0;
  ftp->diralloc = 5; /* default dir depth to allocate */
  ftp->dirs = (char **)calloc(ftp->diralloc, sizeof(ftp->dirs[0]));
  if(!ftp->dirs)
    return CURLE_OUT_OF_MEMORY;

  /* parse the URL path into separate path components */
  while((slash_pos=strchr(cur_pos, '/'))) {
    /* 1 or 0 to indicate absolute directory */
    bool absolute_dir = (cur_pos - conn->path > 0) && (ftp->dirdepth == 0);

    /* seek out the next path component */
    if (slash_pos-cur_pos) {
      /* we skip empty path components, like "x//y" since the FTP command CWD
         requires a parameter and a non-existant parameter a) doesn't work on
         many servers and b) has no effect on the others. */
      int len = (int)(slash_pos - cur_pos + absolute_dir);
      ftp->dirs[ftp->dirdepth] = curl_unescape(cur_pos - absolute_dir, len);

      if (!ftp->dirs[ftp->dirdepth]) { /* run out of memory ... */
        failf(data, "no memory");
        freedirs(ftp);
        return CURLE_OUT_OF_MEMORY;
      }
      if (isBadFtpString(ftp->dirs[ftp->dirdepth])) {
        freedirs(ftp);
        return CURLE_URL_MALFORMAT;
      }
    }
    else {
      cur_pos = slash_pos + 1; /* jump to the rest of the string */
      continue;
    }

    if(!retcode) {
      cur_pos = slash_pos + 1; /* jump to the rest of the string */
      if(++ftp->dirdepth >= ftp->diralloc) {
        /* enlarge array */
        char *bigger;
        ftp->diralloc *= 2; /* double the size each time */
        bigger = realloc(ftp->dirs, ftp->diralloc * sizeof(ftp->dirs[0]));
        if(!bigger) {
          ftp->dirdepth--;
          freedirs(ftp);
          return CURLE_OUT_OF_MEMORY;
        }
        ftp->dirs = (char **)bigger;
      }
    }
  }

  ftp->file = cur_pos;  /* the rest is the file name */

  if(*ftp->file) {
    ftp->file = curl_unescape(ftp->file, 0);
    if(NULL == ftp->file) {
      freedirs(ftp);
      failf(data, "no memory");
      return CURLE_OUT_OF_MEMORY;
    }
    if (isBadFtpString(ftp->file)) {
      freedirs(ftp);
      return CURLE_URL_MALFORMAT;
    }
  }
  else
    ftp->file=NULL; /* instead of point to a zero byte, we make it a NULL
                       pointer */

  ftp->cwddone = FALSE; /* default to not done */

  if(ftp->prevpath) {
    /* prevpath is "raw" so we convert the input path before we compare the
       strings */
    char *path = curl_unescape(conn->path, 0);
    if(!path)
      return CURLE_OUT_OF_MEMORY;

    dlen = strlen(path) - (ftp->file?strlen(ftp->file):0);
    if((dlen == strlen(ftp->prevpath)) &&
       curl_strnequal(path, ftp->prevpath, dlen)) {
      infof(data, "Request has same path as previous transfer\n");
      ftp->cwddone = TRUE;
    }
    free(path);
  }

  return retcode;
}