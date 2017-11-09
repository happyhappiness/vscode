static
CURLcode ftp_parse_url_path(struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;
  /* the ftp struct is already inited in ftp_connect() */
  struct FTP *ftp = data->req.protop;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  const char *slash_pos;  /* position of the first '/' char in curpos */
  const char *path_to_use = data->state.path;
  const char *cur_pos;
  const char *filename = NULL;

  cur_pos = path_to_use; /* current position in path. point at the begin of
                            next path component */

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
    if(path_to_use[0] &&
       (path_to_use[strlen(path_to_use) - 1] != '/') )
      filename = path_to_use;  /* this is a full file path */
    /*
      else {
        ftpc->file is not used anywhere other than for operations on a file.
        In other words, never for directory operations.
        So we can safely leave filename as NULL here and use it as a
        argument in dir/file decisions.
      }
    */
    break;

  case FTPFILE_SINGLECWD:
    /* get the last slash */
    if(!path_to_use[0]) {
      /* no dir, no file */
      ftpc->dirdepth = 0;
      break;
    }
    slash_pos = strrchr(cur_pos, '/');
    if(slash_pos || !*cur_pos) {
      size_t dirlen = slash_pos-cur_pos;
      CURLcode result;

      ftpc->dirs = calloc(1, sizeof(ftpc->dirs[0]));
      if(!ftpc->dirs)
        return CURLE_OUT_OF_MEMORY;

      if(!dirlen)
        dirlen++;

      result = Curl_urldecode(conn->data, slash_pos ? cur_pos : "/",
                              slash_pos ? dirlen : 1,
                              &ftpc->dirs[0], NULL,
                              FALSE);
      if(result) {
        freedirs(ftpc);
        return result;
      }
      ftpc->dirdepth = 1; /* we consider it to be a single dir */
      filename = slash_pos ? slash_pos + 1 : cur_pos; /* rest is file name */
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
    if(!strcmp(path_to_use, "/")) {
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
          size_t len = slash_pos - cur_pos + absolute_dir;
          CURLcode result =
            Curl_urldecode(conn->data, cur_pos - absolute_dir, len,
                           &ftpc->dirs[ftpc->dirdepth], NULL,
                           TRUE);
          if(result) {
            freedirs(ftpc);
            return result;
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
    CURLcode result =
      Curl_urldecode(conn->data, filename, 0,  &ftpc->file, NULL, TRUE);

    if(result) {
      freedirs(ftpc);
      return result;
    }
  }
  else
    ftpc->file = NULL; /* instead of point to a zero byte, we make it a NULL
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
    size_t dlen;
    char *path;
    CURLcode result =
      Curl_urldecode(conn->data, data->state.path, 0, &path, &dlen, FALSE);
    if(result) {
      freedirs(ftpc);
      return result;
    }

    dlen -= ftpc->file?strlen(ftpc->file):0;
    if((dlen == strlen(ftpc->prevpath)) &&
       !strncmp(path, ftpc->prevpath, dlen) &&
       (ftpc->prevmethod == data->set.ftp_filemethod)) {
      infof(data, "Request has same path as previous transfer\n");
      ftpc->cwddone = TRUE;
    }
    free(path);
  }

  return CURLE_OK;
}