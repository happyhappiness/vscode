}



/*

 * ConnectHTTPProxyTunnel() requires that we're connected to a HTTP proxy. This

 * function will issue the necessary commands to get a seamless tunnel through

 * this proxy. After that, the socket can be used just as a normal socket.

 */



CURLcode Curl_ConnectHTTPProxyTunnel(struct connectdata *conn,

                                     int sockindex,

                                     char *hostname,

                                     int remote_port)

{

  int subversion=0;

  struct SessionHandle *data=conn->data;

  struct Curl_transfer_keeper *k = &conn->keep;

  CURLcode result;

  int res;



  size_t nread;   /* total size read */

  int perline; /* count bytes per line */

  bool keepon=TRUE;

  ssize_t gotbytes;

  char *ptr;

  long timeout; /* default timeout in seconds */

  struct timeval interval;

  fd_set rkeepfd;

  fd_set readfd;

  char *line_start;

  char *host_port;

  curl_socket_t tunnelsocket = conn->sock[sockindex];



#define SELECT_OK      0

#define SELECT_ERROR   1

#define SELECT_TIMEOUT 2

  int error = SELECT_OK;



  infof(data, "Establish HTTP proxy tunnel to %s:%d\n", hostname, remote_port);



  do {

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

