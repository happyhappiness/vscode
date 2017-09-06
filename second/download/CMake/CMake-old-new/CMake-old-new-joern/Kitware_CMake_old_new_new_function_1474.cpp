CURLcode Curl_readwrite(struct connectdata *conn,
                        bool *done)
{
  struct Curl_transfer_keeper *k = &conn->keep;
  struct SessionHandle *data = conn->data;
  int result;
  ssize_t nread; /* number of bytes read */
  int didwhat=0;
  
  /* These two are used only if no other select() or _fdset() have been
     invoked before this. This typicly happens if you use the multi interface
     and call curl_multi_perform() without calling curl_multi_fdset()
     first. */
  fd_set extrareadfd;
  fd_set extrawritefd;

  fd_set *readfdp = k->readfdp;
  fd_set *writefdp = k->writefdp;
  
  if((k->keepon & KEEP_READ) && !readfdp) {
    /* reading is requested, but no socket descriptor pointer was set */
    FD_ZERO(&extrareadfd);
    FD_SET(conn->sockfd, &extrareadfd);
    readfdp = &extrareadfd;

    /* no write, no exceptions, no timeout */
    select(conn->sockfd+1, readfdp, NULL, NULL, &notimeout);
  }
  if((k->keepon & KEEP_WRITE) && !writefdp) {
    /* writing is requested, but no socket descriptor pointer was set */
    FD_ZERO(&extrawritefd);
    FD_SET(conn->writesockfd, &extrawritefd);
    writefdp = &extrawritefd;

    /* no read, no exceptions, no timeout */
    select(conn->writesockfd+1, NULL, writefdp, NULL, &notimeout);
  }

  do {
    /* If we still have reading to do, we check if we have a readable
       socket. Sometimes the reafdp is NULL, it no fd_set was done using
       the multi interface and then we can do nothing but to attempt a
       read to be sure. */
    if((k->keepon & KEEP_READ) &&
       (FD_ISSET(conn->sockfd, readfdp))) {

      /* read! */
      result = Curl_read(conn, conn->sockfd, k->buf,
                         data->set.buffer_size?
                         data->set.buffer_size:BUFSIZE -1,
                         &nread);

      if(0>result)
        break; /* get out of loop */
      if(result>0)
        return result;

      if ((k->bytecount == 0) && (k->writebytecount == 0))
        Curl_pgrsTime(data, TIMER_STARTTRANSFER);

      didwhat |= KEEP_READ;

      /* NULL terminate, allowing string ops to be used */
      if (0 < nread)
        k->buf[nread] = 0;

      /* if we receive 0 or less here, the server closed the connection and
         we bail out from this! */
      else if (0 >= nread) {
        k->keepon &= ~KEEP_READ;
        FD_ZERO(&k->rkeepfd);
        break;
      }

      /* Default buffer to use when we write the buffer, it may be changed
         in the flow below before the actual storing is done. */
      k->str = k->buf;

      /* Since this is a two-state thing, we check if we are parsing
         headers at the moment or not. */          
      if (k->header) {
        /* we are in parse-the-header-mode */
        bool stop_reading = FALSE;

        /* header line within buffer loop */
        do {
          int hbufp_index;
              
          /* str_start is start of line within buf */
          k->str_start = k->str;
              
          k->end_ptr = strchr (k->str_start, '\n');
              
          if (!k->end_ptr) {
            /* Not a complete header line within buffer, append the data to
               the end of the headerbuff. */

            if (k->hbuflen + nread >= data->state.headersize) {
              /* We enlarge the header buffer as it is too small */
              char *newbuff;
              long newsize=MAX((k->hbuflen+nread)*3/2,
                               data->state.headersize*2);
              hbufp_index = k->hbufp - data->state.headerbuff;
              newbuff = (char *)realloc(data->state.headerbuff, newsize);
              if(!newbuff) {
                failf (data, "Failed to alloc memory for big header!");
                return CURLE_OUT_OF_MEMORY;
              }
              data->state.headersize=newsize;
              data->state.headerbuff = newbuff;
              k->hbufp = data->state.headerbuff + hbufp_index;
            }
            memcpy(k->hbufp, k->str, nread);
            k->hbufp += nread;
            k->hbuflen += nread;
            if (!k->headerline && (k->hbuflen>5)) {
              /* make a first check that this looks like a HTTP header */
              if(!checkprefix("HTTP/", data->state.headerbuff)) {
                /* this is not the beginning of a HTTP first header line */
                k->header = FALSE;
                k->badheader = HEADER_ALLBAD;
                break;
              }
            }

            break;              /* read more and try again */
          }

          /* decrease the size of the remaining buffer */
          nread -= (k->end_ptr - k->str)+1; 

          k->str = k->end_ptr + 1; /* move past new line */

          /*
           * We're about to copy a chunk of data to the end of the
           * already received header. We make sure that the full string
           * fit in the allocated header buffer, or else we enlarge 
           * it.
           */
          if (k->hbuflen + (k->str - k->str_start) >=
              data->state.headersize) {
            char *newbuff;
            long newsize=MAX((k->hbuflen+
                              (k->str-k->str_start))*3/2,
                             data->state.headersize*2);
            hbufp_index = k->hbufp - data->state.headerbuff;
            newbuff = (char *)realloc(data->state.headerbuff, newsize);
            if(!newbuff) {
              failf (data, "Failed to alloc memory for big header!");
              return CURLE_OUT_OF_MEMORY;
            }
            data->state.headersize= newsize;
            data->state.headerbuff = newbuff;
            k->hbufp = data->state.headerbuff + hbufp_index;
          }

          /* copy to end of line */
          strncpy (k->hbufp, k->str_start, k->str - k->str_start);
          k->hbufp += k->str - k->str_start;
          k->hbuflen += k->str - k->str_start;
          *k->hbufp = 0;
              
          k->p = data->state.headerbuff;
              
          /****
           * We now have a FULL header line that p points to
           *****/

          if(!k->headerline) {
            /* the first read header */
            if((k->hbuflen>5) &&
               !checkprefix("HTTP/", data->state.headerbuff)) {
              /* this is not the beginning of a HTTP first header line */
              k->header = FALSE;
              k->badheader = HEADER_PARTHEADER;
              break;
            }
          }

          if (('\n' == *k->p) || ('\r' == *k->p)) {
            int headerlen;
            /* Zero-length header line means end of headers! */

            if ('\r' == *k->p)
              k->p++; /* pass the \r byte */
            if ('\n' == *k->p)
              k->p++; /* pass the \n byte */

            if(100 == k->httpcode) {
              /*
               * we have made a HTTP PUT or POST and this is 1.1-lingo
               * that tells us that the server is OK with this and ready
               * to receive our stuff.
               * However, we'll get more headers now so we must get
               * back into the header-parsing state!
               */
              k->header = TRUE;
              k->headerline = 0; /* restart the header line counter */
              /* if we did wait for this do enable write now! */
              if (k->write_after_100_header) {

                k->write_after_100_header = FALSE;
                FD_SET (conn->writesockfd, &k->writefd); /* write */
                k->keepon |= KEEP_WRITE;
                k->wkeepfd = k->writefd;
              }
            }
            else
              k->header = FALSE; /* no more header to parse! */

            if (417 == k->httpcode) {
              /*
               * we got: "417 Expectation Failed" this means:
               * we have made a HTTP call and our Expect Header
               * seems to cause a problem => abort the write operations
               * (or prevent them from starting).
               */
              k->write_after_100_header = FALSE;
              k->keepon &= ~KEEP_WRITE;
              FD_ZERO(&k->wkeepfd);
            }

            /* now, only output this if the header AND body are requested:
             */
            k->writetype = CLIENTWRITE_HEADER;
            if (data->set.http_include_header)
              k->writetype |= CLIENTWRITE_BODY;

            headerlen = k->p - data->state.headerbuff;

            result = Curl_client_write(data, k->writetype,
                                       data->state.headerbuff,
                                       headerlen);
            if(result)
              return result;

            data->info.header_size += headerlen;
            conn->headerbytecount += headerlen;

            if(!k->header) {
              /*
               * really end-of-headers.
               *
               * If we requested a "no body", this is a good time to get
               * out and return home.
               */
              if(data->set.no_body)
                stop_reading = TRUE;
              else if(!conn->bits.close) {
                /* If this is not the last request before a close, we must
                   set the maximum download size to the size of the
                   expected document or else, we won't know when to stop
                   reading! */
                if(-1 != conn->size)
                  conn->maxdownload = conn->size;
              }
              /* If max download size is *zero* (nothing) we already
                 have nothing and can safely return ok now! */
              if(0 == conn->maxdownload)
                stop_reading = TRUE;
                    
              if(stop_reading) {
                /* we make sure that this socket isn't read more now */
                k->keepon &= ~KEEP_READ;
                FD_ZERO(&k->rkeepfd);
              }

              break;            /* exit header line loop */
            }

            /* We continue reading headers, so reset the line-based
               header parsing variables hbufp && hbuflen */
            k->hbufp = data->state.headerbuff;
            k->hbuflen = 0;
            continue;
          }

          /*
           * Checks for special headers coming up.
           */
              
          if (!k->headerline++) {
            /* This is the first header, it MUST be the error code line
               or else we consiser this to be the body right away! */
            int httpversion_major;
            int nc=sscanf (k->p, " HTTP/%d.%d %3d",
                           &httpversion_major,
                           &k->httpversion,
                           &k->httpcode);
            if (nc==3) {
              k->httpversion += 10 * httpversion_major;
            }
            else {
              /* this is the real world, not a Nirvana
                 NCSA 1.5.x returns this crap when asked for HTTP/1.1
              */
              nc=sscanf (k->p, " HTTP %3d", &k->httpcode);
              k->httpversion = 10;
            }

            if (nc) {
              data->info.httpcode = k->httpcode;
              data->info.httpversion = k->httpversion;

              /* 404 -> URL not found! */
              if (data->set.http_fail_on_error &&
                  (k->httpcode >= 400)) {
                /* If we have been told to fail hard on HTTP-errors,
                   here is the check for that: */
                /* serious error, go home! */
                failf (data, "The requested file was not found");
                return CURLE_HTTP_NOT_FOUND;
              }

              if(k->httpversion == 10)
                /* Default action for HTTP/1.0 must be to close, unless
                   we get one of those fancy headers that tell us the
                   server keeps it open for us! */
                conn->bits.close = TRUE;

              switch(k->httpcode) {
              case 204:
                /* (quote from RFC2616, section 10.2.5): The server has
                 * fulfilled the request but does not need to return an
                 * entity-body ... The 204 response MUST NOT include a
                 * message-body, and thus is always terminated by the first
                 * empty line after the header fields. */
                /* FALLTHROUGH */
              case 304:
                /* (quote from RFC2616, section 10.3.5): The 304 response MUST
                 * NOT contain a message-body, and thus is always terminated
                 * by the first empty line after the header fields.  */
                conn->size=0;
                conn->maxdownload=0;
                break;
              default:
                /* nothing */
                break;
              }
            }
            else {
              k->header = FALSE;   /* this is not a header line */
              break;
            }
          }

          /* check for Content-Length: header lines to get size */
          if (checkprefix("Content-Length:", k->p) &&
              sscanf (k->p+15, " %ld", &k->contentlength)) {
            conn->size = k->contentlength;
            Curl_pgrsSetDownloadSize(data, k->contentlength);
            }
          /* check for Content-Type: header lines to get the mime-type */
          else if (checkprefix("Content-Type:", k->p)) {
            char *start;
            char *end;
            int len;
              
            /* Find the first non-space letter */
            for(start=k->p+14;
                *start && isspace((int)*start);
                start++);

            /* count all non-space letters following */
            for(end=start, len=0;
                *end && !isspace((int)*end);
                end++, len++);

            /* allocate memory of a cloned copy */
            data->info.contenttype = malloc(len + 1);
            if (NULL == data->info.contenttype)
              return CURLE_OUT_OF_MEMORY;

            /* copy the content-type string */
            memcpy(data->info.contenttype, start, len);
            data->info.contenttype[len] = 0; /* zero terminate */
          }
          else if((k->httpversion == 10) &&
                  conn->bits.httpproxy &&
                  compareheader(k->p, "Proxy-Connection:", "keep-alive")) {
            /*
             * When a HTTP/1.0 reply comes when using a proxy, the
             * 'Proxy-Connection: keep-alive' line tells us the
             * connection will be kept alive for our pleasure.
             * Default action for 1.0 is to close.
             */
            conn->bits.close = FALSE; /* don't close when done */
            infof(data, "HTTP/1.0 proxy connection set to keep alive!\n");
          }
          else if((k->httpversion == 10) &&
                  compareheader(k->p, "Connection:", "keep-alive")) {
            /*
             * A HTTP/1.0 reply with the 'Connection: keep-alive' line
             * tells us the connection will be kept alive for our
             * pleasure.  Default action for 1.0 is to close.
             *
             * [RFC2068, section 19.7.1] */
            conn->bits.close = FALSE; /* don't close when done */
            infof(data, "HTTP/1.0 connection set to keep alive!\n");
          }
          else if (compareheader(k->p, "Connection:", "close")) {
            /*
             * [RFC 2616, section 8.1.2.1]
             * "Connection: close" is HTTP/1.1 language and means that
             * the connection will close when this request has been
             * served.
             */
            conn->bits.close = TRUE; /* close when done */
          }
          else if (compareheader(k->p, "Transfer-Encoding:", "chunked")) {
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
          else if (checkprefix("Content-Encoding:", k->p) &&
                   data->set.encoding) {
            /*
             * Process Content-Encoding. Look for the values: identity, gzip,
             * defalte, compress, x-gzip and x-compress. x-gzip and
             * x-compress are the same as gzip and compress. (Sec 3.5 RFC
             * 2616). zlib cannot handle compress, and gzip is not currently
             * implemented. However, errors are handled further down when the
             * response body is processed 08/27/02 jhrg */
            char *start;

            /* Find the first non-space letter */
            for(start=k->p+17;
                *start && isspace((int)*start);
                start++);

            /* Record the content-encoding for later use. 08/27/02 jhrg */
            if (checkprefix("identity", start))
              k->content_encoding = IDENTITY;
            else if (checkprefix("deflate", start))
              k->content_encoding = DEFLATE;
            else if (checkprefix("gzip", start) 
                     || checkprefix("x-gzip", start))
              k->content_encoding = GZIP;
            else if (checkprefix("compress", start) 
                     || checkprefix("x-compress", start))
              k->content_encoding = COMPRESS;
          }
          else if (checkprefix("Content-Range:", k->p)) {
            if (sscanf (k->p+14, " bytes %d-", &k->offset) ||
                sscanf (k->p+14, " bytes: %d-", &k->offset)) {
              /* This second format was added August 1st 2000 by Igor
                 Khristophorov since Sun's webserver JavaWebServer/1.1.1
                 obviously sends the header this way! :-( */
              if (conn->resume_from == k->offset) {
                /* we asked for a resume and we got it */
                k->content_range = TRUE;
              }
            }
          }
          else if(data->cookies &&
                  checkprefix("Set-Cookie:", k->p)) {
            Curl_cookie_add(data->cookies, TRUE, k->p+11, conn->name);
          }
          else if(checkprefix("Last-Modified:", k->p) &&
                  (data->set.timecondition || data->set.get_filetime) ) {
            time_t secs=time(NULL);
            k->timeofdoc = curl_getdate(k->p+strlen("Last-Modified:"),
                                        &secs);
            if(data->set.get_filetime)
              data->info.filetime = k->timeofdoc;
          }
          else if ((k->httpcode >= 300 && k->httpcode < 400) &&
                   (data->set.http_follow_location) &&
                   checkprefix("Location:", k->p)) {
            /* this is the URL that the server advices us to get instead */
            char *ptr;
            char *start=k->p;
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
            if(ptr != start) {
              *ptr = '\0';   /* zero terminate */
              conn->newurl = strdup(start); /* clone string */
              *ptr = backup; /* restore ending letter */
            }
          }

          /*
           * End of header-checks. Write them to the client.
           */

          k->writetype = CLIENTWRITE_HEADER;
          if (data->set.http_include_header)
            k->writetype |= CLIENTWRITE_BODY;

          if(data->set.verbose)
            Curl_debug(data, CURLINFO_HEADER_IN,
                       k->p, k->hbuflen);

          result = Curl_client_write(data, k->writetype, k->p,
                                     k->hbuflen);
          if(result)
            return result;

          data->info.header_size += k->hbuflen;
          conn->headerbytecount += k->hbuflen;
              
          /* reset hbufp pointer && hbuflen */
          k->hbufp = data->state.headerbuff;
          k->hbuflen = 0;
        }
        while (!stop_reading && *k->str); /* header line within buffer */

        if(stop_reading)
          /* We've stopped dealing with input, get out of the do-while loop */
          break;

        /* We might have reached the end of the header part here, but
           there might be a non-header part left in the end of the read
           buffer. */

      }                 /* end if header mode */

      /* This is not an 'else if' since it may be a rest from the header
         parsing, where the beginning of the buffer is headers and the end
         is non-headers. */
      if (k->str && !k->header && (nread > 0)) {
            
        if(0 == k->bodywrites) {
          /* These checks are only made the first time we are about to
             write a piece of the body */
          if(conn->protocol&PROT_HTTP) {
            /* HTTP-only checks */
            if (conn->newurl) {
              /* abort after the headers if "follow Location" is set */
              infof (data, "Follow to new URL: %s\n", conn->newurl);
              k->keepon &= ~KEEP_READ;
              FD_ZERO(&k->rkeepfd);
              *done = TRUE;
              return CURLE_OK;
            }
            else if (conn->resume_from &&
                     !k->content_range &&
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
              if((k->timeofdoc > 0) && (data->set.timevalue > 0)) {
                switch(data->set.timecondition) {
                case TIMECOND_IFMODSINCE:
                default:
                  if(k->timeofdoc < data->set.timevalue) {
                    infof(data,
                          "The requested document is not new enough\n");
                    *done = TRUE;
                    return CURLE_OK;
                  }
                  break;
                case TIMECOND_IFUNMODSINCE:
                  if(k->timeofdoc > data->set.timevalue) {
                    infof(data,
                          "The requested document is not old enough\n");
                    *done = TRUE;
                    return CURLE_OK;
                  }
                  break;
                } /* switch */
              } /* two valid time strings */
            } /* we have a time condition */

          } /* this is HTTP */
        } /* this is the first time we write a body part */
        k->bodywrites++;

        /* pass data to the debug function before it gets "dechunked" */
        if(data->set.verbose) {
          if(k->badheader) {
            Curl_debug(data, CURLINFO_DATA_IN, data->state.headerbuff,
                       k->hbuflen);
            if(k->badheader == HEADER_PARTHEADER)
              Curl_debug(data, CURLINFO_DATA_IN, k->str, nread);
          }
          else
            Curl_debug(data, CURLINFO_DATA_IN, k->str, nread);
        }

        if(conn->bits.chunk) {
          /*
           * Bless me father for I have sinned. Here comes a chunked
           * transfer flying and we need to decode this properly.  While
           * the name says read, this function both reads and writes away
           * the data. The returned 'nread' holds the number of actual
           * data it wrote to the client.  */
          CHUNKcode res =
            Curl_httpchunk_read(conn, k->str, nread, &nread);

          if(CHUNKE_OK < res) {
            if(CHUNKE_WRITE_ERROR == res) {
              failf(data, "Failed writing data");
              return CURLE_WRITE_ERROR;
            }
            failf(data, "Received problem in the chunky parser");
            return CURLE_RECV_ERROR;
          }
          else if(CHUNKE_STOP == res) {
            /* we're done reading chunks! */
            k->keepon &= ~KEEP_READ; /* read no more */
            FD_ZERO(&k->rkeepfd);

            /* There are now possibly N number of bytes at the end of the
               str buffer that weren't written to the client, but we don't
               care about them right now. */
          }
          /* If it returned OK, we just keep going */
        }

        if((-1 != conn->maxdownload) &&
           (k->bytecount + nread >= conn->maxdownload)) {
          nread = conn->maxdownload - k->bytecount;
          if(nread < 0 ) /* this should be unusual */
            nread = 0;

          k->keepon &= ~KEEP_READ; /* we're done reading */
          FD_ZERO(&k->rkeepfd);
        }

        k->bytecount += nread;

        Curl_pgrsSetDownloadCounter(data, (double)k->bytecount);
            
        if(!conn->bits.chunk && (nread || k->badheader)) {
          /* If this is chunky transfer, it was already written */

          if(k->badheader) {
            /* we parsed a piece of data wrongly assuming it was a header
               and now we output it as body instead */
            result = Curl_client_write(data, CLIENTWRITE_BODY,
                                       data->state.headerbuff,
                                       k->hbuflen);
          }
          if(k->badheader < HEADER_ALLBAD) {
            /* This switch handles various content encodings. If there's an
               error here, be sure to check over the almost identical code in
               http_chunk.c. 08/29/02 jhrg */
#ifdef HAVE_LIBZ
            switch (k->content_encoding) {
            case IDENTITY:
#endif
              /* This is the default when the server sends no
                 Content-Encoding header. See Curl_readwrite_init; the
                 memset() call initializes k->content_encoding to zero.
                 08/28/02 jhrg */
              result = Curl_client_write(data, CLIENTWRITE_BODY, k->str, 
                                         nread);
#ifdef HAVE_LIBZ
              break;

            case DEFLATE: 
              /* Assume CLIENTWRITE_BODY; headers are not encoded. */
              result = Curl_unencode_deflate_write(data, k, nread);
              break;

            case GZIP:          /* FIXME 08/27/02 jhrg */
            case COMPRESS:
            default:
              failf (data, "Unrecognized content encoding type. "
                     "libcurl understands `identity' and `deflate' "
                     "content encodings.");
              result = CURLE_BAD_CONTENT_ENCODING;
              break;
            }
#endif
          }
          k->badheader = HEADER_NORMAL; /* taken care of now */

          if(result)
            return result;
        }

      } /* if (! header and data to read ) */
    } /* if( read from socket ) */

    /* If we still have writing to do, we check if we have a writable
       socket. Sometimes the writefdp is NULL, it no fd_set was done using
       the multi interface and then we can do nothing but to attempt a
       write to be sure. */
    if((k->keepon & KEEP_WRITE) &&
       (FD_ISSET(conn->writesockfd, writefdp)) ) {
      /* write */

      int i, si;
      ssize_t bytes_written;

      if ((k->bytecount == 0) && (k->writebytecount == 0))
        Curl_pgrsTime(data, TIMER_STARTTRANSFER);

      didwhat |= KEEP_WRITE;

      /* only read more data if there's no upload data already
         present in the upload buffer */
      if(0 == conn->upload_present) {
        size_t buffersize = BUFSIZE;
        /* init the "upload from here" pointer */
        conn->upload_fromhere = k->uploadbuf;

        if(!k->upload_done) {

          if(conn->bits.upload_chunky) {
            /* if chunked Transfer-Encoding */
            buffersize -= (8 + 2 + 2);   /* 32bit hex + CRLF + CRLF */
            conn->upload_fromhere += 10; /* 32bit hex + CRLF */
          }

          nread = data->set.fread(conn->upload_fromhere, 1,
                                  buffersize, data->set.in);
          
          if(conn->bits.upload_chunky) {
            /* if chunked Transfer-Encoding */
            char hexbuffer[9];
            int hexlen = snprintf(hexbuffer, sizeof(hexbuffer),
                                  "%x\r\n", nread);
            /* move buffer pointer */
            conn->upload_fromhere -= hexlen;
            nread += hexlen;

            /* copy the prefix to the buffer */
            memcpy(conn->upload_fromhere, hexbuffer, hexlen);
            if(nread>0) {
              /* append CRLF to the data */
              memcpy(conn->upload_fromhere +
                     nread, "\r\n", 2);
              nread+=2;
            }
            else {
              /* mark this as done once this chunk is transfered */
              k->upload_done = TRUE;
            }
          }
        }
        else
          nread = 0; /* we're done uploading/reading */

        /* the signed int typecase of nread of for systems that has
           unsigned size_t */
        if (nread<=0) {
          /* done */
          k->keepon &= ~KEEP_WRITE; /* we're done writing */
          FD_ZERO(&k->wkeepfd);
          break;
        }

        /* store number of bytes available for upload */
        conn->upload_present = nread;

        /* convert LF to CRLF if so asked */
        if (data->set.crlf) {
          for(i = 0, si = 0; i < nread; i++, si++) {
            if (conn->upload_fromhere[i] == 0x0a) {
              data->state.scratch[si++] = 0x0d;
              data->state.scratch[si] = 0x0a;
            }
            else
              data->state.scratch[si] = conn->upload_fromhere[i];
          }
          if(si != nread) {
            /* only perform the special operation if we really did replace
               anything */
            nread = si;

            /* upload from the new (replaced) buffer instead */
            conn->upload_fromhere = data->state.scratch;

            /* set the new amount too */
            conn->upload_present = nread;
          }
        }
      }
      else {
        /* We have a partial buffer left from a previous "round". Use
           that instead of reading more data */
      }

      /* write to socket */
      result = Curl_write(conn,
                          conn->writesockfd,
                          conn->upload_fromhere,
                          conn->upload_present,
                          &bytes_written);
      if(result)
        return result;
      else if(conn->upload_present != bytes_written) {
        /* we only wrote a part of the buffer (if anything), deal with it! */

        /* store the amount of bytes left in the buffer to write */
        conn->upload_present -= bytes_written;

        /* advance the pointer where to find the buffer when the next send
           is to happen */
        conn->upload_fromhere += bytes_written;
      }
      else {
        /* we've uploaded that buffer now */
        conn->upload_fromhere = k->uploadbuf;
        conn->upload_present = 0; /* no more bytes left */

        if(k->upload_done) {
          /* switch off writing, we're done! */
          k->keepon &= ~KEEP_WRITE; /* we're done writing */
          FD_ZERO(&k->wkeepfd);
        }
      }

      if(data->set.verbose)
        Curl_debug(data, CURLINFO_DATA_OUT, conn->upload_fromhere,
                   bytes_written);
      

      k->writebytecount += bytes_written;
      Curl_pgrsSetUploadCounter(data, (double)k->writebytecount);

    }

  } while(0); /* just to break out from! */

  if(didwhat) {
    /* Update read/write counters */
    if(conn->bytecountp)
      *conn->bytecountp = k->bytecount; /* read count */
    if(conn->writebytecountp)
      *conn->writebytecountp = k->writebytecount; /* write count */
  }
  else {
    /* no read no write, this is a timeout? */
    if (k->write_after_100_header) {
      /* This should allow some time for the header to arrive, but only a
         very short time as otherwise it'll be too much wasted times too
         often. */
      k->write_after_100_header = FALSE;
      FD_SET (conn->writesockfd, &k->writefd); /* write socket */
      k->keepon |= KEEP_WRITE;
      k->wkeepfd = k->writefd;
    }    
  }

  k->now = Curl_tvnow();
  if(Curl_pgrsUpdate(conn))
    result = CURLE_ABORTED_BY_CALLBACK;
  else
    result = Curl_speedcheck (data, k->now);
  if (result)
    return result;
    
  if (data->set.timeout &&
      ((Curl_tvdiff(k->now, k->start)/1000) >= data->set.timeout)) {
    failf (data, "Operation timed out with %d out of %d bytes received",
           k->bytecount, conn->size);
    return CURLE_OPERATION_TIMEOUTED;
  }

  if(!k->keepon) {
    /*
     * The transfer has been performed. Just make some general checks before
     * returning.
     */

    if(!(data->set.no_body) && k->contentlength &&
       (k->bytecount != k->contentlength) &&
       !conn->newurl) {
      failf(data, "transfer closed with %d bytes remaining to read",
            k->contentlength-k->bytecount);
      return CURLE_PARTIAL_FILE;
    }
    else if(conn->bits.chunk && conn->proto.http->chunk.datasize) {
      failf(data, "transfer closed with at least %d bytes remaining",
            conn->proto.http->chunk.datasize);
      return CURLE_PARTIAL_FILE;
    }
    if(Curl_pgrsUpdate(conn))
      return CURLE_ABORTED_BY_CALLBACK;
  }

  /* Now update the "done" boolean we return */
  *done = !k->keepon;

  return CURLE_OK;
}