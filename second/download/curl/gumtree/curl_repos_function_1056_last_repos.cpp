static CURLcode readwrite_data(struct Curl_easy *data,
                               struct connectdata *conn,
                               struct SingleRequest *k,
                               int *didwhat, bool *done,
                               bool *comeback)
{
  CURLcode result = CURLE_OK;
  ssize_t nread; /* number of bytes read */
  size_t excess = 0; /* excess bytes read */
  bool is_empty_data = FALSE;
  bool readmore = FALSE; /* used by RTP to signal for more data */
  int maxloops = 100;

  *done = FALSE;
  *comeback = FALSE;

  /* This is where we loop until we have read everything there is to
     read or we get a CURLE_AGAIN */
  do {
    size_t buffersize = data->set.buffer_size;
    size_t bytestoread = buffersize;

    if(
#if defined(USE_NGHTTP2)
       /* For HTTP/2, read data without caring about the content
          length. This is safe because body in HTTP/2 is always
          segmented thanks to its framing layer. Meanwhile, we have to
          call Curl_read to ensure that http2_handle_stream_close is
          called when we read all incoming bytes for a particular
          stream. */
       !((conn->handler->protocol & PROTO_FAMILY_HTTP) &&
         conn->httpversion == 20) &&
#endif
       k->size != -1 && !k->header) {
      /* make sure we don't read "too much" if we can help it since we
         might be pipelining and then someone else might want to read what
         follows! */
      curl_off_t totalleft = k->size - k->bytecount;
      if(totalleft < (curl_off_t)bytestoread)
        bytestoread = (size_t)totalleft;
    }

    if(bytestoread) {
      /* receive data from the network! */
      result = Curl_read(conn, conn->sockfd, k->buf, bytestoread, &nread);

      /* read would've blocked */
      if(CURLE_AGAIN == result)
        break; /* get out of loop */

      if(result>0)
        return result;
    }
    else {
      /* read nothing but since we wanted nothing we consider this an OK
         situation to proceed from */
      DEBUGF(infof(data, "readwrite_data: we're done!\n"));
      nread = 0;
    }

    if((k->bytecount == 0) && (k->writebytecount == 0)) {
      Curl_pgrsTime(data, TIMER_STARTTRANSFER);
      if(k->exp100 > EXP100_SEND_DATA)
        /* set time stamp to compare with when waiting for the 100 */
        k->start100 = Curl_tvnow();
    }

    *didwhat |= KEEP_RECV;
    /* indicates data of zero size, i.e. empty file */
    is_empty_data = ((nread == 0) && (k->bodywrites == 0)) ? TRUE : FALSE;

    /* NUL terminate, allowing string ops to be used */
    if(0 < nread || is_empty_data) {
      k->buf[nread] = 0;
    }
    else if(0 >= nread) {
      /* if we receive 0 or less here, the server closed the connection
         and we bail out from this! */
      DEBUGF(infof(data, "nread <= 0, server closed connection, bailing\n"));
      k->keepon &= ~KEEP_RECV;
      break;
    }

    /* Default buffer to use when we write the buffer, it may be changed
       in the flow below before the actual storing is done. */
    k->str = k->buf;

    if(conn->handler->readwrite) {
      result = conn->handler->readwrite(data, conn, &nread, &readmore);
      if(result)
        return result;
      if(readmore)
        break;
    }

#ifndef CURL_DISABLE_HTTP
    /* Since this is a two-state thing, we check if we are parsing
       headers at the moment or not. */
    if(k->header) {
      /* we are in parse-the-header-mode */
      bool stop_reading = FALSE;
      result = Curl_http_readwrite_headers(data, conn, &nread, &stop_reading);
      if(result)
        return result;

      if(conn->handler->readwrite &&
         (k->maxdownload <= 0 && nread > 0)) {
        result = conn->handler->readwrite(data, conn, &nread, &readmore);
        if(result)
          return result;
        if(readmore)
          break;
      }

      if(stop_reading) {
        /* We've stopped dealing with input, get out of the do-while loop */

        if(nread > 0) {
          if(Curl_pipeline_wanted(conn->data->multi, CURLPIPE_HTTP1)) {
            infof(data,
                  "Rewinding stream by : %zd"
                  " bytes on url %s (zero-length body)\n",
                  nread, data->state.path);
            read_rewind(conn, (size_t)nread);
          }
          else {
            infof(data,
                  "Excess found in a non pipelined read:"
                  " excess = %zd"
                  " url = %s (zero-length body)\n",
                  nread, data->state.path);
          }
        }

        break;
      }
    }
#endif /* CURL_DISABLE_HTTP */


    /* This is not an 'else if' since it may be a rest from the header
       parsing, where the beginning of the buffer is headers and the end
       is non-headers. */
    if(k->str && !k->header && (nread > 0 || is_empty_data)) {

      if(data->set.opt_no_body) {
        /* data arrives although we want none, bail out */
        streamclose(conn, "ignoring body");
        *done = TRUE;
        return CURLE_WEIRD_SERVER_REPLY;
      }

#ifndef CURL_DISABLE_HTTP
      if(0 == k->bodywrites && !is_empty_data) {
        /* These checks are only made the first time we are about to
           write a piece of the body */
        if(conn->handler->protocol&(PROTO_FAMILY_HTTP|CURLPROTO_RTSP)) {
          /* HTTP-only checks */

          if(data->req.newurl) {
            if(conn->bits.close) {
              /* Abort after the headers if "follow Location" is set
                 and we're set to close anyway. */
              k->keepon &= ~KEEP_RECV;
              *done = TRUE;
              return CURLE_OK;
            }
            /* We have a new url to load, but since we want to be able
               to re-use this connection properly, we read the full
               response in "ignore more" */
            k->ignorebody = TRUE;
            infof(data, "Ignoring the response-body\n");
          }
          if(data->state.resume_from && !k->content_range &&
             (data->set.httpreq == HTTPREQ_GET) &&
             !k->ignorebody) {

            if(k->size == data->state.resume_from) {
              /* The resume point is at the end of file, consider this fine
                 even if it doesn't allow resume from here. */
              infof(data, "The entire document is already downloaded");
              connclose(conn, "already downloaded");
              /* Abort download */
              k->keepon &= ~KEEP_RECV;
              *done = TRUE;
              return CURLE_OK;
            }

            /* we wanted to resume a download, although the server doesn't
             * seem to support this and we did this with a GET (if it
             * wasn't a GET we did a POST or PUT resume) */
            failf(data, "HTTP server doesn't seem to support "
                  "byte ranges. Cannot resume.");
            return CURLE_RANGE_ERROR;
          }

          if(data->set.timecondition && !data->state.range) {
            /* A time condition has been set AND no ranges have been
               requested. This seems to be what chapter 13.3.4 of
               RFC 2616 defines to be the correct action for a
               HTTP/1.1 client */

            if(!Curl_meets_timecondition(data, k->timeofdoc)) {
              *done = TRUE;
              /* We're simulating a http 304 from server so we return
                 what should have been returned from the server */
              data->info.httpcode = 304;
              infof(data, "Simulate a HTTP 304 response!\n");
              /* we abort the transfer before it is completed == we ruin the
                 re-use ability. Close the connection */
              connclose(conn, "Simulated 304 handling");
              return CURLE_OK;
            }
          } /* we have a time condition */

        } /* this is HTTP or RTSP */
      } /* this is the first time we write a body part */
#endif /* CURL_DISABLE_HTTP */

      k->bodywrites++;

      /* pass data to the debug function before it gets "dechunked" */
      if(data->set.verbose) {
        if(k->badheader) {
          Curl_debug(data, CURLINFO_DATA_IN, data->state.headerbuff,
                     (size_t)k->hbuflen, conn);
          if(k->badheader == HEADER_PARTHEADER)
            Curl_debug(data, CURLINFO_DATA_IN,
                       k->str, (size_t)nread, conn);
        }
        else
          Curl_debug(data, CURLINFO_DATA_IN,
                     k->str, (size_t)nread, conn);
      }

#ifndef CURL_DISABLE_HTTP
      if(k->chunk) {
        /*
         * Here comes a chunked transfer flying and we need to decode this
         * properly.  While the name says read, this function both reads
         * and writes away the data. The returned 'nread' holds the number
         * of actual data it wrote to the client.
         */

        CHUNKcode res =
          Curl_httpchunk_read(conn, k->str, nread, &nread);

        if(CHUNKE_OK < res) {
          if(CHUNKE_WRITE_ERROR == res) {
            failf(data, "Failed writing data");
            return CURLE_WRITE_ERROR;
          }
          failf(data, "%s in chunked-encoding", Curl_chunked_strerror(res));
          return CURLE_RECV_ERROR;
        }
        if(CHUNKE_STOP == res) {
          size_t dataleft;
          /* we're done reading chunks! */
          k->keepon &= ~KEEP_RECV; /* read no more */

          /* There are now possibly N number of bytes at the end of the
             str buffer that weren't written to the client.

             We DO care about this data if we are pipelining.
             Push it back to be read on the next pass. */

          dataleft = conn->chunk.dataleft;
          if(dataleft != 0) {
            infof(conn->data, "Leftovers after chunking: %zu bytes\n",
                  dataleft);
            if(Curl_pipeline_wanted(conn->data->multi, CURLPIPE_HTTP1)) {
              /* only attempt the rewind if we truly are pipelining */
              infof(conn->data, "Rewinding %zu bytes\n",dataleft);
              read_rewind(conn, dataleft);
            }
          }
        }
        /* If it returned OK, we just keep going */
      }
#endif   /* CURL_DISABLE_HTTP */

      /* Account for body content stored in the header buffer */
      if(k->badheader && !k->ignorebody) {
        DEBUGF(infof(data, "Increasing bytecount by %zu from hbuflen\n",
                     k->hbuflen));
        k->bytecount += k->hbuflen;
      }

      if((-1 != k->maxdownload) &&
         (k->bytecount + nread >= k->maxdownload)) {

        excess = (size_t)(k->bytecount + nread - k->maxdownload);
        if(excess > 0 && !k->ignorebody) {
          if(Curl_pipeline_wanted(conn->data->multi, CURLPIPE_HTTP1)) {
            infof(data,
                  "Rewinding stream by : %zu"
                  " bytes on url %s (size = %" CURL_FORMAT_CURL_OFF_T
                  ", maxdownload = %" CURL_FORMAT_CURL_OFF_T
                  ", bytecount = %" CURL_FORMAT_CURL_OFF_T ", nread = %zd)\n",
                  excess, data->state.path,
                  k->size, k->maxdownload, k->bytecount, nread);
            read_rewind(conn, excess);
          }
          else {
            infof(data,
                  "Excess found in a non pipelined read:"
                  " excess = %zu"
                  ", size = %" CURL_FORMAT_CURL_OFF_T
                  ", maxdownload = %" CURL_FORMAT_CURL_OFF_T
                  ", bytecount = %" CURL_FORMAT_CURL_OFF_T "\n",
                  excess, k->size, k->maxdownload, k->bytecount);
          }
        }

        nread = (ssize_t) (k->maxdownload - k->bytecount);
        if(nread < 0) /* this should be unusual */
          nread = 0;

        k->keepon &= ~KEEP_RECV; /* we're done reading */
      }

      k->bytecount += nread;

      Curl_pgrsSetDownloadCounter(data, k->bytecount);

      if(!k->chunk && (nread || k->badheader || is_empty_data)) {
        /* If this is chunky transfer, it was already written */

        if(k->badheader && !k->ignorebody) {
          /* we parsed a piece of data wrongly assuming it was a header
             and now we output it as body instead */

          /* Don't let excess data pollute body writes */
          if(k->maxdownload == -1 || (curl_off_t)k->hbuflen <= k->maxdownload)
            result = Curl_client_write(conn, CLIENTWRITE_BODY,
                                       data->state.headerbuff,
                                       k->hbuflen);
          else
            result = Curl_client_write(conn, CLIENTWRITE_BODY,
                                       data->state.headerbuff,
                                       (size_t)k->maxdownload);

          if(result)
            return result;
        }
        if(k->badheader < HEADER_ALLBAD) {
          /* This switch handles various content encodings. If there's an
             error here, be sure to check over the almost identical code
             in http_chunks.c.
             Make sure that ALL_CONTENT_ENCODINGS contains all the
             encodings handled here. */
#ifdef HAVE_LIBZ
          switch(conn->data->set.http_ce_skip ?
                 IDENTITY : k->auto_decoding) {
          case IDENTITY:
#endif
            /* This is the default when the server sends no
               Content-Encoding header. See Curl_readwrite_init; the
               memset() call initializes k->auto_decoding to zero. */
            if(!k->ignorebody) {

#ifndef CURL_DISABLE_POP3
              if(conn->handler->protocol&PROTO_FAMILY_POP3)
                result = Curl_pop3_write(conn, k->str, nread);
              else
#endif /* CURL_DISABLE_POP3 */

                result = Curl_client_write(conn, CLIENTWRITE_BODY, k->str,
                                           nread);
            }
#ifdef HAVE_LIBZ
            break;

          case DEFLATE:
            /* Assume CLIENTWRITE_BODY; headers are not encoded. */
            if(!k->ignorebody)
              result = Curl_unencode_deflate_write(conn, k, nread);
            break;

          case GZIP:
            /* Assume CLIENTWRITE_BODY; headers are not encoded. */
            if(!k->ignorebody)
              result = Curl_unencode_gzip_write(conn, k, nread);
            break;

          default:
            failf(data, "Unrecognized content encoding type. "
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

    } /* if(!header and data to read) */

    if(conn->handler->readwrite &&
       (excess > 0 && !conn->bits.stream_was_rewound)) {
      /* Parse the excess data */
      k->str += nread;
      nread = (ssize_t)excess;

      result = conn->handler->readwrite(data, conn, &nread, &readmore);
      if(result)
        return result;

      if(readmore)
        k->keepon |= KEEP_RECV; /* we're not done reading */
      break;
    }

    if(is_empty_data) {
      /* if we received nothing, the server closed the connection and we
         are done */
      k->keepon &= ~KEEP_RECV;
    }

  } while(data_pending(conn) && maxloops--);

  if(maxloops <= 0) {
    /* we mark it as read-again-please */
    conn->cselect_bits = CURL_CSELECT_IN;
    *comeback = TRUE;
  }

  if(((k->keepon & (KEEP_RECV|KEEP_SEND)) == KEEP_SEND) &&
     conn->bits.close) {
    /* When we've read the entire thing and the close bit is set, the server
       may now close the connection. If there's now any kind of sending going
       on from our side, we need to stop that immediately. */
    infof(data, "we are done reading and this is set to close, stop send\n");
    k->keepon &= ~KEEP_SEND; /* no writing anymore either */
  }

  return CURLE_OK;
}