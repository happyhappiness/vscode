CURLcode Curl_connecthost(struct connectdata *conn,  /* context */
                          struct Curl_dns_entry *remotehost, /* use this one */
                          int port,                  /* connect to this */
                          int *sockconn,             /* the connected socket */
                          Curl_ipconnect **addr,     /* the one we used */
                          bool *connected)           /* really connected? */
{
  struct SessionHandle *data = conn->data;
  int rc;
  int sockfd=-1;
  int aliasindex=0;
  char *hostname;

  struct timeval after;
  struct timeval before = Curl_tvnow();

  /*************************************************************
   * Figure out what maximum time we have left
   *************************************************************/
  long timeout_ms=300000; /* milliseconds, default to five minutes */

  *connected = FALSE; /* default to not connected */

  if(data->set.timeout || data->set.connecttimeout) {
    double has_passed;

    /* Evaluate in milliseconds how much time that has passed */
    has_passed = Curl_tvdiff(Curl_tvnow(), data->progress.start);

#ifndef min
#define min(a, b)   ((a) < (b) ? (a) : (b))
#endif

    /* get the most strict timeout of the ones converted to milliseconds */
    if(data->set.timeout && data->set.connecttimeout) {
      if (data->set.timeout < data->set.connecttimeout)
        timeout_ms = data->set.timeout*1000;
      else 
        timeout_ms = data->set.connecttimeout*1000;
    }
    else if(data->set.timeout)
      timeout_ms = data->set.timeout*1000;
    else
      timeout_ms = data->set.connecttimeout*1000;

    /* subtract the passed time */
    timeout_ms -= (long)has_passed;

    if(timeout_ms < 0) {
      /* a precaution, no need to continue if time already is up */
      failf(data, "Connection time-out");
      return CURLE_OPERATION_TIMEOUTED;
    }
  }

  hostname = data->change.proxy?conn->proxyhost:conn->hostname;
  infof(data, "About to connect() to %s%s%s:%d\n",
        conn->bits.ipv6_ip?"[":"",
        hostname,
        conn->bits.ipv6_ip?"]":"",
        port);

#ifdef ENABLE_IPV6
  /*
   * Connecting with IPv6 support is so much easier and cleanly done
   */
  {
    struct addrinfo *ai;
    port =0; /* prevent compiler warning */

    for (ai = remotehost->addr; ai; ai = ai->ai_next, aliasindex++) {
      sockfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
      if (sockfd < 0)
        continue;

      if(conn->data->set.device) {
        /* user selected to bind the outgoing socket to a specified "device"
           before doing connect */
        CURLcode res = bindlocal(conn, sockfd);
        if(res)
          return res;
      }

      /* set socket non-blocking */
      Curl_nonblock(sockfd, TRUE);

      rc = connect(sockfd, ai->ai_addr, ai->ai_addrlen);

      if(-1 == rc) {
        int error=ourerrno();

        switch (error) {
        case EINPROGRESS:
        case EWOULDBLOCK:
#if defined(EAGAIN) && EAGAIN != EWOULDBLOCK
          /* On some platforms EAGAIN and EWOULDBLOCK are the
           * same value, and on others they are different, hence
           * the odd #if
           */
        case EAGAIN:
#endif
        case EINTR:
          /* asynchronous connect, wait for connect or timeout */
          if(data->state.used_interface == Curl_if_multi)
            /* don't hang when doing multi */
            timeout_ms = 0;

          rc = waitconnect(sockfd, timeout_ms);
          break;
        case ECONNREFUSED: /* no one listening */
        default:
          /* unknown error, fallthrough and try another address! */
          failf(data, "Failed connect to %s: %d", hostname, error);
          break;
        }
      }

      if(0 == rc) {
        /* we might be connected, if the socket says it is OK! Ask it! */
        int err;

        err = socketerror(sockfd);
        if ((0 == err) || (EISCONN == err)) {
          /* we are connected, awesome! */
          *connected = TRUE; /* this is truly a connect */
          break;
	}
        failf(data, "socket error: %d", err);
        /* we are _not_ connected, it was a false alert, continue please */
      }
      else if(2 == rc)
        /* waitconnect() returned error */
        ;
      else if(data->state.used_interface == Curl_if_multi) {
        /* When running the multi interface, we bail out here */
        rc = 0;
        break;
      }

      /* connect failed or timed out */
      sclose(sockfd);
      sockfd = -1;

      /* get a new timeout for next attempt */
      after = Curl_tvnow();
      timeout_ms -= Curl_tvdiff(after, before);
      if(timeout_ms < 0) {
        failf(data, "connect() timed out!");
        return CURLE_OPERATION_TIMEOUTED;
      }
      before = after;
      continue;
    }
    if (sockfd < 0)
      return CURLE_COULDNT_CONNECT;

    /* leave the socket in non-blocking mode */

    if(addr)
      *addr = ai; /* the address we ended up connected to */
  }
#else
  /*
   * Connecting with IPv4-only support
   */
  if(!remotehost->addr->h_addr_list[0]) {
    /* If there is no addresses in the address list, then we return
       error right away */
    failf(data, "no address available");
    return CURLE_COULDNT_CONNECT;
  }
  /* create an IPv4 TCP socket */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(-1 == sockfd) {
    failf(data, "couldn't create socket");
    return CURLE_COULDNT_CONNECT; /* big time error */
  }
  
  if(conn->data->set.device) {
    /* user selected to bind the outgoing socket to a specified "device"
       before doing connect */
    CURLcode res = bindlocal(conn, sockfd);
    if(res)
      return res;
  }

  /* Convert socket to non-blocking type */
  Curl_nonblock(sockfd, TRUE);

  /* This is the loop that attempts to connect to all IP-addresses we
     know for the given host. One by one. */
  for(rc=-1, aliasindex=0;
      rc && (struct in_addr *)remotehost->addr->h_addr_list[aliasindex];
      aliasindex++) {
    struct sockaddr_in serv_addr;

    /* do this nasty work to do the connect */
    memset((char *) &serv_addr, '\0', sizeof(serv_addr));
    memcpy((char *)&(serv_addr.sin_addr),
           (struct in_addr *)remotehost->addr->h_addr_list[aliasindex],
           sizeof(struct in_addr));
    serv_addr.sin_family = remotehost->addr->h_addrtype;
    serv_addr.sin_port = htons((unsigned short)port);
  
    rc = connect(sockfd, (struct sockaddr *)&serv_addr,
                 sizeof(serv_addr));

    if(-1 == rc) {
      int error=ourerrno();

      switch (error) {
      case EINPROGRESS:
      case EWOULDBLOCK:
#if defined(EAGAIN) && EAGAIN != EWOULDBLOCK
        /* On some platforms EAGAIN and EWOULDBLOCK are the
         * same value, and on others they are different, hence
         * the odd #if
         */
      case EAGAIN:
#endif
        /* asynchronous connect, wait for connect or timeout */
        if(data->state.used_interface == Curl_if_multi)
          /* don't hang when doing multi */
          timeout_ms = 0;

        rc = waitconnect(sockfd, timeout_ms);
        break;
      default:
        /* unknown error, fallthrough and try another address! */
        failf(data, "Failed to connect to %s IP number %d: %d",
              hostname, aliasindex+1, error);
        break;
      }
    }

    /* The '1 == rc' comes from the waitconnect(), and not from connect().
       We can be sure of this since connect() cannot return 1. */
    if((1 == rc) && (data->state.used_interface == Curl_if_multi)) {
      /* Timeout when running the multi interface, we return here with a
         CURLE_OK return code. */
      rc = 0;
      break;
    }

    if(0 == rc) {
      int err = socketerror(sockfd);
      if ((0 == err) || (EISCONN == err)) {
        /* we are connected, awesome! */
        *connected = TRUE; /* this is a true connect */
        break;
      }
      /* nope, not connected for real */
      rc = -1;
    }

    if(0 != rc) {
      /* get a new timeout for next attempt */
      after = Curl_tvnow();
      timeout_ms -= Curl_tvdiff(after, before);
      if(timeout_ms < 0) {
        failf(data, "Connect timeout on IP number %d", aliasindex+1);
        break;
      }
      before = after;
      continue; /* try next address */
    }
    break;
  }
  if(0 != rc) {
    /* no good connect was made */
    sclose(sockfd);
    *sockconn = -1;
    failf(data, "Connect failed");
    return CURLE_COULDNT_CONNECT;
  }

  /* leave the socket in non-blocking mode */

  if(addr)
    /* this is the address we've connected to */
    *addr = (struct in_addr *)remotehost->addr->h_addr_list[aliasindex];
#endif

  /* allow NULL-pointers to get passed in */
  if(sockconn)
    *sockconn = sockfd;    /* the socket descriptor we've connected */

  return CURLE_OK;
}