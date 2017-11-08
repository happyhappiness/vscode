static CURLcode ftp_readresp(curl_socket_t sockfd,
                             struct connectdata *conn,
                             int *ftpcode, /* return the ftp-code if done */
                             size_t *size) /* size of the response */
{
  ssize_t perline; /* count bytes per line */
  bool keepon=TRUE;
  ssize_t gotbytes;
  char *ptr;
  struct SessionHandle *data = conn->data;
  char *buf = data->state.buffer;
  CURLcode result = CURLE_OK;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  int code = 0;

  *ftpcode = 0; /* 0 for errors or not done */
  *size = 0;

  ptr=buf + ftpc->nread_resp;

  /* number of bytes in the current line, so far */
  perline = (ssize_t)(ptr-ftpc->linestart_resp);

  keepon=TRUE;

  while((ftpc->nread_resp<BUFSIZE) && (keepon && !result)) {

    if(ftpc->cache) {
      /* we had data in the "cache", copy that instead of doing an actual
       * read
       *
       * ftp->cache_size is cast to int here.  This should be safe,
       * because it would have been populated with something of size
       * int to begin with, even though its datatype may be larger
       * than an int.
       */
      memcpy(ptr, ftpc->cache, (int)ftpc->cache_size);
      gotbytes = (int)ftpc->cache_size;
      free(ftpc->cache);    /* free the cache */
      ftpc->cache = NULL;   /* clear the pointer */
      ftpc->cache_size = 0; /* zero the size just in case */
    }
    else {
      int res;
#if defined(HAVE_KRB4) || defined(HAVE_GSSAPI)
      enum protection_level prot = conn->data_prot;

      conn->data_prot = 0;
#endif
      res = Curl_read(conn, sockfd, ptr, BUFSIZE-ftpc->nread_resp,
                      &gotbytes);
#if defined(HAVE_KRB4) || defined(HAVE_GSSAPI)
      conn->data_prot = prot;
#endif
      if(res < 0)
        /* EWOULDBLOCK */
        return CURLE_OK; /* return */

#ifdef CURL_DOES_CONVERSIONS
      if((res == CURLE_OK) && (gotbytes > 0)) {
        /* convert from the network encoding */
        result = res = Curl_convert_from_network(data, ptr, gotbytes);
        /* Curl_convert_from_network calls failf if unsuccessful */
      }
#endif /* CURL_DOES_CONVERSIONS */

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
      ssize_t i;
      ssize_t clipamount = 0;
      bool restart = FALSE;

      data->req.headerbytecount += gotbytes;

      ftpc->nread_resp += gotbytes;
      for(i = 0; i < gotbytes; ptr++, i++) {
        perline++;
        if(*ptr=='\n') {
          /* a newline is CRLF in ftp-talk, so the CR is ignored as
             the line isn't really terminated until the LF comes */

          /* output debug output if that is requested */
#if defined(HAVE_KRB4) || defined(HAVE_GSSAPI)
          if(!conn->sec_complete)
#endif
          if(data->set.verbose)
            Curl_debug(data, CURLINFO_HEADER_IN,
                       ftpc->linestart_resp, (size_t)perline, conn);

          /*
           * We pass all response-lines to the callback function registered
           * for "headers". The response lines can be seen as a kind of
           * headers.
           */
          result = Curl_client_write(conn, CLIENTWRITE_HEADER,
                                     ftpc->linestart_resp, perline);
          if(result)
            return result;

          if(perline>3 && LASTLINE(ftpc->linestart_resp)) {
            /* This is the end of the last line, copy the last line to the
               start of the buffer and zero terminate, for old times sake (and
               krb4)! */
            char *meow;
            int n;
            for(meow=ftpc->linestart_resp, n=0; meow<ptr; meow++, n++)
              buf[n] = *meow;
            *meow=0; /* zero terminate */
            keepon=FALSE;
            ftpc->linestart_resp = ptr+1; /* advance pointer */
            i++; /* skip this before getting out */

            *size = ftpc->nread_resp; /* size of the response */
            ftpc->nread_resp = 0; /* restart */
            break;
          }
          perline=0; /* line starts over here */
          ftpc->linestart_resp = ptr+1;
        }
      }

      if(!keepon && (i != gotbytes)) {
        /* We found the end of the response lines, but we didn't parse the
           full chunk of data we have read from the server. We therefore need
           to store the rest of the data to be checked on the next invoke as
           it may actually contain another end of response already! */
        clipamount = gotbytes - i;
        restart = TRUE;
      }
      else if(keepon) {

        if((perline == gotbytes) && (gotbytes > BUFSIZE/2)) {
          /* We got an excessive line without newlines and we need to deal
             with it. First, check if it seems to start with a valid status
             code and then we keep just that in the line cache. Then throw
             away the rest. */
          infof(data, "Excessive FTP response line length received, %zd bytes."
                " Stripping\n", gotbytes);
          restart = TRUE;
          if(STATUSCODE(ftpc->linestart_resp))
            /* we copy 4 bytes since after the three-digit number there is a
               dash or a space and it is significant */
            clipamount = 4;
        }
        else if(perline && (ftpc->nread_resp > BUFSIZE/2)) {
          /* We got a large chunk of data and there's still trailing data to
             take care of, so we put that part in the "cache" and restart */
          clipamount = perline;
          restart = TRUE;
        }
      }
      else if(i == gotbytes)
        restart = TRUE;

      if(clipamount) {
        ftpc->cache_size = clipamount;
        ftpc->cache = (char *)malloc((int)ftpc->cache_size);
        if(ftpc->cache)
          memcpy(ftpc->cache, ftpc->linestart_resp, (int)ftpc->cache_size);
        else
          return CURLE_OUT_OF_MEMORY;
      }
      if(restart) {
        /* now reset a few variables to start over nicely from the start of
           the big buffer */
        ftpc->nread_resp = 0; /* start over from scratch in the buffer */
        ptr = ftpc->linestart_resp = buf;
        perline = 0;
      }

    } /* there was data */

  } /* while there's buffer left and loop is requested */

  if(!result)
    code = atoi(buf);

#if defined(HAVE_KRB4) || defined(HAVE_GSSAPI)
  /* handle the security-oriented responses 6xx ***/
  /* FIXME: some errorchecking perhaps... ***/
  switch(code) {
  case 631:
    code = Curl_sec_read_msg(conn, buf, prot_safe);
    break;
  case 632:
    code = Curl_sec_read_msg(conn, buf, prot_private);
    break;
  case 633:
    code = Curl_sec_read_msg(conn, buf, prot_confidential);
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