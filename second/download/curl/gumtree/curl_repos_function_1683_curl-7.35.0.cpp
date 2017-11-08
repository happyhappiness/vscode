static
CURLcode ftp_parse_url_path(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  /* the ftp struct is already inited in ftp_connect() */
  struct FTP *ftp = data->req.protop;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  const char *slash_pos;  /* position of the first '/' char in curpos */
  const char *path_to_use = data->state.path;
  const char *cur_pos;
  const char *filename = NULL;

  cur_pos = path_to_use; /* current position in path. point at the begin
                            of next path component */

  ftpc->ctl_valid = FALSE;
  ftpc->cwdfail = FALSE;

  switch(data->set.ftp_filemethod) {
  case FTPFILE_NOCWD:
    /* fastest, but less standard-compliant */

    /*
      The best time to check whether the path is a file or directory is right
      here. so:

      the first condition in the if() right here, is there just in case
      someone decides to set path to NULL one day
   */
    if(data->state.path &&
       data->state.path[0] &&
       (data->state.path[strlen(data->state.path) - 1] != '/') )
      filename = data->state.path;  /* this is a full file path */
      /*
        ftpc->file is not used anywhere other than for operations on a file.
        In other words, never for directory operations.
        So we can safely leave filename as NULL here and use it as a
        argument in dir/file decisions.
      */
    break;

  case FTPFILE_SINGLECWD:
    /* get the last slash */
    if(!path_to_use[0]) {
      /* no dir, no file */
      ftpc->dirdepth = 0;
      break;
    }
    slash_pos=strrchr(cur_pos, '/');
    if(slash_pos || !*cur_pos) {
      size_t dirlen = slash_pos-cur_pos;

      ftpc->dirs = calloc(1, sizeof(ftpc->dirs[0]));
      if(!ftpc->dirs)
        return CURLE_OUT_OF_MEMORY;

      if(!dirlen)
        dirlen++;

      ftpc->dirs[0] = curl_easy_unescape(conn->data, slash_pos ? cur_pos : "/",
                                         slash_pos ? curlx_uztosi(dirlen) : 1,
                                         NULL);
      if(!ftpc->dirs[0]) {
        freedirs(ftpc);
        return CURLE_OUT_OF_MEMORY;
      }
      ftpc->dirdepth = 1; /* we consider it to be a single dir */
      filename = slash_pos ? slash_pos+1 : cur_pos; /* rest is file name */
    }
    else
      filename = cur_pos;  /* this is a file name only */
    break;

  default: /* allow pretty much anything */
  case FTPFILE_MULTICWD:
    ftpc->dirdepth = 0;
    ftpc->diralloc = 5; /* default dir depth to allocate */
    ftpc->dirs = calloc(ftpc->diralloc, sizeof(ftpc->dirs[0]));
    if(!ftpc->dirs)
      return CURLE_OUT_OF_MEMORY;

    /* we have a special case for listing the root dir only */
    if(strequal(path_to_use, "/")) {
      cur_pos++; /* make it point to the zero byte */
      ftpc->dirs[0] = strdup("/");
      ftpc->dirdepth++;
    }
    else {
      /* parse the URL path into separate path components */
      while((slash_pos = strchr(cur_pos, '/')) != NULL) {
        /* 1 or 0 pointer offset to indicate absolute directory */
        ssize_t absolute_dir = ((cur_pos - data->state.path > 0) &&
                                (ftpc->dirdepth == 0))?1:0;

        /* seek out the next path component */
        if(slash_pos-cur_pos) {
          /* we skip empty path components, like "x//y" since the FTP command
             CWD requires a parameter and a non-existent parameter a) doesn't
             work on many servers and b) has no effect on the others. */
          int len = curlx_sztosi(slash_pos - cur_pos + absolute_dir);
          ftpc->dirs[ftpc->dirdepth] =
            curl_easy_unescape(conn->data, cur_pos - absolute_dir, len, NULL);
          if(!ftpc->dirs[ftpc->dirdepth]) { /* run out of memory ... */
            failf(data, "no memory");
            freedirs(ftpc);
            return CURLE_OUT_OF_MEMORY;
          }
          if(isBadFtpString(ftpc->dirs[ftpc->dirdepth])) {
            free(ftpc->dirs[ftpc->dirdepth]);
            freedirs(ftpc);
            return CURLE_URL_MALFORMAT;
          }
        }
        else {
          cur_pos = slash_pos + 1; /* jump to the rest of the string */
          if(!ftpc->dirdepth) {
            /* path starts with a slash, add that as a directory */
            ftpc->dirs[ftpc->dirdepth] = strdup("/");
            if(!ftpc->dirs[ftpc->dirdepth++]) { /* run out of memory ... */
              failf(data, "no memory");
              freedirs(ftpc);
              return CURLE_OUT_OF_MEMORY;
            }
          }
          continue;
        }

        cur_pos = slash_pos + 1; /* jump to the rest of the string */
        if(++ftpc->dirdepth >= ftpc->diralloc) {
          /* enlarge array */
          char **bigger;
          ftpc->diralloc *= 2; /* double the size each time */
          bigger = realloc(ftpc->dirs, ftpc->diralloc * sizeof(ftpc->dirs[0]));
          if(!bigger) {
            freedirs(ftpc);
            return CURLE_OUT_OF_MEMORY;
          }
          ftpc->dirs = bigger;
        }
      }
    }
    filename = cur_pos;  /* the rest is the file name */
    break;
  } /* switch */

  if(filename && *filename) {
    ftpc->file = curl_easy_unescape(conn->data, filename, 0, NULL);
    if(NULL == ftpc->file) {
      freedirs(ftpc);
      failf(data, "no memory");
      return CURLE_OUT_OF_MEMORY;
    }
    if(isBadFtpString(ftpc->file)) {
      freedirs(ftpc);
      return CURLE_URL_MALFORMAT;
    }
  }
  else
    ftpc->file=NULL; /* instead of point to a zero byte, we make it a NULL
                       pointer */

  if(data->set.upload && !ftpc->file && (ftp->transfer == FTPTRANSFER_BODY)) {
    /* We need a file name when uploading. Return error! */
    failf(data, "Uploading to a URL without a file name!");
    return CURLE_URL_MALFORMAT;
  }

  ftpc->cwddone = FALSE; /* default to not done */

  if(ftpc->prevpath) {
    /* prevpath is "raw" so we convert the input path before we compare the
       strings */
    int dlen;
    char *path = curl_easy_unescape(conn->data, data->state.path, 0, &dlen);
    if(!path) {
      freedirs(ftpc);
      return CURLE_OUT_OF_MEMORY;
    }

    dlen -= ftpc->file?curlx_uztosi(strlen(ftpc->file)):0;
    if((dlen == curlx_uztosi(strlen(ftpc->prevpath))) &&
       strnequal(path, ftpc->prevpath, dlen)) {
      infof(data, "Request has same path as previous transfer\n");
      ftpc->cwddone = TRUE;
    }
    free(path);
  }

  return CURLE_OK;
}