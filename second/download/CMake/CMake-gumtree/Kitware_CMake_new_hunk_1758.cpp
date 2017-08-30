   * Connect to server/proxy

   *************************************************************/

  result= Curl_connecthost(conn,

                           hostaddr,

                           conn->port,

                           &conn->firstsocket,

                           &addr,

                           connected);

  if(CURLE_OK == result) {

    /* All is cool, then we store the current information from the hostaddr

       struct to the serv_addr, as it might be needed later. The address

       returned from the function above is crucial here. */

    conn->connect_addr = hostaddr;



#ifdef ENABLE_IPV6

    conn->serv_addr = addr;

#else

    memset((char *) &conn->serv_addr, '\0', sizeof(conn->serv_addr));

    memcpy((char *)&(conn->serv_addr.sin_addr),

           (struct in_addr *)addr, sizeof(struct in_addr));

    conn->serv_addr.sin_family = hostaddr->addr->h_addrtype;

    conn->serv_addr.sin_port = htons((unsigned short)conn->port);

#endif



    if (conn->data->set.proxytype == CURLPROXY_SOCKS5) {

      return handleSock5Proxy(conn->data->state.proxyuser,

                              conn->data->state.proxypasswd,

                              conn,

                              conn->firstsocket) ?

        CURLE_COULDNT_CONNECT : CURLE_OK;

    }

    else if (conn->data->set.proxytype == CURLPROXY_HTTP) {

      /* do nothing here. handled later. */

    }

    else {

      failf(conn->data, "unknown proxytype option given");

      return CURLE_COULDNT_CONNECT; 

    }

  }



  return result;

}



static void verboseconnect(struct connectdata *conn,

                           struct Curl_dns_entry *dns)

{

#ifdef HAVE_INET_NTOA_R

  char ntoa_buf[64];

#endif

  struct SessionHandle *data = conn->data;



  /* Figure out the ip-number and display the first host name it shows: */

#ifdef ENABLE_IPV6

  (void)dns; /* not used in the IPv6 enabled version */

  {

    char hbuf[NI_MAXHOST];

#ifdef NI_WITHSCOPEID

    const int niflags = NI_NUMERICHOST | NI_WITHSCOPEID;

#else

    const int niflags = NI_NUMERICHOST;

#endif

    struct addrinfo *ai = conn->serv_addr;



    if (getnameinfo(ai->ai_addr, ai->ai_addrlen, hbuf, sizeof(hbuf), NULL, 0,

        niflags)) {

      snprintf(hbuf, sizeof(hbuf), "?");

    }

    if (ai->ai_canonname) {

      infof(data, "Connected to %s (%s) port %d\n", ai->ai_canonname, hbuf,

            conn->port);

    } else {

      infof(data, "Connected to %s port %d\n", hbuf, conn->port);

    }

  }

#else

  {

    Curl_addrinfo *hostaddr=dns->addr;

    struct in_addr in;

    (void) memcpy(&in.s_addr, &conn->serv_addr.sin_addr, sizeof (in.s_addr));

    infof(data, "Connected to %s (%s) port %d\n",

          hostaddr?hostaddr->h_name:"",

#if defined(HAVE_INET_NTOA_R)

          inet_ntoa_r(in, ntoa_buf, sizeof(ntoa_buf)),

#else

          inet_ntoa(in),

#endif

          conn->port);

  }

#endif

}



/*

 * We have discovered that the TCP connection has been successful, we can now

 * proceed with some action.

 *

 * If we're using the multi interface, this host address pointer is most

 * likely NULL at this point as we can't keep the resolved info around. This

 * may call for some reworking, like a reference counter in the struct or

 * something. The hostaddr is not used for very much though, we have the

 * 'serv_addr' field in the connectdata struct for most of it.

 */

CURLcode Curl_protocol_connect(struct connectdata *conn,

                               struct Curl_dns_entry *hostaddr)

{

  struct SessionHandle *data = conn->data;

  CURLcode result=CURLE_OK;

  

  Curl_pgrsTime(data, TIMER_CONNECT); /* connect done */



  if(data->set.verbose)

    verboseconnect(conn, hostaddr);



  if(conn->curl_connect) {

    /* is there a protocol-specific connect() procedure? */



    /* set start time here for timeout purposes in the

     * connect procedure, it is later set again for the

     * progress meter purpose */

    conn->now = Curl_tvnow();



    /* Call the protocol-specific connect function */

    result = conn->curl_connect(conn);

  }



  return result; /* pass back status */

}



static CURLcode CreateConnection(struct SessionHandle *data,

                                 struct connectdata **in_connect)

{

