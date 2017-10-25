CURLcode file(struct connectdata *conn)
{
  /* This implementation ignores the host name in conformance with 
     RFC 1738. Only local files (reachable via the standard file system)
     are supported. This means that files on remotely mounted directories
     (via NFS, Samba, NT sharing) can be accessed through a file:// URL
  */
  CURLcode res = CURLE_OK;
  char *path = conn->path;
  struct stat statbuf;
  size_t expected_size=-1;
  size_t nread;
  struct UrlData *data = conn->data;
  char *buf = data->buffer;
  int bytecount = 0;
  struct timeval start = tvnow();
  struct timeval now = start;
  int fd;
  char *actual_path = curl_unescape(path, 0);

#if defined(WIN32) || defined(__EMX__)
  int i;

  /* change path separators from '/' to '\\' for Windows and OS/2 */
  for (i=0; actual_path[i] != '\0'; ++i)
    if (actual_path[i] == '/')
      actual_path[i] = '\\';

  fd = open(actual_path, O_RDONLY | O_BINARY);	/* no CR/LF translation! */
#else
  fd = open(actual_path, O_RDONLY);
#endif
  free(actual_path);

  if(fd == -1) {
    failf(data, "Couldn't open file %s", path);
    return CURLE_FILE_COULDNT_READ_FILE;
  }
  if( -1 != fstat(fd, &statbuf)) {
    /* we could stat it, then read out the size */
    expected_size = statbuf.st_size;
  }

  /* The following is a shortcut implementation of file reading
     this is both more efficient than the former call to download() and
     it avoids problems with select() and recv() on file descriptors
     in Winsock */
#if 0
  ProgressInit (data, expected_size);
#endif
  if(expected_size != -1)
    pgrsSetDownloadSize(data, expected_size);

  while (res == CURLE_OK) {
    nread = read(fd, buf, BUFSIZE-1);

    if (0 <= nread)
      buf[nread] = 0;

    if (nread <= 0)
      break;
    bytecount += nread;
    /* NOTE: The following call to fwrite does CR/LF translation on
       Windows systems if the target is stdout. Use -O or -o parameters
       to prevent CR/LF translation (this then goes to a binary mode
       file descriptor). */
    if(nread != data->fwrite (buf, 1, nread, data->out)) {
      failf (data, "Failed writing output");
      return CURLE_WRITE_ERROR;
    }
    now = tvnow();
    if(pgrsUpdate(data))
      res = CURLE_ABORTED_BY_CALLBACK;
  }
  now = tvnow();
  if(pgrsUpdate(data))
    res = CURLE_ABORTED_BY_CALLBACK;

  close(fd);

  free(actual_path);

  return res;
}