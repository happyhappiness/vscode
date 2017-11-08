static CURLcode ftp_state_use_port(struct connectdata *conn,
                                   ftpport fcmd) /* start with this */

{
  CURLcode result = CURLE_OK;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  struct SessionHandle *data=conn->data;
  curl_socket_t portsock= CURL_SOCKET_BAD;
  char myhost[256] = "";

#ifdef ENABLE_IPV6
  /******************************************************************
   * IPv6-specific section
   */
  struct Curl_sockaddr_storage ss;
  struct addrinfo *res, *ai;
  socklen_t sslen;
  char hbuf[NI_MAXHOST];
  struct sockaddr *sa=(struct sockaddr *)&ss;
  char tmp[1024];
  static const char * const mode[] = { "EPRT", "PORT", NULL };
  int rc;
  int error;
  char *host=NULL;
  struct Curl_dns_entry *h=NULL;
  unsigned short port = 0;

  /* Step 1, figure out what address that is requested */

  if(data->set.str[STRING_FTPPORT] &&
     (strlen(data->set.str[STRING_FTPPORT]) > 1)) {
    /* attempt to get the address of the given interface name */
    if(!Curl_if2ip(data->set.str[STRING_FTPPORT], hbuf, sizeof(hbuf)))
      /* not an interface, use the given string as host name instead */
      host = data->set.str[STRING_FTPPORT];
    else
      host = hbuf; /* use the hbuf for host name */
  } /* data->set.ftpport */

  if(!host) {
    /* not an interface and not a host name, get default by extracting
       the IP from the control connection */

    sslen = sizeof(ss);
    if(getsockname(conn->sock[FIRSTSOCKET], (struct sockaddr *)&ss, &sslen)) {
      failf(data, "getsockname() failed: %s",
          Curl_strerror(conn, SOCKERRNO) );
      return CURLE_FTP_PORT_FAILED;
    }

    if(sslen > (socklen_t)sizeof(ss))
      sslen = sizeof(ss);
    rc = getnameinfo((struct sockaddr *)&ss, sslen, hbuf, sizeof(hbuf), NULL,
                     0, NIFLAGS);
    if(rc) {
      failf(data, "getnameinfo() returned %d", rc);
      return CURLE_FTP_PORT_FAILED;
    }
    host = hbuf; /* use this host name */
  }

  rc = Curl_resolv(conn, host, 0, &h);
  if(rc == CURLRESOLV_PENDING)
    rc = Curl_wait_for_resolv(conn, &h);
  if(h) {
    res = h->addr;
    /* when we return from this function, we can forget about this entry
       to we can unlock it now already */
    Curl_resolv_unlock(data, h);
  } /* (h) */
  else
    res = NULL; /* failure! */


  /* step 2, create a socket for the requested address */

  portsock = CURL_SOCKET_BAD;
  error = 0;
  for (ai = res; ai; ai = ai->ai_next) {
    /*
     * Workaround for AIX5 getaddrinfo() problem (it doesn't set ai_socktype):
     */
    if(ai->ai_socktype == 0)
      ai->ai_socktype = conn->socktype;

    portsock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if(portsock == CURL_SOCKET_BAD) {
      error = SOCKERRNO;
      continue;
    }
    break;
  }
  if(!ai) {
    failf(data, "socket failure: %s", Curl_strerror(conn, error));
    return CURLE_FTP_PORT_FAILED;
  }

  /* step 3, bind to a suitable local address */

  /* Try binding the given address. */
  if(bind(portsock, ai->ai_addr, ai->ai_addrlen)) {

    /* It failed. Bind the address used for the control connection instead */
    sslen = sizeof(ss);
    if(getsockname(conn->sock[FIRSTSOCKET],
                    (struct sockaddr *)sa, &sslen)) {
      failf(data, "getsockname() failed: %s",
          Curl_strerror(conn, SOCKERRNO) );
      sclose(portsock);
      return CURLE_FTP_PORT_FAILED;
    }

    /* set port number to zero to make bind() pick "any" */
    if(((struct sockaddr *)sa)->sa_family == AF_INET)
      ((struct sockaddr_in *)sa)->sin_port=0;
    else
      ((struct sockaddr_in6 *)sa)->sin6_port =0;

    if(sslen > (socklen_t)sizeof(ss))
      sslen = sizeof(ss);

    if(bind(portsock, (struct sockaddr *)sa, sslen)) {
      failf(data, "bind failed: %s", Curl_strerror(conn, SOCKERRNO));
      sclose(portsock);
      return CURLE_FTP_PORT_FAILED;
    }
  }

  /* get the name again after the bind() so that we can extract the
     port number it uses now */
  sslen = sizeof(ss);
  if(getsockname(portsock, (struct sockaddr *)sa, &sslen)) {
    failf(data, "getsockname() failed: %s",
          Curl_strerror(conn, SOCKERRNO) );
    sclose(portsock);
    return CURLE_FTP_PORT_FAILED;
  }

  /* step 4, listen on the socket */

  if(listen(portsock, 1)) {
    failf(data, "socket failure: %s", Curl_strerror(conn, SOCKERRNO));
    sclose(portsock);
    return CURLE_FTP_PORT_FAILED;
  }

  /* step 5, send the proper FTP command */

  /* get a plain printable version of the numerical address to work with
     below */
  Curl_printable_address(ai, myhost, sizeof(myhost));

#ifdef PF_INET6
  if(!conn->bits.ftp_use_eprt && conn->bits.ipv6)
    /* EPRT is disabled but we are connected to a IPv6 host, so we ignore the
       request and enable EPRT again! */
    conn->bits.ftp_use_eprt = TRUE;
#endif

  for (; fcmd != DONE; fcmd++) {

    if(!conn->bits.ftp_use_eprt && (EPRT == fcmd))
      /* if disabled, goto next */
      continue;

    switch (sa->sa_family) {
    case AF_INET:
      port = ntohs(((struct sockaddr_in *)sa)->sin_port);
      break;
    case AF_INET6:
      port = ntohs(((struct sockaddr_in6 *)sa)->sin6_port);
      break;
    default:
      break;
    }

    if(EPRT == fcmd) {
      /*
       * Two fine examples from RFC2428;
       *
       * EPRT |1|132.235.1.2|6275|
       *
       * EPRT |2|1080::8:800:200C:417A|5282|
       */

      result = Curl_nbftpsendf(conn, "%s |%d|%s|%d|", mode[fcmd],
                               ai->ai_family == AF_INET?1:2,
                               myhost, port);
      if(result)
        return result;
      break;
    }
    else if(PORT == fcmd) {
      char *source = myhost;
      char *dest = tmp;

      if((PORT == fcmd) && ai->ai_family != AF_INET)
        continue;

      /* translate x.x.x.x to x,x,x,x */
      while(source && *source) {
        if(*source == '.')
          *dest=',';
        else
          *dest = *source;
        dest++;
        source++;
      }
      *dest = 0;
      snprintf(dest, 20, ",%d,%d", port>>8, port&0xff);

      result = Curl_nbftpsendf(conn, "%s %s", mode[fcmd], tmp);
      if(result)
        return result;
      break;
    }
  }

  /* store which command was sent */
  ftpc->count1 = fcmd;

  /* we set the secondary socket variable to this for now, it is only so that
     the cleanup function will close it in case we fail before the true
     secondary stuff is made */
  if(CURL_SOCKET_BAD != conn->sock[SECONDARYSOCKET])
    sclose(conn->sock[SECONDARYSOCKET]);
  conn->sock[SECONDARYSOCKET] = portsock;

#else
  /******************************************************************
   * IPv4-specific section
   */
  struct sockaddr_in sa;
  unsigned short porttouse;
  bool sa_filled_in = FALSE;
  Curl_addrinfo *addr = NULL;
  unsigned short ip[4];
  bool freeaddr = TRUE;
  socklen_t sslen = sizeof(sa);
  const char *ftpportstr = data->set.str[STRING_FTPPORT];

  (void)fcmd; /* not used in the IPv4 code */
  if(ftpportstr) {
    in_addr_t in;

    /* First check if the given name is an IP address */
    in=inet_addr(ftpportstr);

    if(in != CURL_INADDR_NONE)
      /* this is an IPv4 address */
      addr = Curl_ip2addr(in, ftpportstr, 0);
    else {
      if(Curl_if2ip(ftpportstr, myhost, sizeof(myhost))) {
        /* The interface to IP conversion provided a dotted address */
        in=inet_addr(myhost);
        addr = Curl_ip2addr(in, myhost, 0);
      }
      else if(strlen(ftpportstr)> 1) {
        /* might be a host name! */
        struct Curl_dns_entry *h=NULL;
        int rc = Curl_resolv(conn, ftpportstr, 0, &h);
        if(rc == CURLRESOLV_PENDING)
          /* BLOCKING */
          rc = Curl_wait_for_resolv(conn, &h);
        if(h) {
          addr = h->addr;
          /* when we return from this function, we can forget about this entry
             so we can unlock it now already */
          Curl_resolv_unlock(data, h);

          freeaddr = FALSE; /* make sure we don't free 'addr' in this function
                               since it points to a DNS cache entry! */
        } /* (h) */
        else {
          infof(data, "Failed to resolve host name %s\n", ftpportstr);
        }
      } /* strlen */
    } /* CURL_INADDR_NONE */
  } /* ftpportstr */

  if(!addr) {
    /* pick a suitable default here */

    if(getsockname(conn->sock[FIRSTSOCKET],
                    (struct sockaddr *)&sa, &sslen)) {
      failf(data, "getsockname() failed: %s",
          Curl_strerror(conn, SOCKERRNO) );
      return CURLE_FTP_PORT_FAILED;
    }
    if(sslen > (socklen_t)sizeof(sa))
      sslen = sizeof(sa);

    sa_filled_in = TRUE; /* the sa struct is filled in */
  }

  if(addr || sa_filled_in) {
    portsock = socket(AF_INET, SOCK_STREAM, 0);
    if(CURL_SOCKET_BAD != portsock) {

      /* we set the secondary socket variable to this for now, it
         is only so that the cleanup function will close it in case
         we fail before the true secondary stuff is made */
      if(CURL_SOCKET_BAD != conn->sock[SECONDARYSOCKET])
        sclose(conn->sock[SECONDARYSOCKET]);
      conn->sock[SECONDARYSOCKET] = portsock;

      if(!sa_filled_in) {
        memcpy(&sa, addr->ai_addr, sslen);
        sa.sin_addr.s_addr = INADDR_ANY;
      }

      sa.sin_port = 0;
      sslen = sizeof(sa);

      if(bind(portsock, (struct sockaddr *)&sa, sslen) == 0) {
        /* we succeeded to bind */
        struct sockaddr_in add;
        socklen_t socksize = sizeof(add);

        if(getsockname(portsock, (struct sockaddr *) &add,
                       &socksize)) {
          failf(data, "getsockname() failed: %s",
            Curl_strerror(conn, SOCKERRNO) );
          return CURLE_FTP_PORT_FAILED;
        }
        porttouse = ntohs(add.sin_port);

        if( listen(portsock, 1) < 0 ) {
          failf(data, "listen(2) failed on socket");
          return CURLE_FTP_PORT_FAILED;
        }
      }
      else {
        failf(data, "bind(2) failed on socket");
        return CURLE_FTP_PORT_FAILED;
      }
    }
    else {
      failf(data, "socket(2) failed (%s)");
      return CURLE_FTP_PORT_FAILED;
    }
  }
  else {
    failf(data, "couldn't find IP address to use");
    return CURLE_FTP_PORT_FAILED;
  }

  if(sa_filled_in)
    Curl_inet_ntop(AF_INET, &((struct sockaddr_in *)&sa)->sin_addr,
                   myhost, sizeof(myhost));
  else
    Curl_printable_address(addr, myhost, sizeof(myhost));

  if(4 == sscanf(myhost, "%hu.%hu.%hu.%hu",
                 &ip[0], &ip[1], &ip[2], &ip[3])) {

    infof(data, "Telling server to connect to %d.%d.%d.%d:%d\n",
          ip[0], ip[1], ip[2], ip[3], porttouse);

    result=Curl_nbftpsendf(conn, "PORT %d,%d,%d,%d,%d,%d",
                           ip[0], ip[1], ip[2], ip[3],
                           porttouse >> 8, porttouse & 255);
    if(result)
      return result;
  }
  else
    return CURLE_FTP_PORT_FAILED;

  if(freeaddr)
    Curl_freeaddrinfo(addr);

  ftpc->count1 = PORT;

#endif /* end of ipv4-specific code */

  /* this tcpconnect assignment below is a hackish work-around to make the
     multi interface with active FTP work - as it will not wait for a
     (passive) connect in Curl_is_connected().

     The *proper* fix is to make sure that the active connection from the
     server is done in a non-blocking way. Currently, it is still BLOCKING.
  */
  conn->bits.tcpconnect = TRUE;

  state(conn, FTP_PORT);
  return result;
}