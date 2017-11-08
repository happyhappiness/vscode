static CURLcode file_do(struct connectdata *conn, bool *done)
{
  /* This implementation ignores the host name in conformance with
     RFC 1738. Only local files (reachable via the standard file system)
     are supported. This means that files on remotely mounted directories
     (via NFS, Samba, NT sharing) can be accessed through a file:// URL
  */
  CURLcode res = CURLE_OK;
  struct_stat statbuf; /* struct_stat instead of struct stat just to allow the
                          Windows version to have a different struct without
                          having to redefine the simple word 'stat' */
  curl_off_t expected_size=0;
  bool fstated=FALSE;
  ssize_t nread;
  size_t bytestoread;
  struct SessionHandle *data = conn->data;
  char *buf = data->state.buffer;
  curl_off_t bytecount = 0;
  int fd;
  struct timeval now = Curl_tvnow();

  *done = TRUE; /* unconditionally */

  Curl_initinfo(data);
  Curl_pgrsStartNow(data);

  if(data->set.upload)
    return file_upload(conn);

  /* get the fd from the connection phase */
  fd = conn->data->state.proto.file->fd;

  /* VMS: This only works reliable for STREAMLF files */
  if( -1 != fstat(fd, &statbuf)) {
    /* we could stat it, then read out the size */
    expected_size = statbuf.st_size;
    fstated = TRUE;
  }

  /* If we have selected NOBODY and HEADER, it means that we only want file
     information. Which for FILE can't be much more than the file size and
     date. */
  if(data->set.opt_no_body && data->set.include_header && fstated) {
    CURLcode result;
    snprintf(buf, sizeof(data->state.buffer),
             "Content-Length: %" FORMAT_OFF_T "\r\n", expected_size);
    result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
    if(result)
      return result;

    result = Curl_client_write(conn, CLIENTWRITE_BOTH,
                               (char *)"Accept-ranges: bytes\r\n", 0);
    if(result)
      return result;

    if(fstated) {
      const struct tm *tm;
      time_t filetime = (time_t)statbuf.st_mtime;
#ifdef HAVE_GMTIME_R
      struct tm buffer;
      tm = (const struct tm *)gmtime_r(&filetime, &buffer);
#else
      tm = gmtime(&filetime);
#endif
      /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
      snprintf(buf, BUFSIZE-1,
               "Last-Modified: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n",
               Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
               tm->tm_mday,
               Curl_month[tm->tm_mon],
               tm->tm_year + 1900,
               tm->tm_hour,
               tm->tm_min,
               tm->tm_sec);
      result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
    }
    return result;
  }

  /* Check whether file range has been specified */
  file_range(conn);

  /* Adjust the start offset in case we want to get the N last bytes
   * of the stream iff the filesize could be determined */
  if(data->state.resume_from < 0) {
    if(!fstated) {
      failf(data, "Can't get the size of file.");
      return CURLE_READ_ERROR;
    }
    else
      data->state.resume_from += (curl_off_t)statbuf.st_size;
  }

  if(data->state.resume_from <= expected_size)
    expected_size -= data->state.resume_from;
  else {
    failf(data, "failed to resume file:// transfer");
    return CURLE_BAD_DOWNLOAD_RESUME;
  }

  /* A high water mark has been specified so we obey... */
  if (data->req.maxdownload > 0)
    expected_size = data->req.maxdownload;

  if(fstated && (expected_size == 0))
    return CURLE_OK;

  /* The following is a shortcut implementation of file reading
     this is both more efficient than the former call to download() and
     it avoids problems with select() and recv() on file descriptors
     in Winsock */
  if(fstated)
    Curl_pgrsSetDownloadSize(data, expected_size);

  if(data->state.resume_from) {
    if(data->state.resume_from !=
       lseek(fd, data->state.resume_from, SEEK_SET))
      return CURLE_BAD_DOWNLOAD_RESUME;
  }

  Curl_pgrsTime(data, TIMER_STARTTRANSFER);

  while(res == CURLE_OK) {
    /* Don't fill a whole buffer if we want less than all data */
    bytestoread = (expected_size < BUFSIZE-1)?(size_t)expected_size:BUFSIZE-1;
    nread = read(fd, buf, bytestoread);

    if( nread > 0)
      buf[nread] = 0;

    if (nread <= 0 || expected_size == 0)
      break;

    bytecount += nread;
    expected_size -= nread;

    res = Curl_client_write(conn, CLIENTWRITE_BODY, buf, nread);
    if(res)
      return res;

    Curl_pgrsSetDownloadCounter(data, bytecount);

    if(Curl_pgrsUpdate(conn))
      res = CURLE_ABORTED_BY_CALLBACK;
    else
      res = Curl_speedcheck(data, now);
  }
  if(Curl_pgrsUpdate(conn))
    res = CURLE_ABORTED_BY_CALLBACK;

  return res;
}