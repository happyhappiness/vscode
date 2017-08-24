{
          /* a newline is CRLF in pp-talk, so the CR is ignored as
             the line isn't really terminated until the LF comes */

          /* output debug output if that is requested */
#ifdef HAVE_GSSAPI
          if(!conn->sec_complete)
#endif
            if(data->set.verbose)
              Curl_debug(data, CURLINFO_HEADER_IN,
                         pp->linestart_resp, (size_t)perline, conn);

          /*
           * We pass all response-lines to the callback function registered
           * for "headers". The response lines can be seen as a kind of
           * headers.
           */
          result = Curl_client_write(conn, CLIENTWRITE_HEADER,
                                     pp->linestart_resp, perline);
          if(result)
            return result;

          if(pp->endofresp(conn, pp->linestart_resp, perline, code)) {
            /* This is the end of the last line, copy the last line to the
               start of the buffer and zero terminate, for old times sake */
            size_t n = ptr - pp->linestart_resp;
            memmove(buf, pp->linestart_resp, n);
            buf[n]=0; /* zero terminate */
            keepon=FALSE;
            pp->linestart_resp = ptr+1; /* advance pointer */
            i++; /* skip this before getting out */

            *size = pp->nread_resp; /* size of the response */
            pp->nread_resp = 0; /* restart */
            break;
          }
          perline=0; /* line starts over here */
          pp->linestart_resp = ptr+1;
        }