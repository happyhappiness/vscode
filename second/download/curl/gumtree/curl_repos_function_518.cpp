CURLcode Curl_GetFTPResponse(ssize_t *nreadp, /* return number of bytes read */
                             struct connectdata *conn,
                             int *ftpcode) /* return the ftp-code */
{
  /*
   * We cannot read just one byte per read() and then go back to select() as
   * the OpenSSL read() doesn't grok that properly.
   *
   * Alas, read as much as possible, split up into lines, use the ending
   * line in a response or continue reading.  */

  curl_socket_t sockfd = conn->sock[FIRSTSOCKET];
  int perline; /* count bytes per line */
  bool keepon=TRUE;
  ssize_t gotbytes;
  char *ptr;
  long timeout;              /* timeout in seconds */
  int interval_ms;
  struct SessionHandle *data = conn->data;
  char *line_start;
  int code=0; /* default ftp "error code" to return */
  char *buf = data->state.buffer;
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->proto.ftp;
  struct timeval now = Curl_tvnow();

  if (ftpcode)
    *ftpcode = 0; /* 0 for errors */

  ptr=buf;
  line_start = buf;

  *nreadp=0;
  perline=0;
  keepon=TRUE;

  while((*nreadp<BUFSIZE) && (keepon && !result)) {
    /* check and reset timeout value every lap */
    if(data->set.ftp_response_timeout )
      /* if CURLOPT_FTP_RESPONSE_TIMEOUT is set, use that to determine
         remaining time.  Also, use "now" as opposed to "conn->now"
         because ftp_response_timeout is only supposed to govern
         the response for any given ftp response, not for the time
         from connect to the given ftp response. */
      timeout = data->set.ftp_response_timeout - /* timeout time */
        Curl_tvdiff(Curl_tvnow(), now)/1000; /* spent time */
    else if(data->set.timeout)
      /* if timeout is requested, find out how much remaining time we have */
      timeout = data->set.timeout - /* timeout time */
        Curl_tvdiff(Curl_tvnow(), conn->now)/1000; /* spent time */
    else
      /* Even without a requested timeout, we only wait response_time
         seconds for the full response to arrive before we bail out */
      timeout = ftp->response_time -
        Curl_tvdiff(Curl_tvnow(), now)/1000; /* spent time */

    if(timeout <=0 ) {
      failf(data, "FTP response timeout");
      return CURLE_OPERATION_TIMEDOUT; /* already too little time */
    }

    if(!ftp->cache) {
      interval_ms = 1 * 1000;  /* use 1 second timeout intervals */

      switch (Curl_select(sockfd, CURL_SOCKET_BAD, interval_ms)) {
      case -1: /* select() error, stop reading */
        result = CURLE_RECV_ERROR;
        failf(data, "FTP response aborted due to select() error: %d", errno);
        break;
      case 0: /* timeout */
        if(Curl_pgrsUpdate(conn))
          return CURLE_ABORTED_BY_CALLBACK;
        continue; /* just continue in our loop for the timeout duration */

      default:
        break;
      }
    }
    if(CURLE_OK == result) {
      /*
       * This code previously didn't use the kerberos sec_read() code
       * to read, but when we use Curl_read() it may do so. Do confirm
       * that this is still ok and then remove this comment!
       */
      if(ftp->cache) {
        /* we had data in the "cache", copy that instead of doing an actual
         * read
         *
         * Dave Meyer, December 2003:
         * ftp->cache_size is cast to int here.  This should be safe,
         * because it would have been populated with something of size
         * int to begin with, even though its datatype may be larger
         * than an int.
         */
        memcpy(ptr, ftp->cache, (int)ftp->cache_size);
        gotbytes = (int)ftp->cache_size;
        free(ftp->cache);    /* free the cache */
        ftp->cache = NULL;   /* clear the pointer */
        ftp->cache_size = 0; /* zero the size just in case */
      }
      else {
        int res = Curl_read(conn, sockfd, ptr, BUFSIZE-*nreadp, &gotbytes);
        if(res < 0)
          /* EWOULDBLOCK */
          continue; /* go looping again */

        if(CURLE_OK != res)
          keepon = FALSE;
      }

      if(!keepon)
        ;
      else if(gotbytes <= 0) {
        keepon = FALSE;
        result = CURLE_RECV_ERROR;
        failf(data, "FTP response reading failed");
      }
      else {
        /* we got a whole chunk of data, which can be anything from one
         * byte to a set of lines and possible just a piece of the last
         * line */
        int i;

        conn->headerbytecount += gotbytes;

        *nreadp += gotbytes;
        for(i = 0; i < gotbytes; ptr++, i++) {
          perline++;
          if(*ptr=='\n') {
            /* a newline is CRLF in ftp-talk, so the CR is ignored as
               the line isn't really terminated until the LF comes */

            /* output debug output if that is requested */
            if(data->set.verbose)
              Curl_debug(data, CURLINFO_HEADER_IN, line_start, perline, conn);

            /*
             * We pass all response-lines to the callback function registered
             * for "headers". The response lines can be seen as a kind of
             * headers.
             */
            result = Curl_client_write(data, CLIENTWRITE_HEADER,
                                       line_start, perline);
            if(result)
              return result;

            if(perline>3 && lastline(line_start)) {
              /* This is the end of the last line, copy the last
               * line to the start of the buffer and zero terminate,
               * for old times sake (and krb4)! */
              char *meow;
              int n;
              for(meow=line_start, n=0; meow<ptr; meow++, n++)
                buf[n] = *meow;
              *meow=0; /* zero terminate */
              keepon=FALSE;
              line_start = ptr+1; /* advance pointer */
              i++; /* skip this before getting out */
              break;
            }
            perline=0; /* line starts over here */
            line_start = ptr+1;
          }
        }
        if(!keepon && (i != gotbytes)) {
          /* We found the end of the response lines, but we didn't parse the
             full chunk of data we have read from the server. We therefore
             need to store the rest of the data to be checked on the next
             invoke as it may actually contain another end of response
             already!  Cleverly figured out by Eric Lavigne in December
             2001. */
          ftp->cache_size = gotbytes - i;
          ftp->cache = (char *)malloc((int)ftp->cache_size);
          if(ftp->cache)
            memcpy(ftp->cache, line_start, (int)ftp->cache_size);
          else
            return CURLE_OUT_OF_MEMORY; /**BANG**/
        }
      } /* there was data */
    } /* if(no error) */
  } /* while there's buffer left and loop is requested */

  if(!result)
    code = atoi(buf);

#ifdef HAVE_KRB4
  /* handle the security-oriented responses 6xx ***/
  /* FIXME: some errorchecking perhaps... ***/
  switch(code) {
  case 631:
    Curl_sec_read_msg(conn, buf, prot_safe);
    break;
  case 632:
    Curl_sec_read_msg(conn, buf, prot_private);
    break;
  case 633:
    Curl_sec_read_msg(conn, buf, prot_confidential);
    break;
  default:
    /* normal ftp stuff we pass through! */
    break;
  }
#endif

  if(ftpcode)
    *ftpcode=code; /* return the initial number like this */

  /* store the latest code for later retrieval */
  conn->data->info.httpcode=code;

  return result;
}