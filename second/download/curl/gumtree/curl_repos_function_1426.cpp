CURLcode Curl_proxyCONNECT(struct connectdata *conn,
                           int sockindex,
                           const char *hostname,
                           int remote_port)
{
  int subversion=0;
  struct SessionHandle *data=conn->data;
  struct SingleRequest *k = &data->req;
  CURLcode result;
  curl_socket_t tunnelsocket = conn->sock[sockindex];
  curl_off_t cl=0;
  bool closeConnection = FALSE;
  bool chunked_encoding = FALSE;
  long check;

#define SELECT_OK      0
#define SELECT_ERROR   1
#define SELECT_TIMEOUT 2
  int error = SELECT_OK;

  if(conn->tunnel_state[sockindex] == TUNNEL_COMPLETE)
    return CURLE_OK; /* CONNECT is already completed */

  conn->bits.proxy_connect_closed = FALSE;

  do {
    if(TUNNEL_INIT == conn->tunnel_state[sockindex]) {
      /* BEGIN CONNECT PHASE */
      char *host_port;
      Curl_send_buffer *req_buffer;

      infof(data, "Establish HTTP proxy tunnel to %s:%hu\n",
            hostname, remote_port);

      if(data->req.newurl) {
        /* This only happens if we've looped here due to authentication
           reasons, and we don't really use the newly cloned URL here
           then. Just free() it. */
        free(data->req.newurl);
        data->req.newurl = NULL;
      }

      /* initialize a dynamic send-buffer */
      req_buffer = Curl_add_buffer_init();

      if(!req_buffer)
        return CURLE_OUT_OF_MEMORY;

      host_port = aprintf("%s:%hu", hostname, remote_port);
      if(!host_port) {
        free(req_buffer);
        return CURLE_OUT_OF_MEMORY;
      }

      /* Setup the proxy-authorization header, if any */
      result = Curl_http_output_auth(conn, "CONNECT", host_port, TRUE);

      free(host_port);

      if(!result) {
        char *host=(char *)"";
        const char *proxyconn="";
        const char *useragent="";
        const char *http = (conn->proxytype == CURLPROXY_HTTP_1_0) ?
          "1.0" : "1.1";
        char *hostheader= /* host:port with IPv6 support */
          aprintf("%s%s%s:%hu", conn->bits.ipv6_ip?"[":"",
                  hostname, conn->bits.ipv6_ip?"]":"",
                  remote_port);
        if(!hostheader) {
          free(req_buffer);
          return CURLE_OUT_OF_MEMORY;
        }

        if(!Curl_checkProxyheaders(conn, "Host:")) {
          host = aprintf("Host: %s\r\n", hostheader);
          if(!host) {
            free(hostheader);
            free(req_buffer);
            return CURLE_OUT_OF_MEMORY;
          }
        }
        if(!Curl_checkProxyheaders(conn, "Proxy-Connection:"))
          proxyconn = "Proxy-Connection: Keep-Alive\r\n";

        if(!Curl_checkProxyheaders(conn, "User-Agent:") &&
           data->set.str[STRING_USERAGENT])
          useragent = conn->allocptr.uagent;

        result =
          Curl_add_bufferf(req_buffer,
                           "CONNECT %s HTTP/%s\r\n"
                           "%s"  /* Host: */
                           "%s"  /* Proxy-Authorization */
                           "%s"  /* User-Agent */
                           "%s", /* Proxy-Connection */
                           hostheader,
                           http,
                           host,
                           conn->allocptr.proxyuserpwd?
                           conn->allocptr.proxyuserpwd:"",
                           useragent,
                           proxyconn);

        if(host && *host)
          free(host);
        free(hostheader);

        if(!result)
          result = Curl_add_custom_headers(conn, TRUE, req_buffer);

        if(!result)
          /* CRLF terminate the request */
          result = Curl_add_bufferf(req_buffer, "\r\n");

        if(!result) {
          /* Send the connect request to the proxy */
          /* BLOCKING */
          result =
            Curl_add_buffer_send(req_buffer, conn,
                                 &data->info.request_size, 0, sockindex);
        }
        req_buffer = NULL;
        if(result)
          failf(data, "Failed sending CONNECT to proxy");
      }

      Curl_safefree(req_buffer);
      if(result)
        return result;

      conn->tunnel_state[sockindex] = TUNNEL_CONNECT;
    } /* END CONNECT PHASE */

    check = Curl_timeleft(data, NULL, TRUE);
    if(check <= 0) {
      failf(data, "Proxy CONNECT aborted due to timeout");
      return CURLE_RECV_ERROR;
    }

    if(0 == Curl_socket_ready(tunnelsocket, CURL_SOCKET_BAD, 0))
      /* return so we'll be called again polling-style */
      return CURLE_OK;
    else {
      DEBUGF(infof(data,
                   "Read response immediately from proxy CONNECT\n"));
    }

    /* at this point, the tunnel_connecting phase is over. */

    { /* READING RESPONSE PHASE */
      size_t nread;   /* total size read */
      int perline; /* count bytes per line */
      int keepon=TRUE;
      ssize_t gotbytes;
      char *ptr;
      char *line_start;

      ptr=data->state.buffer;
      line_start = ptr;

      nread=0;
      perline=0;

      while((nread<BUFSIZE) && (keepon && !error)) {

        check = Curl_timeleft(data, NULL, TRUE);
        if(check <= 0) {
          failf(data, "Proxy CONNECT aborted due to timeout");
          error = SELECT_TIMEOUT; /* already too little time */
          break;
        }

        /* loop every second at least, less if the timeout is near */
        switch (Curl_socket_ready(tunnelsocket, CURL_SOCKET_BAD,
                                  check<1000L?check:1000)) {
        case -1: /* select() error, stop reading */
          error = SELECT_ERROR;
          failf(data, "Proxy CONNECT aborted due to select/poll error");
          break;
        case 0: /* timeout */
          break;
        default:
          DEBUGASSERT(ptr+BUFSIZE-nread <= data->state.buffer+BUFSIZE+1);
          result = Curl_read(conn, tunnelsocket, ptr, BUFSIZE-nread,
                             &gotbytes);
          if(result==CURLE_AGAIN)
            continue; /* go loop yourself */
          else if(result)
            keepon = FALSE;
          else if(gotbytes <= 0) {
            keepon = FALSE;
            if(data->set.proxyauth && data->state.authproxy.avail) {
              /* proxy auth was requested and there was proxy auth available,
                 then deem this as "mere" proxy disconnect */
              conn->bits.proxy_connect_closed = TRUE;
              infof(data, "Proxy CONNECT connection closed");
            }
            else {
              error = SELECT_ERROR;
              failf(data, "Proxy CONNECT aborted");
            }
          }
          else {
            /*
             * We got a whole chunk of data, which can be anything from one
             * byte to a set of lines and possibly just a piece of the last
             * line.
             */
            int i;

            nread += gotbytes;

            if(keepon > TRUE) {
              /* This means we are currently ignoring a response-body */

              nread = 0; /* make next read start over in the read buffer */
              ptr=data->state.buffer;
              if(cl) {
                /* A Content-Length based body: simply count down the counter
                   and make sure to break out of the loop when we're done! */
                cl -= gotbytes;
                if(cl<=0) {
                  keepon = FALSE;
                  break;
                }
              }
              else {
                /* chunked-encoded body, so we need to do the chunked dance
                   properly to know when the end of the body is reached */
                CHUNKcode r;
                ssize_t tookcareof=0;

                /* now parse the chunked piece of data so that we can
                   properly tell when the stream ends */
                r = Curl_httpchunk_read(conn, ptr, gotbytes, &tookcareof);
                if(r == CHUNKE_STOP) {
                  /* we're done reading chunks! */
                  infof(data, "chunk reading DONE\n");
                  keepon = FALSE;
                  /* we did the full CONNECT treatment, go COMPLETE */
                  conn->tunnel_state[sockindex] = TUNNEL_COMPLETE;
                }
                else
                  infof(data, "Read %zd bytes of chunk, continue\n",
                        tookcareof);
              }
            }
            else
              for(i = 0; i < gotbytes; ptr++, i++) {
                perline++; /* amount of bytes in this line so far */
                if(*ptr == 0x0a) {
                  char letter;
                  int writetype;

                  /* convert from the network encoding */
                  result = Curl_convert_from_network(data, line_start,
                                                     perline);
                  /* Curl_convert_from_network calls failf if unsuccessful */
                  if(result)
                    return result;

                  /* output debug if that is requested */
                  if(data->set.verbose)
                    Curl_debug(data, CURLINFO_HEADER_IN,
                               line_start, (size_t)perline, conn);

                  /* send the header to the callback */
                  writetype = CLIENTWRITE_HEADER;
                  if(data->set.include_header)
                    writetype |= CLIENTWRITE_BODY;

                  result = Curl_client_write(conn, writetype, line_start,
                                             perline);

                  data->info.header_size += (long)perline;
                  data->req.headerbytecount += (long)perline;

                  if(result)
                    return result;

                  /* Newlines are CRLF, so the CR is ignored as the line isn't
                     really terminated until the LF comes. Treat a following CR
                     as end-of-headers as well.*/

                  if(('\r' == line_start[0]) ||
                     ('\n' == line_start[0])) {
                    /* end of response-headers from the proxy */
                    nread = 0; /* make next read start over in the read
                                  buffer */
                    ptr=data->state.buffer;
                    if((407 == k->httpcode) && !data->state.authproblem) {
                      /* If we get a 407 response code with content length
                         when we have no auth problem, we must ignore the
                         whole response-body */
                      keepon = 2;

                      if(cl) {
                        infof(data, "Ignore %" CURL_FORMAT_CURL_OFF_T
                              " bytes of response-body\n", cl);

                        /* remove the remaining chunk of what we already
                           read */
                        cl -= (gotbytes - i);

                        if(cl<=0)
                          /* if the whole thing was already read, we are done!
                           */
                          keepon=FALSE;
                      }
                      else if(chunked_encoding) {
                        CHUNKcode r;
                        /* We set ignorebody true here since the chunked
                           decoder function will acknowledge that. Pay
                           attention so that this is cleared again when this
                           function returns! */
                        k->ignorebody = TRUE;
                        infof(data, "%zd bytes of chunk left\n", gotbytes-i);

                        if(line_start[1] == '\n') {
                          /* this can only be a LF if the letter at index 0
                             was a CR */
                          line_start++;
                          i++;
                        }

                        /* now parse the chunked piece of data so that we can
                           properly tell when the stream ends */
                        r = Curl_httpchunk_read(conn, line_start+1,
                                                  gotbytes -i, &gotbytes);
                        if(r == CHUNKE_STOP) {
                          /* we're done reading chunks! */
                          infof(data, "chunk reading DONE\n");
                          keepon = FALSE;
                          /* we did the full CONNECT treatment, go to
                             COMPLETE */
                          conn->tunnel_state[sockindex] = TUNNEL_COMPLETE;
                        }
                        else
                          infof(data, "Read %zd bytes of chunk, continue\n",
                                gotbytes);
                      }
                      else {
                        /* without content-length or chunked encoding, we
                           can't keep the connection alive since the close is
                           the end signal so we bail out at once instead */
                        keepon=FALSE;
                      }
                    }
                    else {
                      keepon = FALSE;
                      if(200 == data->info.httpproxycode) {
                        if(gotbytes - (i+1))
                          failf(data, "Proxy CONNECT followed by %zd bytes "
                                "of opaque data. Data ignored (known bug #39)",
                                gotbytes - (i+1));
                      }
                    }
                    /* we did the full CONNECT treatment, go to COMPLETE */
                    conn->tunnel_state[sockindex] = TUNNEL_COMPLETE;
                    break; /* breaks out of for-loop, not switch() */
                  }

                  /* keep a backup of the position we are about to blank */
                  letter = line_start[perline];
                  line_start[perline]=0; /* zero terminate the buffer */
                  if((checkprefix("WWW-Authenticate:", line_start) &&
                      (401 == k->httpcode)) ||
                     (checkprefix("Proxy-authenticate:", line_start) &&
                      (407 == k->httpcode))) {

                    bool proxy = (k->httpcode == 407) ? TRUE : FALSE;
                    char *auth = Curl_copy_header_value(line_start);
                    if(!auth)
                      return CURLE_OUT_OF_MEMORY;

                    result = Curl_http_input_auth(conn, proxy, auth);

                    Curl_safefree(auth);

                    if(result)
                      return result;
                  }
                  else if(checkprefix("Content-Length:", line_start)) {
                    cl = curlx_strtoofft(line_start +
                                         strlen("Content-Length:"), NULL, 10);
                  }
                  else if(Curl_compareheader(line_start,
                                             "Connection:", "close"))
                    closeConnection = TRUE;
                  else if(Curl_compareheader(line_start,
                                             "Transfer-Encoding:",
                                             "chunked")) {
                    infof(data, "CONNECT responded chunked\n");
                    chunked_encoding = TRUE;
                    /* init our chunky engine */
                    Curl_httpchunk_init(conn);
                  }
                  else if(Curl_compareheader(line_start,
                                             "Proxy-Connection:", "close"))
                    closeConnection = TRUE;
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
        if(Curl_pgrsUpdate(conn))
          return CURLE_ABORTED_BY_CALLBACK;
      } /* while there's buffer left and loop is requested */

      if(error)
        return CURLE_RECV_ERROR;

      if(data->info.httpproxycode != 200) {
        /* Deal with the possibly already received authenticate
           headers. 'newurl' is set to a new URL if we must loop. */
        result = Curl_http_auth_act(conn);
        if(result)
          return result;

        if(conn->bits.close)
          /* the connection has been marked for closure, most likely in the
             Curl_http_auth_act() function and thus we can kill it at once
             below
          */
          closeConnection = TRUE;
      }

      if(closeConnection && data->req.newurl) {
        /* Connection closed by server. Don't use it anymore */
        Curl_closesocket(conn, conn->sock[sockindex]);
        conn->sock[sockindex] = CURL_SOCKET_BAD;
        break;
      }
    } /* END READING RESPONSE PHASE */

    /* If we are supposed to continue and request a new URL, which basically
     * means the HTTP authentication is still going on so if the tunnel
     * is complete we start over in INIT state */
    if(data->req.newurl &&
       (TUNNEL_COMPLETE == conn->tunnel_state[sockindex])) {
      conn->tunnel_state[sockindex] = TUNNEL_INIT;
      infof(data, "TUNNEL_STATE switched to: %d\n",
            conn->tunnel_state[sockindex]);
    }

  } while(data->req.newurl);

  if(200 != data->req.httpcode) {
    if(closeConnection && data->req.newurl) {
      conn->bits.proxy_connect_closed = TRUE;
      infof(data, "Connect me again please\n");
    }
    else {
      if(data->req.newurl) {
        /* this won't be used anymore for the CONNECT so free it now */
        free(data->req.newurl);
        data->req.newurl = NULL;
      }
      /* failure, close this connection to avoid re-use */
      connclose(conn, "proxy CONNECT failure");
      Curl_closesocket(conn, conn->sock[sockindex]);
      conn->sock[sockindex] = CURL_SOCKET_BAD;
    }

    /* to back to init state */
    conn->tunnel_state[sockindex] = TUNNEL_INIT;

    if(conn->bits.proxy_connect_closed)
      /* this is not an error, just part of the connection negotiation */
      return CURLE_OK;
    else {
      failf(data, "Received HTTP code %d from proxy after CONNECT",
            data->req.httpcode);
      return CURLE_RECV_ERROR;
    }
  }

  conn->tunnel_state[sockindex] = TUNNEL_COMPLETE;

  /* If a proxy-authorization header was used for the proxy, then we should
     make sure that it isn't accidentally used for the document request
     after we've connected. So let's free and clear it here. */
  Curl_safefree(conn->allocptr.proxyuserpwd);
  conn->allocptr.proxyuserpwd = NULL;

  data->state.authproxy.done = TRUE;

  infof (data, "Proxy replied OK to CONNECT request\n");
  data->req.ignorebody = FALSE; /* put it (back) to non-ignore state */
  conn->bits.rewindaftersend = FALSE; /* make sure this isn't set for the
                                         document request  */
  return CURLE_OK;
}