CURLcode Curl_ftp(struct connectdata *conn)
{
  CURLcode retcode;

  struct SessionHandle *data = conn->data;
  struct FTP *ftp;
  int dirlength=0; /* 0 forces strlen() */

  /* the ftp struct is already inited in ftp_connect() */
  ftp = conn->proto.ftp;

  /* We split the path into dir and file parts *before* we URLdecode
     it */
  ftp->file = strrchr(conn->ppath, '/');
  if(ftp->file) {
    if(ftp->file != conn->ppath)
      dirlength=ftp->file-conn->ppath; /* don't count the traling slash */

    ftp->file++; /* point to the first letter in the file name part or
                    remain NULL */
  }
  else {
    ftp->file = conn->ppath; /* there's only a file part */
  }

  if(*ftp->file) {
    ftp->file = curl_unescape(ftp->file, 0);
    if(NULL == ftp->file) {
      failf(data, "no memory");
      return CURLE_OUT_OF_MEMORY;
    }
  }
  else
    ftp->file=NULL; /* instead of point to a zero byte, we make it a NULL
                       pointer */

  ftp->urlpath = conn->ppath;
  if(dirlength) {
    ftp->dir = curl_unescape(ftp->urlpath, dirlength);
    if(NULL == ftp->dir) {
      if(ftp->file)
        free(ftp->file);
      failf(data, "no memory");
      return CURLE_OUT_OF_MEMORY; /* failure */
    }
  }
  else
    ftp->dir = NULL;

  retcode = _ftp(conn);

  /* clean up here, success or error doesn't matter */
  if(ftp->file)
    free(ftp->file);
  if(ftp->dir)
    free(ftp->dir);

  ftp->file = ftp->dir = NULL; /* zero */

  return retcode;
}