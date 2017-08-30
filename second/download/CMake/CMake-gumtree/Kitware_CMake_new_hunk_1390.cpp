}

/*
 * Curl_proxyCONNECT() requires that we're connected to a HTTP proxy. This
 * function will issue the necessary commands to get a seamless tunnel through
 * this proxy. After that, the socket can be used just as a normal socket.
 *
 * This badly needs to be rewritten. CONNECT should be sent and dealt with
 * like any ordinary HTTP request, and not specially crafted like this. This
 * function only remains here like this for now since the rewrite is a bit too
 * much work to do at the moment.
 *
 * This function is BLOCKING which is nasty for all multi interface using apps.
 */

CURLcode Curl_proxyCONNECT(struct connectdata *conn,
                           int sockindex,
                           char *hostname,
                           int remote_port)
{
  int subversion=0;
  struct SessionHandle *data=conn->data;
  struct Curl_transfer_keeper *k = &data->reqdata.keep;
  CURLcode result;
  int res;
  size_t nread;   /* total size read */
  int perline; /* count bytes per line */
  int keepon=TRUE;
  ssize_t gotbytes;
  char *ptr;
  long timeout =
    data->set.timeout?data->set.timeout:3600; /* in seconds */
  char *line_start;
  char *host_port;
  curl_socket_t tunnelsocket = conn->sock[sockindex];
  send_buffer *req_buffer;
  curl_off_t cl=0;
  bool closeConnection = FALSE;

#define SELECT_OK      0
#define SELECT_ERROR   1
#define SELECT_TIMEOUT 2
  int error = SELECT_OK;

  infof(data, "Establish HTTP proxy tunnel to %s:%d\n", hostname, remote_port);
  conn->bits.proxy_connect_closed = FALSE;

  do {
    if(data->reqdata.newurl) {
      /* This only happens if we've looped here due to authentication reasons,
         and we don't really use the newly cloned URL here then. Just free()
         it. */
      free(data->reqdata.newurl);
      data->reqdata.newurl = NULL;
    }

    /* initialize a dynamic send-buffer */
    req_buffer = add_buffer_init();

    if(!req_buffer)
      return CURLE_OUT_OF_MEMORY;

    host_port = aprintf("%s:%d", hostname, remote_port);
    if(!host_port)
      return CURLE_OUT_OF_MEMORY;

    /* Setup the proxy-authorization header, if any */
    result = Curl_http_output_auth(conn, (char *)"CONNECT", host_port, TRUE);

    if(CURLE_OK == result) {
      char *host=(char *)"";
      const char *proxyconn="";
      const char *useragent="";

      if(!checkheaders(data, "Host:")) {
        host = aprintf("Host: %s\r\n", host_port);
        if(!host)
          result = CURLE_OUT_OF_MEMORY;
      }
      if(!checkheaders(data, "Proxy-Connection:"))
        proxyconn = "Proxy-Connection: Keep-Alive\r\n";

      if(!checkheaders(data, "User-Agent:") && data->set.useragent)
        useragent = conn->allocptr.uagent;

      if(CURLE_OK == result) {
        /* Send the connect request to the proxy */
        /* BLOCKING */
        result =
          add_bufferf(req_buffer,
                      "CONNECT %s:%d HTTP/1.0\r\n"
                      "%s"  /* Host: */
                      "%s"  /* Proxy-Authorization */
                      "%s"  /* User-Agent */
                      "%s", /* Proxy-Connection */
                      hostname, remote_port,
                      host,
                      conn->allocptr.proxyuserpwd?
                      conn->allocptr.proxyuserpwd:"",
                      useragent,
                      proxyconn);

        if(CURLE_OK == result)
          result = add_custom_headers(conn, req_buffer);

        if(host && *host)
          free(host);

        if(CURLE_OK == result)
          /* CRLF terminate the request */
          result = add_bufferf(req_buffer, "\r\n");

        if(CURLE_OK == result)
          /* Now send off the request */
          result = add_buffer_send(req_buffer, conn,
                                   &data->info.request_size, 0, sockindex);
      }
      if(result)
        failf(data, "Failed sending CONNECT to proxy");
    }
    free(host_port);
    if(result)
      return result;

    ptr=data->state.buffer;
    line_start = ptr;

    nread=0;
    perline=0;
    keepon=TRUE;

    while((nread<BUFSIZE) && (keepon && !error)) {

      /* if timeout is requested, find out how much remaining time we have */
      long check = timeout - /* timeout time */
        Curl_tvdiff(Curl_tvnow(), conn->now)/1000; /* spent time */
      if(check <=0 ) {
        failf(data, "Proxy CONNECT aborted due to timeout");
        error = SELECT_TIMEOUT; /* already too little time */
        break;
      }

      /* timeout each second and check the timeout */
      switch (Curl_select(tunnelsocket, CURL_SOCKET_BAD, 1000)) {
      case -1: /* select() error, stop reading */
        error = SELECT_ERROR;
        failf(data, "Proxy CONNECT aborted due to select() error");
        break;
      case 0: /* timeout */
        break;
      default:
        res = Curl_read(conn, tunnelsocket, ptr, BUFSIZE-nread, &gotbytes);
        if(res< 0)
          /* EWOULDBLOCK */
          continue; /* go loop yourself */
