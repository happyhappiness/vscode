{
    if(conn->newurl) {
      /* This only happens if we've looped here due to authentication reasons,
         and we don't really use the newly cloned URL here then. Just free()
         it. */
      free(conn->newurl);
      conn->newurl = NULL;
    }

    host_port = aprintf("%s:%d", hostname, remote_port);
    if(!host_port)
      return CURLE_OUT_OF_MEMORY;

    /* Setup the proxy-authorization header, if any */
    result = Curl_http_output_auth(conn, (char *)"CONNECT", host_port, TRUE);
    if(CURLE_OK == result) {

      /* OK, now send the connect request to the proxy */
      result =
        Curl_sendf(tunnelsocket, conn,
                   "CONNECT %s:%d HTTP/1.0\015\012"
                   "%s"
                   "%s"
                   "\r\n",
                   hostname, remote_port,
                   conn->bits.proxy_user_passwd?
                   conn->allocptr.proxyuserpwd:"",
                   data->set.useragent?conn->allocptr.uagent:""
                   );
      if(result)
        failf(data, "Failed sending CONNECT to proxy");
    }
    free(host_port);
    if(result)
      return result;

    FD_ZERO (&readfd);          /* clear it */
    FD_SET (tunnelsocket, &readfd);     /* read socket */

    /* get this in a backup variable to be able to restore it on each lap in
       the select() loop */
    rkeepfd = readfd;

    ptr=data->state.buffer;
    line_start = ptr;

    nread=0;
    perline=0;

    while((nread<BUFSIZE) && (keepon && !error)) {
      readfd = rkeepfd;     /* set every lap */
      interval.tv_sec = 1;  /* timeout each second and check the timeout */
      interval.tv_usec = 0;

      if(data->set.timeout) {
        /* if timeout is requested, find out how much remaining time we have */
        timeout = data->set.timeout - /* timeout time */
          Curl_tvdiff(Curl_tvnow(), conn->now)/1000; /* spent time */
        if(timeout <=0 ) {
          failf(data, "Proxy connection aborted due to timeout");
          error = SELECT_TIMEOUT; /* already too little time */
          break;
        }
      }

      switch (select (tunnelsocket+1, &readfd, NULL, NULL, &interval)) {
      case -1: /* select() error, stop reading */
        error = SELECT_ERROR;
        failf(data, "Proxy CONNECT aborted due to select() error");
        break;
      case 0: /* timeout */
        break;
      default:
        /*
         * This code previously didn't use the kerberos sec_read() code
         * to read, but when we use Curl_read() it may do so. Do confirm
         * that this is still ok and then remove this comment!
         */
        res= Curl_read(conn, tunnelsocket, ptr, BUFSIZE-nread, &gotbytes);
        if(res< 0)
          /* EWOULDBLOCK */
          continue; /* go loop yourself */
        else if(res)
          keepon = FALSE;
        else if(gotbytes <= 0) {
          keepon = FALSE;
          error = SELECT_ERROR;
          failf(data, "Proxy CONNECT aborted");
        }
        else {
          /*
           * We got a whole chunk of data, which can be anything from one byte
           * to a set of lines and possibly just a piece of the last line.
           *
           * TODO: To make this code work less error-prone, we need to make
           * sure that we read and create full lines before we compare them,
           * as there is really nothing that stops the proxy from delivering
           * the response lines in multiple parts, each part consisting of
           * only a little piece of the line(s).  */
          int i;

          nread += gotbytes;
          for(i = 0; i < gotbytes; ptr++, i++) {
            perline++; /* amount of bytes in this line so far */
            if(*ptr=='\n') {
              char letter;
              int writetype;

              /* output debug output if that is requested */
              if(data->set.verbose)
                Curl_debug(data, CURLINFO_HEADER_IN, line_start, perline,
                           conn->host.dispname);

              /* send the header to the callback */
              writetype = CLIENTWRITE_HEADER;
              if(data->set.include_header)
                writetype |= CLIENTWRITE_BODY;

              result = Curl_client_write(data, writetype, line_start, perline);
              if(result)
                return result;

              /* Newlines are CRLF, so the CR is ignored as the line isn't
                 really terminated until the LF comes. Treat a following CR
                 as end-of-headers as well.*/

              if(('\r' == line_start[0]) ||
                 ('\n' == line_start[0])) {
                /* end of response-headers from the proxy */
                keepon=FALSE;
                break; /* breaks out of for-loop, not switch() */
              }

              /* keep a backup of the position we are about to blank */
              letter = line_start[perline];
              line_start[perline]=0; /* zero terminate the buffer */
              if((checkprefix("WWW-Authenticate:", line_start) &&
                  (401 == k->httpcode)) ||
                 (checkprefix("Proxy-authenticate:", line_start) &&
                  (407 == k->httpcode))) {
                result = Curl_http_input_auth(conn, k->httpcode, line_start);
                if(result)
                  return result;
              }
              else if(2 == sscanf(line_start, "HTTP/1.%d %d",
                                  &subversion,
                                  &k->httpcode)) {
                /* store the HTTP code from the proxy */
                data->info.httpproxycode = k->httpcode;
              }
              /* put back the letter we blanked out before */
              line_start[perline]= letter;

              perline=0; /* line starts over here */
              line_start = ptr+1; /* this skips the zero byte we wrote */
            }
          }
        }
        break;
      } /* switch */
    } /* while there's buffer left and loop is requested */

    if(error)
      return CURLE_RECV_ERROR;

    if(data->info.httpproxycode != 200)
      /* Deal with the possibly already received authenticate
         headers. 'newurl' is set to a new URL if we must loop. */
      Curl_http_auth_act(conn);

  }