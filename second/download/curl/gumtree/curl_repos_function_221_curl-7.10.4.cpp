CURLcode Curl_ConnectHTTPProxyTunnel(struct connectdata *conn,
                                     int tunnelsocket,
                                     char *hostname, int remote_port)
{
  int httperror=0;
  int subversion=0;
  struct SessionHandle *data=conn->data;
  CURLcode result;
  int res;

  int nread;   /* total size read */
  int perline; /* count bytes per line */
  bool keepon=TRUE;
  ssize_t gotbytes;
  char *ptr;
  int timeout = 3600; /* default timeout in seconds */
  struct timeval interval;
  fd_set rkeepfd;
  fd_set readfd;
  char *line_start;

#define SELECT_OK      0
#define SELECT_ERROR   1
#define SELECT_TIMEOUT 2
  int error = SELECT_OK;

  infof(data, "Establish HTTP proxy tunnel to %s:%d\n", hostname, remote_port);

  /* OK, now send the connect request to the proxy */
  result =
    Curl_sendf(tunnelsocket, conn,
               "CONNECT %s:%d HTTP/1.0\015\012"
               "%s"
               "%s"
               "\r\n",
               hostname, remote_port,
               (conn->bits.proxy_user_passwd)?conn->allocptr.proxyuserpwd:"",
               (data->set.useragent?conn->allocptr.uagent:"")
               );
  if(result) {
    failf(data, "Failed sending CONNECT to proxy");
    return result;
  }

  /* Now, read the full reply we get from the proxy */


  if(data->set.timeout) {
    /* if timeout is requested, find out how much remaining time we have */
    timeout = data->set.timeout - /* timeout time */
      Curl_tvdiff(Curl_tvnow(), conn->now)/1000; /* spent time */
    if(timeout <=0 ) {
      failf(data, "Transfer aborted due to timeout");
      return -SELECT_TIMEOUT; /* already too little time */
    }
  }

  FD_ZERO (&readfd);		/* clear it */
  FD_SET (tunnelsocket, &readfd);     /* read socket */

  /* get this in a backup variable to be able to restore it on each lap in the
     select() loop */
  rkeepfd = readfd;

  ptr=data->state.buffer;
  line_start = ptr;

  nread=0;
  perline=0;
  keepon=TRUE;

  while((nread<BUFSIZE) && (keepon && !error)) {
    readfd = rkeepfd;		   /* set every lap */
    interval.tv_sec = timeout;
    interval.tv_usec = 0;

    switch (select (tunnelsocket+1, &readfd, NULL, NULL, &interval)) {
    case -1: /* select() error, stop reading */
      error = SELECT_ERROR;
      failf(data, "Transfer aborted due to select() error");
      break;
    case 0: /* timeout */
      error = SELECT_TIMEOUT;
      failf(data, "Transfer aborted due to timeout");
      break;
    default:
      /*
       * This code previously didn't use the kerberos sec_read() code
       * to read, but when we use Curl_read() it may do so. Do confirm
       * that this is still ok and then remove this comment!
       */
      res= Curl_read(conn, tunnelsocket, ptr, BUFSIZE-nread,
                     &gotbytes);
      if(res< 0)
        /* EWOULDBLOCK */
        continue; /* go loop yourself */
      else if(res)
        keepon = FALSE;
      else if(gotbytes <= 0) {
        keepon = FALSE;
        error = SELECT_ERROR;
        failf(data, "Connection aborted");
      }
      else {
        /* we got a whole chunk of data, which can be anything from one
         * byte to a set of lines and possibly just a piece of the last
         * line */
        int i;

        nread += gotbytes;
        for(i = 0; i < gotbytes; ptr++, i++) {
          perline++; /* amount of bytes in this line so far */
          if(*ptr=='\n') {
            /* a newline is CRLF in ftp-talk, so the CR is ignored as
               the line isn't really terminated until the LF comes */

            /* output debug output if that is requested */
            if(data->set.verbose)
              Curl_debug(data, CURLINFO_DATA_IN, line_start, perline);
            
            if('\r' == line_start[0]) {
              /* end of headers */
              keepon=FALSE;
              break; /* breaks out of loop, not switch */
            }

            if(2 == sscanf(line_start, "HTTP/1.%d %d",
                           &subversion,
                           &httperror)) {
              ;
            }

            perline=0; /* line starts over here */
            line_start = ptr+1;
          }
        }
      }
      break;
    } /* switch */
  } /* while there's buffer left and loop is requested */

  if(error)
    return CURLE_RECV_ERROR;

  if(200 != httperror) {
    if(407 == httperror)
      /* Added Nov 6 1998 */
      failf(data, "Proxy requires authorization!");
    else 
      failf(data, "Received error code %d from proxy", httperror);
    return CURLE_RECV_ERROR;
  }

  infof (data, "Proxy replied to CONNECT request\n");
  return CURLE_OK;
}