static CURLcode bindlocal(struct connectdata *conn,
                          curl_socket_t sockfd)
{
#ifdef ENABLE_IPV6
  char ipv6_addr[16];
#endif
  struct SessionHandle *data = conn->data;
  struct sockaddr_in me;
  struct sockaddr *sock = NULL;  /* bind to this address */
  socklen_t socksize; /* size of the data sock points to */
  unsigned short port = data->set.localport; /* use this port number, 0 for
                                                "random" */
  /* how many port numbers to try to bind to, increasing one at a time */
  int portnum = data->set.localportrange;
  const char *dev = data->set.str[STRING_DEVICE];

  /*************************************************************
   * Select device to bind socket to
   *************************************************************/
  if(dev && (strlen(dev)<255) ) {
    struct Curl_dns_entry *h=NULL;
    char myhost[256] = "";
    in_addr_t in;
    int rc;
    bool was_iface = FALSE;
    int in6 = -1;

    /* First check if the given name is an IP address */
    in=inet_addr((char *) dev);

    if((in == CURL_INADDR_NONE) &&
       Curl_if2ip(dev, myhost, sizeof(myhost))) {
      /*
       * We now have the numerical IPv4-style x.y.z.w in the 'myhost' buffer
       */
      rc = Curl_resolv(conn, myhost, 0, &h);
      if(rc == CURLRESOLV_PENDING)
        (void)Curl_wait_for_resolv(conn, &h);

      if(h) {
        was_iface = TRUE;
        Curl_resolv_unlock(data, h);
      }
    }

    if(!was_iface) {
      /*
       * This was not an interface, resolve the name as a host name
       * or IP number
       */
      rc = Curl_resolv(conn, dev, 0, &h);
      if(rc == CURLRESOLV_PENDING)
        (void)Curl_wait_for_resolv(conn, &h);

      if(h) {
        if(in == CURL_INADDR_NONE)
          /* convert the resolved address, sizeof myhost >= INET_ADDRSTRLEN */
          Curl_inet_ntop(h->addr->ai_addr->sa_family,
                         &((struct sockaddr_in*)h->addr->ai_addr)->sin_addr,
                         myhost, sizeof myhost);
        else
          /* we know data->set.device is shorter than the myhost array */
          strcpy(myhost, dev);
        Curl_resolv_unlock(data, h);
      }
    }

    if(! *myhost) {
      /* need to fix this
         h=Curl_gethost(data,
         getmyhost(*myhost,sizeof(myhost)),
         hostent_buf,
         sizeof(hostent_buf));
      */
      failf(data, "Couldn't bind to '%s'", dev);
      return CURLE_INTERFACE_FAILED;
    }

    infof(data, "Bind local address to %s\n", myhost);

#ifdef SO_BINDTODEVICE
    /* I am not sure any other OSs than Linux that provide this feature, and
     * at the least I cannot test. --Ben
     *
     * This feature allows one to tightly bind the local socket to a
     * particular interface.  This will force even requests to other local
     * interfaces to go out the external interface.
     *
     */
    if(was_iface) {
      /* Only bind to the interface when specified as interface, not just as a
       * hostname or ip address.
       */
      if(setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,
                     dev, strlen(dev)+1) != 0) {
        /* printf("Failed to BINDTODEVICE, socket: %d  device: %s error: %s\n",
           sockfd, dev, Curl_strerror(SOCKERRNO)); */
        infof(data, "SO_BINDTODEVICE %s failed\n", dev);
        /* This is typically "errno 1, error: Operation not permitted" if
           you're not running as root or another suitable privileged user */
      }
    }
#endif

    in=inet_addr(myhost);

#ifdef ENABLE_IPV6
    in6 = Curl_inet_pton (AF_INET6, myhost, (void *)&ipv6_addr);
#endif
    if(CURL_INADDR_NONE == in && -1 == in6) {
      failf(data,"couldn't find my own IP address (%s)", myhost);
      return CURLE_INTERFACE_FAILED;
    } /* end of inet_addr */

    if( h ) {
      Curl_addrinfo *addr = h->addr;
      sock = addr->ai_addr;
      socksize = addr->ai_addrlen;
    }
    else
      return CURLE_INTERFACE_FAILED;

  }
  else if(port) {
    /* if a local port number is requested but no local IP, extract the
       address from the socket */
    memset(&me, 0, sizeof(struct sockaddr));
    me.sin_family = AF_INET;
    me.sin_addr.s_addr = INADDR_ANY;

    sock = (struct sockaddr *)&me;
    socksize = sizeof(struct sockaddr);

  }
  else
    /* no local kind of binding was requested */
    return CURLE_OK;

  do {

    /* Set port number to bind to, 0 makes the system pick one */
    if(sock->sa_family == AF_INET)
      ((struct sockaddr_in *)sock)->sin_port = htons(port);
#ifdef ENABLE_IPV6
    else
      ((struct sockaddr_in6 *)sock)->sin6_port = htons(port);
#endif

    if( bind(sockfd, sock, socksize) >= 0) {
      /* we succeeded to bind */
      struct Curl_sockaddr_storage add;
      socklen_t size;

      size = sizeof(add);
      if(getsockname(sockfd, (struct sockaddr *) &add, &size) < 0) {
        failf(data, "getsockname() failed");
        return CURLE_INTERFACE_FAILED;
      }
      /* We re-use/clobber the port variable here below */
      if(((struct sockaddr *)&add)->sa_family == AF_INET)
        port = ntohs(((struct sockaddr_in *)&add)->sin_port);
#ifdef ENABLE_IPV6
      else
        port = ntohs(((struct sockaddr_in6 *)&add)->sin6_port);
#endif
      infof(data, "Local port: %d\n", port);
      conn->bits.bound = TRUE;
      return CURLE_OK;
    }
    if(--portnum > 0) {
      infof(data, "Bind to local port %d failed, trying next\n", port);
      port++; /* try next port */
    }
    else
      break;
  } while(1);

  data->state.os_errno = SOCKERRNO;
  failf(data, "bind failure: %s",
        Curl_strerror(conn, data->state.os_errno));
  return CURLE_INTERFACE_FAILED;

}