static CURLcode ftp_readresp(curl_socket_t sockfd,
                             struct connectdata *conn,
                             int *ftpcode, /* return the ftp-code if done */
                             size_t *size) /* size of the response */
{
  int perline; /* count bytes per line */
  bool keepon=TRUE;
  ssize_t gotbytes;
  char *ptr;
  struct SessionHandle *data = conn->data;
  char *buf = data->state.buffer;
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->proto.ftp;
  int code = 0;

  if (ftpcode)
    *ftpcode = 0; /* 0 for errors or not done */

  ptr=buf + ftp->nread_resp;

  perline= (int)(ptr-ftp->linestart_resp); /* number of bytes in the current
                                              line, so far */
  keepon=TRUE;

  while((ftp->nread_resp<BUFSIZE) && (keepon && !result)) {

    if(ftp->cache) {
      /* we had data in the "cache", copy that instead of doing an actual
       * read
       *
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
      int res = Curl_read(conn, sockfd, ptr, BUFSIZE-ftp->nread_resp,
                          &gotbytes);
      if(res < 0)
        /* EWOULDBLOCK */
        return CURLE_OK; /* return */

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

      ftp->nread_resp += gotbytes;
      for(i = 0; i < gotbytes; ptr++, i++) {
        perline++;
        if(*ptr=='\n') {
          /* a newline is CRLF in ftp-talk, so the CR is ignored as
             the line isn't really terminated until the LF comes */

          /* output debug output if that is requested */
          if(data->set.verbose)
            Curl_debug(data, CURLINFO_HEADER_IN,
                       ftp->linestart_resp, perline, conn);

          /*
           * We pass all response-lines to the callback function registered
           * for "headers". The response lines can be seen as a kind of
           * headers.
           */
          result = Curl_client_write(data, CLIENTWRITE_HEADER,
                                     ftp->linestart_resp, perline);
          if(result)
            return result;

          if(perline>3 && lastline(ftp->linestart_resp)) {
            /* This is the end of the last line, copy the last line to the
               start of the buffer and zero terminate, for old times sake (and
               krb4)! */
            char *meow;
            int n;
            for(meow=ftp->linestart_resp, n=0; meow<ptr; meow++, n++)
              buf[n] = *meow;
            *meow=0; /* zero terminate */
            keepon=FALSE;
            ftp->linestart_resp = ptr+1; /* advance pointer */
            i++; /* skip this before getting out */

            *size = ftp->nread_resp; /* size of the response */
            ftp->nread_resp = 0; /* restart */
            break;
          }
          perline=0; /* line starts over here */
          ftp->linestart_resp = ptr+1;
        }
      }
      if(!keepon && (i != gotbytes)) {
        /* We found the end of the response lines, but we didn't parse the
           full chunk of data we have read from the server. We therefore need
           to store the rest of the data to be checked on the next invoke as
           it may actually contain another end of response already! */
        ftp->cache_size = gotbytes - i;
        ftp->cache = (char *)malloc((int)ftp->cache_size);
        if(ftp->cache)
          memcpy(ftp->cache, ftp->linestart_resp, (int)ftp->cache_size);
        else
          return CURLE_OUT_OF_MEMORY; /**BANG**/
      }
    } /* there was data */

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

  *ftpcode=code; /* return the initial number like this */


  /* store the latest code for later retrieval */
  conn->data->info.httpcode=code;

  return result;
}