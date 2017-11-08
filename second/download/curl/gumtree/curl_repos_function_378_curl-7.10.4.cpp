CURLcode Curl_file(struct connectdata *conn)
{
  /* This implementation ignores the host name in conformance with 
     RFC 1738. Only local files (reachable via the standard file system)
     are supported. This means that files on remotely mounted directories
     (via NFS, Samba, NT sharing) can be accessed through a file:// URL
  */
  CURLcode res = CURLE_OK;
  struct stat statbuf;
  double expected_size=-1;
  ssize_t nread;
  struct SessionHandle *data = conn->data;
  char *buf = data->state.buffer;
  int bytecount = 0;
  struct timeval start = Curl_tvnow();
  struct timeval now = start;
  int fd;

  /* get the fd from the connection phase */
  fd = conn->proto.file->fd;

/*VMS?? -- This only works reliable for STREAMLF files */
  if( -1 != fstat(fd, &statbuf)) {
    /* we could stat it, then read out the size */
    expected_size = (double)statbuf.st_size;
  }

  /* Added by Dolbneff A.V & Spiridonoff A.V */
  if (conn->resume_from <= expected_size)
    expected_size -= conn->resume_from;
  else
    /* Is this error code suitable in such situation? */
    return CURLE_FTP_BAD_DOWNLOAD_RESUME;

  if (expected_size == 0)
    return CURLE_OK;

  /* The following is a shortcut implementation of file reading
     this is both more efficient than the former call to download() and
     it avoids problems with select() and recv() on file descriptors
     in Winsock */
  if(expected_size != -1)
    Curl_pgrsSetDownloadSize(data, expected_size);

  if(conn->resume_from)
    /* Added by Dolbneff A.V & Spiridonoff A.V */
    lseek(fd, conn->resume_from, SEEK_SET);

  while (res == CURLE_OK) {
    nread = read(fd, buf, BUFSIZE-1);

    if ( nread > 0)
      buf[nread] = 0;

    if (nread <= 0)
      break;

    bytecount += nread;
    /* NOTE: The following call to fwrite does CR/LF translation on
       Windows systems if the target is stdout. Use -O or -o parameters
       to prevent CR/LF translation (this then goes to a binary mode
       file descriptor). */

    res = Curl_client_write(data, CLIENTWRITE_BODY, buf, nread);
    if(res)
      return res;

    now = Curl_tvnow();
    if(Curl_pgrsUpdate(conn))
      res = CURLE_ABORTED_BY_CALLBACK;
  }
  now = Curl_tvnow();
  if(Curl_pgrsUpdate(conn))
    res = CURLE_ABORTED_BY_CALLBACK;

  close(fd);

  return res;
}