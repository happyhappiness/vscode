static CURLcode
Transfer(struct connectdata *c_conn)
{
  ssize_t nread;                /* number of bytes read */
  int bytecount = 0;            /* total number of bytes read */
  int writebytecount = 0;       /* number of bytes written */
  long contentlength=0;         /* size of incoming data */
  struct timeval start = Curl_tvnow();
  struct timeval now = start;   /* current time */
  bool header = TRUE;		/* incoming data has HTTP header */
  int headerline = 0;		/* counts header lines to better track the
                                   first one */
  char *hbufp;			/* points at *end* of header line */
  int hbuflen = 0;
  char *str;			/* within buf */
  char *str_start;		/* within buf */
  char *end_ptr;		/* within buf */
  char *p;			/* within headerbuff */
  bool content_range = FALSE;	/* set TRUE if Content-Range: was found */
  int offset = 0;		/* possible resume offset read from the
                                   Content-Range: header */
  int httpcode = 0;		/* error code from the 'HTTP/1.? XXX' line */
  int httpversion = -1;			/* the HTTP version*10 */
  bool write_after_100_header = FALSE;  /* should we enable the write after
                                           we received a 100-continue/timeout
                                           or directly */

  /* for the low speed checks: */
  CURLcode urg;
  time_t timeofdoc=0;
  long bodywrites=0;
  int writetype;

  /* the highest fd we use + 1 */
  struct SessionHandle *data;
  struct connectdata *conn = (struct connectdata *)c_conn;
  char *buf;
  int maxfd;

  data = conn->data; /* there's the root struct */
  buf = data->state.buffer;
  maxfd = (conn->sockfd>conn->writesockfd?conn->sockfd:conn->writesockfd)+1;

  hbufp = data->state.headerbuff;

  myalarm (0);			/* switch off the alarm-style timeout */

  now = Curl_tvnow();
  start = now;

#define KEEP_READ  1
#define KEEP_WRITE 2

  Curl_pgrsTime(data, TIMER_PRETRANSFER);
  Curl_speedinit(data);

  if((conn->sockfd == -1) &&
     (conn->writesockfd == -1)) {
    /* nothing to read, nothing to write, we're already OK! */
    return CURLE_OK;
  }

  if (!conn->getheader) {
    header = FALSE;
    if(conn->size > 0)
      Curl_pgrsSetDownloadSize(data, conn->size);
  }
  /* we want header and/or body, if neither then don't do this! */
  if(conn->getheader ||
     !data->set.no_body) {
    fd_set readfd;
    fd_set writefd;
    fd_set rkeepfd;
    fd_set wkeepfd;
    struct timeval interval;
    int keepon=0;

    /* timeout every X second
       - makes a better progress meter (i.e even when no data is read, the
       meter can be updated and reflect reality)
       - allows removal of the alarm() crap
       - variable timeout is easier
     */

    FD_ZERO (&readfd);		/* clear it */
    if(conn->sockfd != -1) {
      FD_SET (conn->sockfd, &readfd); /* read socket */
      keepon |= KEEP_READ;
    }

    FD_ZERO (&writefd);		/* clear it */
    if(conn->writesockfd != -1) {
      if (data->set.expect100header)
        /* wait with write until we either got 100-continue or a timeout */
        write_after_100_header = TRUE;
      else {
        FD_SET (conn->writesockfd, &writefd); /* write socket */
        keepon |= KEEP_WRITE;
      }
    }

    /* get these in backup variables to be able to restore them on each lap in
       the select() loop */
    rkeepfd = readfd;
    wkeepfd = writefd;

    while (keepon) {
      readfd = rkeepfd;		/* set those every lap in the loop */
      writefd = wkeepfd;
      interval.tv_sec = 1;
      interval.tv_usec = 0;

      switch (select (maxfd, &readfd, &writefd, NULL, &interval)) {
      case -1:			/* select() error, stop reading */
#ifdef EINTR
        /* The EINTR is not serious, and it seems you might get this more
           ofen when using the lib in a multi-threaded environment! */
        if(errno == EINTR)
          ;
        else
#endif
          keepon = 0; /* no more read or write */
	continue;
      case 0:			/* timeout */
        if (write_after_100_header) {
          write_after_100_header = FALSE;
          FD_SET (conn->writesockfd, &writefd); /* write socket */
          keepon |= KEEP_WRITE;
          wkeepfd = writefd;
        }
	break;
      default:
        if((keepon & KEEP_READ) && FD_ISSET(conn->sockfd, &readfd)) {
          /* read! */
          urg = Curl_read(conn, conn->sockfd, buf, BUFSIZE -1, &nread);

          /* NULL terminate, allowing string ops to be used */
          if (0 < (signed int) nread)
            buf[nread] = 0;

          /* if we receive 0 or less here, the server closed the connection and
             we bail out from this! */
          else if (0 >= (signed int) nread) {
            keepon &= ~KEEP_READ;
            FD_ZERO(&rkeepfd);
            break;
          }

          str = buf;		/* Default buffer to use when we write the
                                   buffer, it may be changed in the flow below
                                   before the actual storing is done. */

          /* Since this is a two-state thing, we check if we are parsing
             headers at the moment or not. */
          
          if (header) {
            /* we are in parse-the-header-mode */

            /* header line within buffer loop */
            do {
              int hbufp_index;
              
              str_start = str;	/* str_start is start of line within buf */
              
              end_ptr = strchr (str_start, '\n');
              
              if (!end_ptr) {
                /* no more complete header lines within buffer */
                /* copy what is remaining into headerbuff */
                int str_length = (int)strlen(str);

                /*
                 * We enlarge the header buffer if it seems to be too
                 * smallish
                 */
                if (hbuflen + (int)str_length >= data->state.headersize) {
                  char *newbuff;
                  long newsize=MAX((hbuflen+str_length)*3/2,
                                   data->state.headersize*2);
                  hbufp_index = hbufp - data->state.headerbuff;
                  newbuff = (char *)realloc(data->state.headerbuff, newsize);
                  if(!newbuff) {
                    failf (data, "Failed to alloc memory for big header!");
                    return CURLE_READ_ERROR;
                  }
                  data->state.headersize=newsize;
                  data->state.headerbuff = newbuff;
                  hbufp = data->state.headerbuff + hbufp_index;
                }
                strcpy (hbufp, str);
                hbufp += strlen (str);
                hbuflen += strlen (str);
                break;		/* read more and try again */
              }

              str = end_ptr + 1;	/* move just past new line */

              /*
               * We're about to copy a chunk of data to the end of the
               * already received header. We make sure that the full string
               * fit in the allocated header buffer, or else we enlarge 
               * it.
               */
              if (hbuflen + (str - str_start) >= data->state.headersize) {
                char *newbuff;
                long newsize=MAX((hbuflen+(str-str_start))*3/2,
                                 data->state.headersize*2);
                hbufp_index = hbufp - data->state.headerbuff;
                newbuff = (char *)realloc(data->state.headerbuff, newsize);
                if(!newbuff) {
                  failf (data, "Failed to alloc memory for big header!");
                  return CURLE_READ_ERROR;
                }
                data->state.headersize= newsize;
                data->state.headerbuff = newbuff;
                hbufp = data->state.headerbuff + hbufp_index;
              }

              /* copy to end of line */
              strncpy (hbufp, str_start, str - str_start);
              hbufp += str - str_start;
              hbuflen += str - str_start;
              *hbufp = 0;
              
              p = data->state.headerbuff;
              
              /****
               * We now have a FULL header line that p points to
               *****/

              if (('\n' == *p) || ('\r' == *p)) {
                /* Zero-length header line means end of headers! */

                if ('\r' == *p)
                  p++;		/* pass the \r byte */
                if ('\n' == *p)
                  p++;		/* pass the \n byte */

                if(100 == httpcode) {
                  /*
                   * we have made a HTTP PUT or POST and this is 1.1-lingo
                   * that tells us that the server is OK with this and ready
                   * to receive our stuff.
                   * However, we'll get more headers now so we must get
                   * back into the header-parsing state!
                   */
                  header = TRUE;
                  headerline = 0; /* we restart the header line counter */
                  /* if we did wait for this do enable write now! */
                  if (write_after_100_header) {
                    write_after_100_header = FALSE;
                    FD_SET (conn->writesockfd, &writefd); /* write socket */
                    keepon |= KEEP_WRITE;
                    wkeepfd = writefd;
                  }
                }
		else
                  header = FALSE;	/* no more header to parse! */

		if (417 == httpcode) {
		  /*
		   * we got: "417 Expectation Failed" this means:
		   * we have made a HTTP call and our Expect Header
		   * seems to cause a problem => abort the write operations
		   * (or prevent them from starting
		   */
		  write_after_100_header = FALSE;
		  keepon &= ~KEEP_WRITE;
		  FD_ZERO(&wkeepfd);
		}

                /* now, only output this if the header AND body are requested:
                 */
                writetype = CLIENTWRITE_HEADER;
                if (data->set.http_include_header)
                  writetype |= CLIENTWRITE_BODY;

                urg = Curl_client_write(data, writetype, data->state.headerbuff,
                                        p - data->state.headerbuff);
                if(urg)
                  return urg;

                data->info.header_size += p - data->state.headerbuff;

                if(!header) {
                  /*
                   * really end-of-headers.
                   *
                   * If we requested a "no body", this is a good time to get
                   * out and return home.
                   */
                  if(data->set.no_body)
                    return CURLE_OK;

                  if(!conn->bits.close) {
                    /* If this is not the last request before a close, we must
                       set the maximum download size to the size of the
                       expected document or else, we won't know when to stop
                       reading! */
                    if(-1 != conn->size)
                      conn->maxdownload = conn->size;

                    /* If max download size is *zero* (nothing) we already
                       have nothing and can safely return ok now! */
                    if(0 == conn->maxdownload)
                      return CURLE_OK;
                    
                    /* What to do if the size is *not* known? */
                  }
                  break;		/* exit header line loop */
                }

                /* We continue reading headers, so reset the line-based
                   header parsing variables hbufp && hbuflen */
                hbufp = data->state.headerbuff;
                hbuflen = 0;
                continue;
              }

              /*
               * Checks for special headers coming up.
               */
              
              if (!headerline++) {
                /* This is the first header, it MUST be the error code line
                   or else we consiser this to be the body right away! */
                int httpversion_major;
                int nc=sscanf (p, " HTTP/%d.%d %3d",
                               &httpversion_major ,&httpversion, &httpcode);
                if (nc==3) {
                  httpversion+=10*httpversion_major;
                }
                else {
                  /* this is the real world, not a Nirvana
                     NCSA 1.5.x returns this crap when asked for HTTP/1.1
                  */
                  nc=sscanf (p, " HTTP %3d", &httpcode);
                  httpversion = 10;
                }

                if (nc) {
                  data->info.httpcode = httpcode;
                  data->info.httpversion = httpversion;

                  /* 404 -> URL not found! */
                  if (
                      ( ((data->set.http_follow_location) &&
                         (httpcode >= 400))
                        ||
                        (!data->set.http_follow_location &&
                         (httpcode >= 300)))
                      && (data->set.http_fail_on_error)) {
                    /* If we have been told to fail hard on HTTP-errors,
                       here is the check for that: */
                    /* serious error, go home! */
                    failf (data, "The requested file was not found");
                    return CURLE_HTTP_NOT_FOUND;
                  }

                  if(httpversion == 10)
                    /* Default action for HTTP/1.0 must be to close, unless
                       we get one of those fancy headers that tell us the
                       server keeps it open for us! */
                    conn->bits.close = TRUE;

                  if (httpcode == 304)
                    /* (quote from RFC2616, section 10.3.5):
                     *  The 304 response MUST NOT contain a
                     * message-body, and thus is always
                     * terminated by the first empty line
                     * after the header fields.
                     */
                    conn->size=0;
                }
                else {
                  header = FALSE;	/* this is not a header line */
                  break;
                }
              }
              /* check for Content-Length: header lines to get size */
              if (strnequal("Content-Length:", p, 15) &&
                  sscanf (p+15, " %ld", &contentlength)) {
                conn->size = contentlength;
                Curl_pgrsSetDownloadSize(data, contentlength);
              }
              else if((httpversion == 10) &&
                      conn->bits.httpproxy &&
                      compareheader(p, "Proxy-Connection:", "keep-alive")) {
                /*
                 * When a HTTP/1.0 reply comes when using a proxy, the
                 * 'Proxy-Connection: keep-alive' line tells us the
                 * connection will be kept alive for our pleasure.
                 * Default action for 1.0 is to close.
                 */
                conn->bits.close = FALSE; /* don't close when done */
                infof(data, "HTTP/1.0 proxy connection set to keep alive!\n");
              }
              else if((httpversion == 10) &&
                      compareheader(p, "Connection:", "keep-alive")) {
                /*
                 * A HTTP/1.0 reply with the 'Connection: keep-alive' line
                 * tells us the connection will be kept alive for our
                 * pleasure.  Default action for 1.0 is to close.
                 *
                 * [RFC2068, section 19.7.1] */
                conn->bits.close = FALSE; /* don't close when done */
                infof(data, "HTTP/1.0 connection set to keep alive!\n");
              }
              else if (compareheader(p, "Connection:", "close")) {
                /*
                 * [RFC 2616, section 8.1.2.1]
                 * "Connection: close" is HTTP/1.1 language and means that
                 * the connection will close when this request has been
                 * served.
                 */
                conn->bits.close = TRUE; /* close when done */
              }
              else if (compareheader(p, "Transfer-Encoding:", "chunked")) {
                /*
                 * [RFC 2616, section 3.6.1] A 'chunked' transfer encoding
                 * means that the server will send a series of "chunks". Each
                 * chunk starts with line with info (including size of the
                 * coming block) (terminated with CRLF), then a block of data
                 * with the previously mentioned size. There can be any amount
                 * of chunks, and a chunk-data set to zero signals the
                 * end-of-chunks. */
                conn->bits.chunk = TRUE; /* chunks coming our way */

                /* init our chunky engine */
                Curl_httpchunk_init(conn);
              }
              else if (strnequal("Content-Range:", p, 14)) {
                if (sscanf (p+14, " bytes %d-", &offset) ||
                    sscanf (p+14, " bytes: %d-", &offset)) {
                  /* This second format was added August 1st 2000 by Igor
                     Khristophorov since Sun's webserver JavaWebServer/1.1.1
                     obviously sends the header this way! :-( */
                  if (conn->resume_from == offset) {
                    /* we asked for a resume and we got it */
                    content_range = TRUE;
                  }
                }
              }
              else if(data->cookies &&
                      strnequal("Set-Cookie:", p, 11)) {
                Curl_cookie_add(data->cookies, TRUE, &p[12]);
              }
              else if(strnequal("Last-Modified:", p,
                                strlen("Last-Modified:")) &&
                      (data->set.timecondition || data->set.get_filetime) ) {
                time_t secs=time(NULL);
                timeofdoc = curl_getdate(p+strlen("Last-Modified:"), &secs);
                if(data->set.get_filetime)
                  data->info.filetime = timeofdoc;
              }
              else if ((httpcode >= 300 && httpcode < 400) &&
                       (data->set.http_follow_location) &&
                       strnequal("Location:", p, 9)) {
                /* this is the URL that the server advices us to get instead */
                char *ptr;
                char *start=p;
                char backup;

                start += 9; /* pass "Location:" */

                /* Skip spaces and tabs. We do this to support multiple
                   white spaces after the "Location:" keyword. */
                while(*start && isspace((int)*start ))
                  start++;
                ptr = start; /* start scanning here */

                /* scan through the string to find the end */
                while(*ptr && !isspace((int)*ptr))
                  ptr++;
                backup = *ptr; /* store the ending letter */
                *ptr = '\0';   /* zero terminate */
                conn->newurl = strdup(start); /* clone string */
                *ptr = backup; /* restore ending letter */
              }

              /*
               * End of header-checks. Write them to the client.
               */

              writetype = CLIENTWRITE_HEADER;
              if (data->set.http_include_header)
                writetype |= CLIENTWRITE_BODY;

              urg = Curl_client_write(data, writetype, p, hbuflen);
              if(urg)
                return urg;

              data->info.header_size += hbuflen;
              
              /* reset hbufp pointer && hbuflen */
              hbufp = data->state.headerbuff;
              hbuflen = 0;
            }
            while (*str);		/* header line within buffer */

            /* We might have reached the end of the header part here, but
               there might be a non-header part left in the end of the read
               buffer. */

            if (!header) {
              /* the next token and forward is not part of
                 the header! */

              /* we subtract the remaining header size from the buffer */
              nread -= (str - buf);
            }

          }			/* end if header mode */

          /* This is not an 'else if' since it may be a rest from the header
             parsing, where the beginning of the buffer is headers and the end
             is non-headers. */
          if (str && !header && ((signed int)nread > 0)) {
            
            if(0 == bodywrites) {
              /* These checks are only made the first time we are about to
                 write a piece of the body */
              if(conn->protocol&PROT_HTTP) {
                /* HTTP-only checks */
                if (conn->newurl) {
                  /* abort after the headers if "follow Location" is set */
                  infof (data, "Follow to new URL: %s\n", conn->newurl);
                  return CURLE_OK;
                }
                else if (conn->resume_from &&
                         !content_range &&
                         (data->set.httpreq==HTTPREQ_GET)) {
                  /* we wanted to resume a download, although the server
                     doesn't seem to support this and we did this with a GET
                     (if it wasn't a GET we did a POST or PUT resume) */
                  failf (data, "HTTP server doesn't seem to support "
                         "byte ranges. Cannot resume.");
                  return CURLE_HTTP_RANGE_ERROR;
                }
                else if(data->set.timecondition && !conn->range) {
                  /* A time condition has been set AND no ranges have been
                     requested. This seems to be what chapter 13.3.4 of
                     RFC 2616 defines to be the correct action for a
                     HTTP/1.1 client */
                  if((timeofdoc > 0) && (data->set.timevalue > 0)) {
                    switch(data->set.timecondition) {
                    case TIMECOND_IFMODSINCE:
                    default:
                      if(timeofdoc < data->set.timevalue) {
                        infof(data,
                              "The requested document is not new enough\n");
                        return CURLE_OK;
                      }
                      break;
                    case TIMECOND_IFUNMODSINCE:
                      if(timeofdoc > data->set.timevalue) {
                        infof(data,
                              "The requested document is not old enough\n");
                        return CURLE_OK;
                      }
                      break;
                    } /* switch */
                  } /* two valid time strings */
                } /* we have a time condition */

              } /* this is HTTP */
            } /* this is the first time we write a body part */
            bodywrites++;

            if(conn->bits.chunk) {
              /*
               * Bless me father for I have sinned. Here comes a chunked
               * transfer flying and we need to decode this properly.  While
               * the name says read, this function both reads and writes away
               * the data. The returned 'nread' holds the number of actual
               * data it wrote to the client.  */
              CHUNKcode res =
                Curl_httpchunk_read(conn, str, nread, &nread);

              if(CHUNKE_OK < res) {
                failf(data, "Receeived problem in the chunky parser");
                return CURLE_READ_ERROR;
              }
              else if(CHUNKE_STOP == res) {
                /* we're done reading chunks! */
                keepon &= ~KEEP_READ; /* read no more */
                FD_ZERO(&rkeepfd);

                /* There are now possibly N number of bytes at the end of the
                   str buffer that weren't written to the client, but we don't
                   care about them right now. */
              }
              /* If it returned OK, we just keep going */
            }

            if((-1 != conn->maxdownload) &&
               (bytecount + nread >= conn->maxdownload)) {
              nread = conn->maxdownload - bytecount;
              if((signed int)nread < 0 ) /* this should be unusual */
                nread = 0;

              keepon &= ~KEEP_READ; /* we're done reading */
              FD_ZERO(&rkeepfd);
            }

            bytecount += nread;

            Curl_pgrsSetDownloadCounter(data, (double)bytecount);
            
            if(!conn->bits.chunk && nread) {
              /* If this is chunky transfer, it was already written */
              urg = Curl_client_write(data, CLIENTWRITE_BODY, str, nread);
              if(urg)
                return urg;
            }

          } /* if (! header and data to read ) */
        } /* if( read from socket ) */

        if((keepon & KEEP_WRITE) && FD_ISSET(conn->writesockfd, &writefd)) {
          /* write */

          int i, si;
          size_t bytes_written;

          nread = data->set.fread(buf, 1, conn->upload_bufsize, data->set.in);

          /* the signed int typecase of nread of for systems that has
             unsigned size_t */
          if ((signed int)nread<=0) {
            /* done */
            keepon &= ~KEEP_WRITE; /* we're done writing */
            FD_ZERO(&wkeepfd);
            break;
          }
          writebytecount += nread;
          Curl_pgrsSetUploadCounter(data, (double)writebytecount);            

          /* convert LF to CRLF if so asked */
          if (data->set.crlf) {
            for(i = 0, si = 0; i < (int)nread; i++, si++) {
              if (buf[i] == 0x0a) {
                data->state.scratch[si++] = 0x0d;
                data->state.scratch[si] = 0x0a;
              }
              else {
                data->state.scratch[si] = buf[i];
              }
            }
            nread = si;
            buf = data->state.scratch; /* point to the new buffer */
          }

          /* write to socket */
          urg = Curl_write(conn, conn->writesockfd, buf, nread,
                           &bytes_written);

          if(nread != (int)bytes_written) {
            failf(data, "Failed uploading data");
            return CURLE_WRITE_ERROR;
          }
          if(data->set.crlf)
            buf = data->state.buffer; /* put it back on the buffer */

        }

        break;
      }

      now = Curl_tvnow();
      if(Curl_pgrsUpdate(conn))
        urg = CURLE_ABORTED_BY_CALLBACK;
      else
        urg = Curl_speedcheck (data, now);
      if (urg)
	return urg;

      if(data->progress.ulspeed > conn->upload_bufsize) {
        /* If we're transfering more data per second than fits in our buffer,
           we increase the buffer size to adjust to the current
           speed. However, we must not set it larger than BUFSIZE. We don't
           adjust it downwards again since we don't see any point in that!
        */
        conn->upload_bufsize=(long)min(data->progress.ulspeed, BUFSIZE);
      }

      if (data->set.timeout && (Curl_tvdiff (now, start) > data->set.timeout)) {
	failf (data, "Operation timed out with %d out of %d bytes received",
	       bytecount, conn->size);
	return CURLE_OPERATION_TIMEOUTED;
      }
    }
  }

  /*
   * The tranfer has been performed. Just make some general checks before
   * returning.
   */

  if(!(data->set.no_body) && contentlength &&
     (bytecount != contentlength)) {
    failf(data, "transfer closed with %d bytes remaining to read",
          contentlength-bytecount);
    return CURLE_PARTIAL_FILE;
  }
  else if(conn->bits.chunk && conn->proto.http->chunk.datasize) {
    failf(data, "transfer closed with at least %d bytes remaining",
          conn->proto.http->chunk.datasize);
    return CURLE_PARTIAL_FILE;
  }
  if(Curl_pgrsUpdate(conn))
    return CURLE_ABORTED_BY_CALLBACK;

  if(conn->bytecountp)
    *conn->bytecountp = bytecount; /* read count */
  if(conn->writebytecountp)
    *conn->writebytecountp = writebytecount; /* write count */

  return CURLE_OK;
}