static CURLcode file_upload(struct connectdata *conn)
{
  struct FILEPROTO *file = conn->data->state.proto.file;
  const char *dir = strchr(file->path, DIRSEP);
  FILE *fp;
  CURLcode res=CURLE_OK;
  struct SessionHandle *data = conn->data;
  char *buf = data->state.buffer;
  size_t nread;
  size_t nwrite;
  curl_off_t bytecount = 0;
  struct timeval now = Curl_tvnow();
  struct_stat file_stat;
  const char* buf2;

  /*
   * Since FILE: doesn't do the full init, we need to provide some extra
   * assignments here.
   */
  conn->fread_func = data->set.fread_func;
  conn->fread_in = data->set.in;
  conn->data->req.upload_fromhere = buf;

  if(!dir)
    return CURLE_FILE_COULDNT_READ_FILE; /* fix: better error code */

  if(!dir[1])
     return CURLE_FILE_COULDNT_READ_FILE; /* fix: better error code */

  if(data->state.resume_from)
    fp = fopen( file->path, "ab" );
  else {
    int fd;

#if defined(WIN32) || defined(MSDOS) || defined(__EMX__)
    fd = open(file->path, O_WRONLY|O_CREAT|O_TRUNC|O_BINARY,
              conn->data->set.new_file_perms);
#else /* !(WIN32 || MSDOS || __EMX__) */
    fd = open(file->path, O_WRONLY|O_CREAT|O_TRUNC,
              conn->data->set.new_file_perms);
#endif /* !(WIN32 || MSDOS || __EMX__) */
    if(fd < 0) {
      failf(data, "Can't open %s for writing", file->path);
      return CURLE_WRITE_ERROR;
    }
    fp = fdopen(fd, "wb");
  }

  if(!fp) {
    failf(data, "Can't open %s for writing", file->path);
    return CURLE_WRITE_ERROR;
  }

  if(-1 != data->set.infilesize)
    /* known size of data to "upload" */
    Curl_pgrsSetUploadSize(data, data->set.infilesize);

  /* treat the negative resume offset value as the case of "-" */
  if(data->state.resume_from < 0) {
    if(stat(file->path, &file_stat)) {
      fclose(fp);
      failf(data, "Can't get the size of %s", file->path);
      return CURLE_WRITE_ERROR;
    }
    else
      data->state.resume_from = (curl_off_t)file_stat.st_size;
  }

  while(res == CURLE_OK) {
    int readcount;
    res = Curl_fillreadbuffer(conn, BUFSIZE, &readcount);
    if(res)
      break;

    if(readcount <= 0)  /* fix questionable compare error. curlvms */
      break;

    nread = (size_t)readcount;

    /*skip bytes before resume point*/
    if(data->state.resume_from) {
      if( (curl_off_t)nread <= data->state.resume_from ) {
        data->state.resume_from -= nread;
        nread = 0;
        buf2 = buf;
      }
      else {
        buf2 = buf + data->state.resume_from;
        nread -= (size_t)data->state.resume_from;
        data->state.resume_from = 0;
      }
    }
    else
      buf2 = buf;

    /* write the data to the target */
    nwrite = fwrite(buf2, 1, nread, fp);
    if(nwrite != nread) {
      res = CURLE_SEND_ERROR;
      break;
    }

    bytecount += nread;

    Curl_pgrsSetUploadCounter(data, bytecount);

    if(Curl_pgrsUpdate(conn))
      res = CURLE_ABORTED_BY_CALLBACK;
    else
      res = Curl_speedcheck(data, now);
  }
  if(!res && Curl_pgrsUpdate(conn))
    res = CURLE_ABORTED_BY_CALLBACK;

  fclose(fp);

  return res;
}