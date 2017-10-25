static CURLcode file_upload(struct connectdata *conn)
{
  struct FILEPROTO *file = conn->proto.file;
  char *dir = strchr(file->path, DIRSEP);
  FILE *fp;
  CURLcode res=CURLE_OK;
  struct SessionHandle *data = conn->data;
  char *buf = data->state.buffer;
  size_t nread;
  size_t nwrite;
  curl_off_t bytecount = 0;
  struct timeval now = Curl_tvnow();

  /*
   * Since FILE: doesn't do the full init, we need to provide some extra
   * assignments here.
   */
  conn->fread = data->set.fread;
  conn->fread_in = data->set.in;
  conn->upload_fromhere = buf;

  if(!dir)
    return CURLE_FILE_COULDNT_READ_FILE; /* fix: better error code */

  if(!dir[1])
     return CURLE_FILE_COULDNT_READ_FILE; /* fix: better error code */

  fp = fopen(file->path, "wb");
  if(!fp) {
    failf(data, "Can't open %s for writing", file->path);
    return CURLE_WRITE_ERROR;
  }

  if(-1 != data->set.infilesize)
    /* known size of data to "upload" */
    Curl_pgrsSetUploadSize(data, data->set.infilesize);

  while (res == CURLE_OK) {
    int readcount;
    res = Curl_fillreadbuffer(conn, BUFSIZE, &readcount);
    if(res)
      break;

    nread = (size_t)readcount;

    if (nread <= 0)
      break;

    /* write the data to the target */
    nwrite = fwrite(buf, 1, nread, fp);
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