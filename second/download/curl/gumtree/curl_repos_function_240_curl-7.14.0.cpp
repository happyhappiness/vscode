CURLcode Curl_readwrite(struct connectdata *conn,
                        bool *done)
{
  struct Curl_transfer_keeper *k = &conn->keep;
  struct SessionHandle *data = conn->data;
  CURLcode result;
  ssize_t nread; /* number of bytes read */
  int didwhat=0;

  curl_socket_t fd_read;
  curl_socket_t fd_write;
  curl_socket_t select_res;

  curl_off_t contentlength;

  if(k->keepon & KEEP_READ)
    fd_read = conn->sockfd;
  else
    fd_read = CURL_SOCKET_BAD;

  if(k->keepon & KEEP_WRITE)
    fd_write = conn->writesockfd;
  else
    fd_write = CURL_SOCKET_BAD;

  select_res = Curl_select(fd_read, fd_write, 0);
  if(select_res == CSELECT_ERR) {
    failf(data, "select/poll returned error");
    return CURLE_SEND_ERROR;
  }

  do {
    /* If we still have reading to do, we check if we have a readable
       socket. */
    if((k->keepon & KEEP_READ) && (select_res & CSELECT_IN)) {

      bool is_empty_data = FALSE;

      /* This is where we loop until we have read everything there is to
         read or we get a EWOULDBLOCK */
      do {
        size_t buffersize = data->set.buffer_size?
          data->set.buffer_size:BUFSIZE;

        /* receive data from the network! */
        int readrc = Curl_read(conn, conn->sockfd, k->buf, buffersize, &nread);

        /* subzero, this would've blocked */
        if(0>readrc)
          break; /* get out of loop */

        /* get the CURLcode from the int */
        result = (CURLcode)readrc;

        if(result>0)
          return result;

        if ((k->bytecount == 0) && (k->writebytecount == 0)) {
          Curl_pgrsTime(data, TIMER_STARTTRANSFER);
          if(k->wait100_after_headers)
            /* set time stamp to compare with when waiting for the 100 */
            k->start100 = Curl_tvnow();
        }

        didwhat |= KEEP_READ;
        /* indicates data of zero size, i.e. empty file */
        is_empty_data = (nread == 0 && k->bodywrites == 0);

        /* NULL terminate, allowing string ops to be used */
        if (0 < nread || is_empty_data)
          k->buf[nread] = 0;

        /* if we receive 0 or less here, the server closed the connection and
           we bail out from this! */
        else if (0 >= nread) {
          k->keepon &= ~KEEP_READ;
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
            size_t hbufp_index;
            size_t rest_length;
            size_t full_length;
            int writetype;

            /* str_start is start of line within buf */
            k->str_start = k->str;

            k->end_ptr = strchr (k->str_start, '\n');

            if (!k->end_ptr) {
              /* Not a complete header line within buffer, append the data to
                 the end of the headerbuff. */

              if (k->hbuflen + nread >= data->state.headersize) {
                /* We enlarge the header buffer as it is too small */
                char *newbuff;
                size_t newsize=CURLMAX((k->hbuflen+nread)*3/2,
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
                if(!checkhttpprefix(data, data->state.headerbuff)) {
                  /* this is not the beginning of a HTTP first header line */
                  k->header = FALSE;
                  k->badheader = HEADER_ALLBAD;
                  break;
                }
              }

              break; /* read more and try again */
            }

            /* decrease the size of the remaining (supposed) header line */
            rest_length = (k->end_ptr - k->str)+1;
            nread -= (ssize_t)rest_length;

            k->str = k->end_ptr + 1; /* move past new line */

            full_length = k->str - k->str_start;

            /*
             * We're about to copy a chunk of data to the end of the
             * already received header. We make sure that the full string
             * fit in the allocated header buffer, or else we enlarge
             * it.
             */
            if (k->hbuflen + full_length >=
                data->state.headersize) {
              char *newbuff;
              size_t newsize=CURLMAX((k->hbuflen+full_length)*3/2,
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
            strncpy (k->hbufp, k->str_start, full_length);
            k->hbufp += full_length;
            k->hbuflen += full_length;
            *k->hbufp = 0;
            k->end_ptr = k->hbufp;

            k->p = data->state.headerbuff;

            /****
             * We now have a FULL header line that p points to
             *****/

            if(!k->headerline) {
              /* the first read header */
              if((k->hbuflen>5) &&
                 !checkhttpprefix(data, data->state.headerbuff)) {
                /* this is not the beginning of a HTTP first header line */
                k->header = FALSE;
                if(nread)
                  /* since there's more, this is a partial bad header */
                  k->badheader = HEADER_PARTHEADER;
                else {
                  /* this was all we read so its all a bad header */
                  k->badheader = HEADER_ALLBAD;
                  nread = (ssize_t)rest_length;
                }
                break;
              }
            }

            if (('\n' == *k->p) || ('\r' == *k->p)) {
              size_t headerlen;
              /* Zero-length header line means end of headers! */

              if ('\r' == *k->p)
                k->p++; /* pass the \r byte */
              if ('\n' == *k->p)
                k->p++; /* pass the \n byte */

              if(100 == k->httpcode) {
                /*
                 * We have made a HTTP PUT or POST and this is 1.1-lingo
                 * that tells us that the server is OK with this and ready
                 * to receive the data.
                 * However, we'll get more headers now so we must get
                 * back into the header-parsing state!
                 */
                k->header = TRUE;
                k->headerline = 0; /* restart the header line counter */
                /* if we did wait for this do enable write now! */
                if (k->write_after_100_header) {

                  k->write_after_100_header = FALSE;
                  k->keepon |= KEEP_WRITE;
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
              }

#ifndef CURL_DISABLE_HTTP
              /*
               * When all the headers have been parsed, see if we should give
               * up and return an error.
               */
              if (Curl_http_should_fail(conn)) {
                failf (data, "The requested URL returned error: %d",
                       k->httpcode);
                return CURLE_HTTP_RETURNED_ERROR;
              }
#endif   /* CURL_DISABLE_HTTP */

              /* now, only output this if the header AND body are requested:
               */
              writetype = CLIENTWRITE_HEADER;
              if (data->set.include_header)
                writetype |= CLIENTWRITE_BODY;

              headerlen = k->p - data->state.headerbuff;

              result = Curl_client_write(data, writetype,
                                         data->state.headerbuff,
                                         headerlen);
              if(result)
                return result;

              data->info.header_size += (long)headerlen;
              conn->headerbytecount += (long)headerlen;

              conn->deductheadercount =
                (100 == k->httpcode)?conn->headerbytecount:0;

              if (conn->resume_from &&
                  (data->set.httpreq==HTTPREQ_GET) &&
                  (k->httpcode == 416)) {
                /* "Requested Range Not Satisfiable" */
                stop_reading = TRUE;
              }

#ifndef CURL_DISABLE_HTTP
              if(!stop_reading) {
                /* Curl_http_auth_act() checks what authentication methods
                 * that are available and decides which one (if any) to
                 * use. It will set 'newurl' if an auth metod was picked. */
                result = Curl_http_auth_act(conn);

                if(result)
                  return result;

                if(conn->bits.rewindaftersend) {
                  /* We rewind after a complete send, so thus we continue
                     sending now */
                  infof(data, "Keep sending data to get tossed away!\n");
                  k->keepon |= KEEP_WRITE;
                }
              }
#endif   /* CURL_DISABLE_HTTP */

              if(!k->header) {
                /*
                 * really end-of-headers.
                 *
                 * If we requested a "no body", this is a good time to get
                 * out and return home.
                 */
                if(conn->bits.no_body)
                  stop_reading = TRUE;
                else {
                  /* If we know the expected size of this document, we set the
                     maximum download size to the size of the expected
                     document or else, we won't know when to stop reading!

                     Note that we set the download maximum even if we read a
                     "Connection: close" header, to make sure that
                     "Content-Length: 0" still prevents us from attempting to
                     read the (missing) response-body.
                  */
                  /* According to RFC2616 section 4.4, we MUST ignore
                     Content-Length: headers if we are now receiving data
                     using chunked Transfer-Encoding.
                  */
                  if(conn->bits.chunk)
                    conn->size=-1;

                }
                if(-1 != conn->size) {
                  /* We do this operation even if no_body is true, since this
                     data might be retrieved later with curl_easy_getinfo()
                     and its CURLINFO_CONTENT_LENGTH_DOWNLOAD option. */

                  Curl_pgrsSetDownloadSize(data, conn->size);
                  conn->maxdownload = conn->size;
                }
                /* If max download size is *zero* (nothing) we already
                   have nothing and can safely return ok now! */
                if(0 == conn->maxdownload)
                  stop_reading = TRUE;

                if(stop_reading) {
                  /* we make sure that this socket isn't read more now */
                  k->keepon &= ~KEEP_READ;
                }

                break;          /* exit header line loop */
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
              int nc=sscanf(k->p, " HTTP/%d.%d %3d",
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
                nc=sscanf(k->p, " HTTP %3d", &k->httpcode);
                k->httpversion = 10;

               /* If user has set option HTTP200ALIASES,
                  compare header line against list of aliases
               */
                if (!nc) {
                  if (checkhttpprefix(data, k->p)) {
                    nc = 1;
                    k->httpcode = 200;
                    k->httpversion =
                      (data->set.httpversion==CURL_HTTP_VERSION_1_0)? 10 : 11;
                  }
                }
              }

              if (nc) {
                data->info.httpcode = k->httpcode;
                data->info.httpversion = k->httpversion;

                /*
                 * This code executes as part of processing the header.  As a
                 * result, it's not totally clear how to interpret the
                 * response code yet as that depends on what other headers may
                 * be present.  401 and 407 may be errors, but may be OK
                 * depending on how authentication is working.  Other codes
                 * are definitely errors, so give up here.
                 */
                if (data->set.http_fail_on_error &&
                    (k->httpcode >= 400) &&
                    (k->httpcode != 401) &&
                    (k->httpcode != 407)) {

                  if (conn->resume_from &&
                      (data->set.httpreq==HTTPREQ_GET) &&
                      (k->httpcode == 416)) {
                    /* "Requested Range Not Satisfiable", just proceed and
                       pretend this is no error */
                  }
                  else {
                    /* serious error, go home! */
                    failf (data, "The requested URL returned error: %d",
                           k->httpcode);
                    return CURLE_HTTP_RETURNED_ERROR;
                  }
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
                case 416: /* Requested Range Not Satisfiable, it has the
                             Content-Length: set as the "real" document but no
                             actual response is sent. */
                case 304:
                  /* (quote from RFC2616, section 10.3.5): The 304 response
                   * MUST NOT contain a message-body, and thus is always
                   * terminated by the first empty line after the header
                   * fields.  */
                  conn->size=0;
                  conn->maxdownload=0;
                  k->ignorecl = TRUE; /* ignore Content-Length headers */
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

            /* Check for Content-Length: header lines to get size. Ignore
               the header completely if we get a 416 response as then we're
               resuming a document that we don't get, and this header contains
               info about the true size of the document we didn't get now. */
            if (!k->ignorecl &&
                checkprefix("Content-Length:", k->p)) {
              contentlength = curlx_strtoofft(k->p+15, NULL, 10);
              if (data->set.max_filesize &&
                  contentlength > data->set.max_filesize) {
                failf(data, "Maximum file size exceeded");
                return CURLE_FILESIZE_EXCEEDED;
              }
              if(contentlength >= 0)
                conn->size = contentlength;
              else {
                /* Negative Content-Length is really odd, and we know it
                   happens for example when older Apache servers send large
                   files */
                conn->bits.close = TRUE;
                infof(data, "Negative content-length: %" FORMAT_OFF_T
                      ", closing after transfer\n", contentlength);
              }
            }
            /* check for Content-Type: header lines to get the mime-type */
            else if (checkprefix("Content-Type:", k->p)) {
              char *start;
              char *end;
              size_t len;

              /* Find the first non-space letter */
              for(start=k->p+13;
                  *start && isspace((int)*start);
                  start++)
                ;  /* empty loop */

              end = strchr(start, '\r');
              if(!end)
                end = strchr(start, '\n');

              if(end) {
                /* skip all trailing space letters */
                for(; isspace((int)*end) && (end > start); end--)
                  ;  /* empty loop */

                /* get length of the type */
                len = end-start+1;

                /* allocate memory of a cloned copy */
                Curl_safefree(data->info.contenttype);

                data->info.contenttype = malloc(len + 1);
                if (NULL == data->info.contenttype)
                  return CURLE_OUT_OF_MEMORY;

                /* copy the content-type string */
                memcpy(data->info.contenttype, start, len);
                data->info.contenttype[len] = 0; /* zero terminate */
              }
            }
#ifndef CURL_DISABLE_HTTP
            else if((k->httpversion == 10) &&
                    conn->bits.httpproxy &&
                    Curl_compareheader(k->p,
                                       "Proxy-Connection:", "keep-alive")) {
              /*
               * When a HTTP/1.0 reply comes when using a proxy, the
               * 'Proxy-Connection: keep-alive' line tells us the
               * connection will be kept alive for our pleasure.
               * Default action for 1.0 is to close.
               */
              conn->bits.close = FALSE; /* don't close when done */
              infof(data, "HTTP/1.0 proxy connection set to keep alive!\n");
            }
            else if((k->httpversion == 11) &&
                    conn->bits.httpproxy &&
                    Curl_compareheader(k->p,
                                       "Proxy-Connection:", "close")) {
              /*
               * We get a HTTP/1.1 response from a proxy and it says it'll
               * close down after this transfer.
               */
              conn->bits.close = TRUE; /* close when done */
              infof(data, "HTTP/1.1 proxy connection set close!\n");
            }
            else if((k->httpversion == 10) &&
                    Curl_compareheader(k->p, "Connection:", "keep-alive")) {
              /*
               * A HTTP/1.0 reply with the 'Connection: keep-alive' line
               * tells us the connection will be kept alive for our
               * pleasure.  Default action for 1.0 is to close.
               *
               * [RFC2068, section 19.7.1] */
              conn->bits.close = FALSE; /* don't close when done */
              infof(data, "HTTP/1.0 connection set to keep alive!\n");
            }
            else if (Curl_compareheader(k->p, "Connection:", "close")) {
              /*
               * [RFC 2616, section 8.1.2.1]
               * "Connection: close" is HTTP/1.1 language and means that
               * the connection will close when this request has been
               * served.
               */
              conn->bits.close = TRUE; /* close when done */
            }
            else if (Curl_compareheader(k->p,
                                        "Transfer-Encoding:", "chunked")) {
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
               * Process Content-Encoding. Look for the values: identity,
               * gzip, deflate, compress, x-gzip and x-compress. x-gzip and
               * x-compress are the same as gzip and compress. (Sec 3.5 RFC
               * 2616). zlib cannot handle compress.  However, errors are
               * handled further down when the response body is processed
               */
              char *start;

              /* Find the first non-space letter */
              for(start=k->p+17;
                  *start && isspace((int)*start);
                  start++)
                ;  /* empty loop */

              /* Record the content-encoding for later use */
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
            else if (Curl_compareheader(k->p, "Content-Range:", "bytes")) {
              /* Content-Range: bytes [num]-
                 Content-Range: bytes: [num]-

                 The second format was added August 1st 2000 by Igor
                 Khristophorov since Sun's webserver JavaWebServer/1.1.1
                 obviously sends the header this way! :-( */

              char *ptr = strstr(k->p, "bytes");
              ptr+=5;

              if(*ptr == ':')
                /* stupid colon skip */
                ptr++;

              k->offset = curlx_strtoofft(ptr, NULL, 10);

              if (conn->resume_from == k->offset)
                /* we asked for a resume and we got it */
                k->content_range = TRUE;
            }
#if !defined(CURL_DISABLE_COOKIES)
            else if(data->cookies &&
                    checkprefix("Set-Cookie:", k->p)) {
              Curl_share_lock(data, CURL_LOCK_DATA_COOKIE,
                              CURL_LOCK_ACCESS_SINGLE);
              Curl_cookie_add(data,
                              data->cookies, TRUE, k->p+11,
                              /* If there is a custom-set Host: name, use it
                                 here, or else use real peer host name. */
                              conn->allocptr.cookiehost?
                              conn->allocptr.cookiehost:conn->host.name,
                              conn->path);
              Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
            }
#endif
            else if(checkprefix("Last-Modified:", k->p) &&
                    (data->set.timecondition || data->set.get_filetime) ) {
              time_t secs=time(NULL);
              k->timeofdoc = curl_getdate(k->p+strlen("Last-Modified:"),
                                          &secs);
              if(data->set.get_filetime)
                data->info.filetime = (long)k->timeofdoc;
            }
            else if((checkprefix("WWW-Authenticate:", k->p) &&
                     (401 == k->httpcode)) ||
                    (checkprefix("Proxy-authenticate:", k->p) &&
                     (407 == k->httpcode))) {
              result = Curl_http_input_auth(conn, k->httpcode, k->p);
              if(result)
                return result;
            }
            else if ((k->httpcode >= 300 && k->httpcode < 400) &&
                     checkprefix("Location:", k->p)) {
              if(data->set.http_follow_location) {
                /* this is the URL that the server advices us to get instead */
                char *ptr;
                char *start=k->p;
                char backup;

                start += 9; /* pass "Location:" */

                /* Skip spaces and tabs. We do this to support multiple
                   white spaces after the "Location:" keyword. */
                while(*start && isspace((int)*start ))
                  start++;

                /* Scan through the string from the end to find the last
                   non-space. k->end_ptr points to the actual terminating zero
                   letter, move pointer one letter back and start from
                   there. This logic strips off trailing whitespace, but keeps
                   any embedded whitespace. */
                ptr = k->end_ptr-1;
                while((ptr>=start) && isspace((int)*ptr))
                  ptr--;
                ptr++;

                backup = *ptr; /* store the ending letter */
                if(ptr != start) {
                  *ptr = '\0';   /* zero terminate */
                  conn->newurl = strdup(start); /* clone string */
                  *ptr = backup; /* restore ending letter */
                  if(!conn->newurl)
                    return CURLE_OUT_OF_MEMORY;
                }
              }
            }
#endif   /* CURL_DISABLE_HTTP */

            /*
             * End of header-checks. Write them to the client.
             */

            writetype = CLIENTWRITE_HEADER;
            if (data->set.include_header)
              writetype |= CLIENTWRITE_BODY;

            if(data->set.verbose)
              Curl_debug(data, CURLINFO_HEADER_IN,
                         k->p, k->hbuflen, conn);

            result = Curl_client_write(data, writetype, k->p, k->hbuflen);
            if(result)
              return result;

            data->info.header_size += (long)k->hbuflen;
            conn->headerbytecount += (long)k->hbuflen;

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

        }                       /* end if header mode */

        /* This is not an 'else if' since it may be a rest from the header
           parsing, where the beginning of the buffer is headers and the end
           is non-headers. */
        if (k->str && !k->header && (nread > 0 || is_empty_data)) {

          if(0 == k->bodywrites && !is_empty_data) {
            /* These checks are only made the first time we are about to
               write a piece of the body */
            if(conn->protocol&PROT_HTTP) {
              /* HTTP-only checks */

              if (conn->newurl) {
                if(conn->bits.close) {
                  /* Abort after the headers if "follow Location" is set
                     and we're set to close anyway. */
                  k->keepon &= ~KEEP_READ;
                  *done = TRUE;
                  return CURLE_OK;
                }
                /* We have a new url to load, but since we want to be able
                   to re-use this connection properly, we read the full
                   response in "ignore more" */
                k->ignorebody = TRUE;
                infof(data, "Ignoring the response-body\n");
              }
              if (conn->resume_from && !k->content_range &&
                  (data->set.httpreq==HTTPREQ_GET) &&
                  !k->ignorebody) {
                /* we wanted to resume a download, although the server doesn't
                 * seem to support this and we did this with a GET (if it
                 * wasn't a GET we did a POST or PUT resume) */
                failf(data, "HTTP server doesn't seem to support "
                      "byte ranges. Cannot resume.");
                return CURLE_HTTP_RANGE_ERROR;
              }

              if(data->set.timecondition && !conn->range) {
                /* A time condition has been set AND no ranges have been
                   requested. This seems to be what chapter 13.3.4 of
                   RFC 2616 defines to be the correct action for a
                   HTTP/1.1 client */
                if((k->timeofdoc > 0) && (data->set.timevalue > 0)) {
                  switch(data->set.timecondition) {
                  case CURL_TIMECOND_IFMODSINCE:
                  default:
                    if(k->timeofdoc < data->set.timevalue) {
                      infof(data,
                            "The requested document is not new enough\n");
                      *done = TRUE;
                      return CURLE_OK;
                    }
                    break;
                  case CURL_TIMECOND_IFUNMODSINCE:
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
                         k->hbuflen, conn);
              if(k->badheader == HEADER_PARTHEADER)
                Curl_debug(data, CURLINFO_DATA_IN, k->str, nread, conn);
            }
            else
              Curl_debug(data, CURLINFO_DATA_IN, k->str, nread, conn);
          }

#ifndef CURL_DISABLE_HTTP
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
              failf(data, "Received problem %d in the chunky parser", res);
              return CURLE_RECV_ERROR;
            }
            else if(CHUNKE_STOP == res) {
              /* we're done reading chunks! */
              k->keepon &= ~KEEP_READ; /* read no more */

              /* There are now possibly N number of bytes at the end of the
                 str buffer that weren't written to the client, but we don't
                 care about them right now. */
            }
            /* If it returned OK, we just keep going */
          }
#endif   /* CURL_DISABLE_HTTP */

          if((-1 != conn->maxdownload) &&
             (k->bytecount + nread >= conn->maxdownload)) {
            nread = (ssize_t) (conn->maxdownload - k->bytecount);
            if(nread < 0 ) /* this should be unusual */
              nread = 0;

            k->keepon &= ~KEEP_READ; /* we're done reading */
          }

          k->bytecount += nread;

          Curl_pgrsSetDownloadCounter(data, k->bytecount);

          if(!conn->bits.chunk && (nread || k->badheader || is_empty_data)) {
            /* If this is chunky transfer, it was already written */

            if(k->badheader && !k->ignorebody) {
              /* we parsed a piece of data wrongly assuming it was a header
                 and now we output it as body instead */
              result = Curl_client_write(data, CLIENTWRITE_BODY,
                                         data->state.headerbuff,
                                         k->hbuflen);
            }
            if(k->badheader < HEADER_ALLBAD) {
              /* This switch handles various content encodings. If there's an
                 error here, be sure to check over the almost identical code
                 in http_chunks.c.
                 Make sure that ALL_CONTENT_ENCODINGS contains all the
                 encodings handled here. */
#ifdef HAVE_LIBZ
              switch (k->content_encoding) {
              case IDENTITY:
#endif
                /* This is the default when the server sends no
                   Content-Encoding header. See Curl_readwrite_init; the
                   memset() call initializes k->content_encoding to zero. */
                if(!k->ignorebody)
                  result = Curl_client_write(data, CLIENTWRITE_BODY, k->str,
                                             nread);
#ifdef HAVE_LIBZ
                break;

              case DEFLATE:
                /* Assume CLIENTWRITE_BODY; headers are not encoded. */
                result = Curl_unencode_deflate_write(data, k, nread);
                break;

              case GZIP:
                /* Assume CLIENTWRITE_BODY; headers are not encoded. */
                result = Curl_unencode_gzip_write(data, k, nread);
                break;

              case COMPRESS:
              default:
                failf (data, "Unrecognized content encoding type. "
                       "libcurl understands `identity', `deflate' and `gzip' "
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

        if (is_empty_data) {
          /* if we received nothing, the server closed the connection and we
             are done */
          k->keepon &= ~KEEP_READ;
        }

      } while(data_pending(conn));

    } /* if( read from socket ) */

    /* If we still have writing to do, we check if we have a writable
       socket. */
    if((k->keepon & KEEP_WRITE) && (select_res & CSELECT_OUT)) {
      /* write */

      int i, si;
      ssize_t bytes_written;
      bool writedone=TRUE;

      if ((k->bytecount == 0) && (k->writebytecount == 0))
        Curl_pgrsTime(data, TIMER_STARTTRANSFER);

      didwhat |= KEEP_WRITE;

      /*
       * We loop here to do the READ and SEND loop until we run out of
       * data to send or until we get EWOULDBLOCK back
       */
      do {

        /* only read more data if there's no upload data already
           present in the upload buffer */
        if(0 == conn->upload_present) {
          /* init the "upload from here" pointer */
          conn->upload_fromhere = k->uploadbuf;

          if(!k->upload_done) {
            /* HTTP pollution, this should be written nicer to become more
               protocol agnostic. */
            int fillcount;

            if(k->wait100_after_headers &&
               (conn->proto.http->sending == HTTPSEND_BODY)) {
              /* If this call is to send body data, we must take some action:
                 We have sent off the full HTTP 1.1 request, and we shall now
                 go into the Expect: 100 state and await such a header */
              k->wait100_after_headers = FALSE; /* headers sent */
              k->write_after_100_header = TRUE; /* wait for the header */
              k->keepon &= ~KEEP_WRITE;         /* disable writing */
              k->start100 = Curl_tvnow();       /* timeout count starts now */
              didwhat &= ~KEEP_WRITE;  /* we didn't write anything actually */
              break;
            }

            result = Curl_fillreadbuffer(conn, BUFSIZE, &fillcount);
            if(result)
              return result;

            nread = (ssize_t)fillcount;
          }
          else
            nread = 0; /* we're done uploading/reading */

          /* the signed int typecase of nread of for systems that has
             unsigned size_t */
          if (nread<=0) {
            /* done */
            k->keepon &= ~KEEP_WRITE; /* we're done writing */
            writedone = TRUE;

            if(conn->bits.rewindaftersend) {
              result = Curl_readrewind(conn);
              if(result)
                return result;
            }
            break;
          }

          /* store number of bytes available for upload */
          conn->upload_present = nread;

          /* convert LF to CRLF if so asked */
          if (data->set.crlf) {
              if(data->state.scratch == NULL)
                data->state.scratch = malloc(2*BUFSIZE);
              if(data->state.scratch == NULL) {
                failf (data, "Failed to alloc scratch buffer!");
                return CURLE_OUT_OF_MEMORY;
              }
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

        /* write to socket (send away data) */
        result = Curl_write(conn,
                            conn->writesockfd,     /* socket to send to */
                            conn->upload_fromhere, /* buffer pointer */
                            conn->upload_present,  /* buffer size */
                            &bytes_written);       /* actually send away */
        if(result)
          return result;

        if(data->set.verbose)
          /* show the data before we change the pointer upload_fromhere */
          Curl_debug(data, CURLINFO_DATA_OUT, conn->upload_fromhere,
                     bytes_written, conn);

        if(conn->upload_present != bytes_written) {
          /* we only wrote a part of the buffer (if anything), deal with it! */

          /* store the amount of bytes left in the buffer to write */
          conn->upload_present -= bytes_written;

          /* advance the pointer where to find the buffer when the next send
             is to happen */
          conn->upload_fromhere += bytes_written;

          writedone = TRUE; /* we are done, stop the loop */
        }
        else {
          /* we've uploaded that buffer now */
          conn->upload_fromhere = k->uploadbuf;
          conn->upload_present = 0; /* no more bytes left */

          if(k->upload_done) {
            /* switch off writing, we're done! */
            k->keepon &= ~KEEP_WRITE; /* we're done writing */
            writedone = TRUE;
          }
        }

        k->writebytecount += bytes_written;
        Curl_pgrsSetUploadCounter(data, k->writebytecount);

      } while(!writedone); /* loop until we're done writing! */

    }

  } while(0); /* just to break out from! */

  k->now = Curl_tvnow();
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

      /* Quoting RFC2616, section "8.2.3 Use of the 100 (Continue) Status":

      Therefore, when a client sends this header field to an origin server
      (possibly via a proxy) from which it has never seen a 100 (Continue)
      status, the client SHOULD NOT wait for an indefinite period before
      sending the request body.

      */

      long ms = Curl_tvdiff(k->now, k->start100);
      if(ms > CURL_TIMEOUT_EXPECT_100) {
        /* we've waited long enough, continue anyway */
        k->write_after_100_header = FALSE;
        k->keepon |= KEEP_WRITE;
      }
    }
  }

  if(Curl_pgrsUpdate(conn))
    result = CURLE_ABORTED_BY_CALLBACK;
  else
    result = Curl_speedcheck(data, k->now);
  if (result)
    return result;

  if (data->set.timeout &&
      ((Curl_tvdiff(k->now, k->start)/1000) >= data->set.timeout)) {
    failf(data, "Operation timed out with %" FORMAT_OFF_T
          " out of %" FORMAT_OFF_T " bytes received",
          k->bytecount, conn->size);
    return CURLE_OPERATION_TIMEOUTED;
  }

  if(!k->keepon) {
    /*
     * The transfer has been performed. Just make some general checks before
     * returning.
     */

    if(!(conn->bits.no_body) && (conn->size != -1) &&
       (k->bytecount != conn->size) &&
       !conn->newurl) {
      failf(data, "transfer closed with %" FORMAT_OFF_T
            " bytes remaining to read",
            conn->size - k->bytecount);
      return CURLE_PARTIAL_FILE;
    }
    else if(!(conn->bits.no_body) &&
            conn->bits.chunk &&
            (conn->proto.http->chunk.state != CHUNK_STOP)) {
      /*
       * In chunked mode, return an error if the connection is closed prior to
       * the empty (terminiating) chunk is read.
       *
       * The condition above used to check for
       * conn->proto.http->chunk.datasize != 0 which is true after reading
       * *any* chunk, not just the empty chunk.
       *
       */
      failf(data, "transfer closed with outstanding read data remaining");
      return CURLE_PARTIAL_FILE;
    }
    if(Curl_pgrsUpdate(conn))
      return CURLE_ABORTED_BY_CALLBACK;
  }

  /* Now update the "done" boolean we return */
  *done = !k->keepon;

  return CURLE_OK;
}