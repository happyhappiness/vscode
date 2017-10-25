int GetLastResponse(int sockfd, char *buf,
                    struct connectdata *conn)
{
  int nread;
  int keepon=TRUE;
  char *ptr;
  int timeout = 3600; /* in seconds */
  struct timeval interval;
  fd_set rkeepfd;
  fd_set readfd;
  struct UrlData *data = conn->data;

#define SELECT_OK      0
#define SELECT_ERROR   1
#define SELECT_TIMEOUT 2
  int error = SELECT_OK;

  if(data->timeout) {
    /* if timeout is requested, find out how much remaining time we have */
    timeout = data->timeout - /* timeout time */
      (tvlong(tvnow()) - tvlong(conn->now)); /* spent time */
    if(timeout <=0 ) {
      failf(data, "Transfer aborted due to timeout");
      return -SELECT_TIMEOUT; /* already too little time */
    }
  }

  FD_ZERO (&readfd);		/* clear it */
  FD_SET (sockfd, &readfd);     /* read socket */

  /* get this in a backup variable to be able to restore it on each lap in the
     select() loop */
  rkeepfd = readfd;

  do {
    ptr=buf;

    /* get us a full line, terminated with a newline */
    nread=0;
    keepon=TRUE;
    while((nread<BUFSIZE) && (keepon && !error)) {
      readfd = rkeepfd;		   /* set every lap */
      interval.tv_sec = timeout;
      interval.tv_usec = 0;

      switch (select (sockfd+1, &readfd, NULL, NULL, &interval)) {
      case -1: /* select() error, stop reading */
        error = SELECT_ERROR;
        failf(data, "Transfer aborted due to select() error");
        break;
      case 0: /* timeout */
        error = SELECT_TIMEOUT;
        infof(data, "Transfer aborted due to timeout\n");
        failf(data, "Transfer aborted due to timeout");
        break;
      default:
#ifdef USE_SSLEAY
        if (data->use_ssl) {
          keepon = SSL_read(data->ssl, ptr, 1);
        }
        else {
#endif
          keepon = sread(sockfd, ptr, 1);
#ifdef USE_SSLEAY
        }
#endif /* USE_SSLEAY */

        if ((*ptr == '\n') || (*ptr == '\r'))
          keepon = FALSE;
      }
      if(keepon) {
        nread++;
        ptr++;
      }
    }
    *ptr=0; /* zero terminate */

    if(data->bits.verbose && buf[0]) {
      fputs("< ", data->err);
      fwrite(buf, 1, nread, data->err);
      fputs("\n", data->err);
    }
  } while(!error &&
	  (nread<4 || !lastline(buf)) );
  
  if(error)
    return -error;

  return nread;
}