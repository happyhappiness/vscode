static CURLcode ftp_state_use_port(struct connectdata *conn,
                                   ftpport fcmd) /* start with this */

{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->proto.ftp;
  struct SessionHandle *data=conn->data;
  curl_socket_t portsock= CURL_SOCKET_BAD;

#ifdef ENABLE_IPV6
  /******************************************************************
   * IPv6-specific section
   */
#ifdef HAVE_STRUCT_SOCKADDR_STORAGE
  struct sockaddr_storage ss;
#else
  char ss[256]; /* this should be big enough to fit a lot */
#endif
  struct addrinfo *res, *ai;
  socklen_t sslen;
  char hbuf[NI_MAXHOST];
  struct sockaddr *sa=(struct sockaddr *)&ss;
  unsigned char *ap;
  unsigned char *pp;
  char portmsgbuf[1024], tmp[1024];
  const char *mode[] = { "EPRT", "LPRT", "PORT", NULL };
  int rc;
  int error;
  char *host=NULL;
  struct Curl_dns_entry *h=NULL;

  if(data->set.ftpport && (strlen(data->set.ftpport) > 1)) {
    /* attempt to get the address of the given interface name */
    if(!Curl_if2ip(data->set.ftpport, hbuf, sizeof(hbuf)))
      /* not an interface, use the given string as host name instead */
      host = data->set.ftpport;
    else
      host = hbuf; /* use the hbuf for host name */
  } /* data->set.ftpport */

  if(!host) {
    /* not an interface and not a host name, get default by extracting
       the IP from the control connection */

    sslen = sizeof(ss);
    rc = getsockname(conn->sock[FIRSTSOCKET], (struct sockaddr *)&ss, &sslen);
    if(rc < 0) {
      failf(data, "getsockname() returned %d\n", rc);
      return CURLE_FTP_PORT_FAILED;
    }

    rc = getnameinfo((struct sockaddr *)&ss, sslen, hbuf, sizeof(hbuf), NULL,
                     0, NIFLAGS);
    if(rc) {
      failf(data, "getnameinfo() returned %d\n", rc);
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

  portsock = CURL_SOCKET_BAD;
  error = 0;
  for (ai = res; ai; ai = ai->ai_next) {
    /*
     * Workaround for AIX5 getaddrinfo() problem (it doesn't set ai_socktype):
     */
    if (ai->ai_socktype == 0)
      ai->ai_socktype = SOCK_STREAM;

    portsock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (portsock == CURL_SOCKET_BAD) {
      error = Curl_ourerrno();
      continue;
    }

    if (bind(portsock, ai->ai_addr, ai->ai_addrlen) < 0) {
      error = Curl_ourerrno();
      sclose(portsock);
      portsock = CURL_SOCKET_BAD;
      continue;
    }

    if (listen(portsock, 1) < 0) {
      error = Curl_ourerrno();
      sclose(portsock);
      portsock = CURL_SOCKET_BAD;
      continue;
    }

    break;
  }

  if (portsock == CURL_SOCKET_BAD) {
    failf(data, "socket failure: %s", Curl_strerror(conn,error));
    return CURLE_FTP_PORT_FAILED;
  }

  sslen = sizeof(ss);
  if (getsockname(portsock, sa, &sslen) < 0) {
    failf(data, "getsockname(): %s", Curl_strerror(conn,Curl_ourerrno()));
    return CURLE_FTP_PORT_FAILED;
  }

#ifdef PF_INET6
  if(!conn->bits.ftp_use_eprt && conn->bits.ipv6)
    /* EPRT is disabled but we are connected to a IPv6 host, so we ignore the
       request and enable EPRT again! */
    conn->bits.ftp_use_eprt = TRUE;
#endif

  for (; fcmd != DONE; fcmd++) {
    int lprtaf, eprtaf;
    int alen=0, plen=0;

    if(!conn->bits.ftp_use_eprt && (EPRT == fcmd))
      /* if disabled, goto next */
      continue;

    if(!conn->bits.ftp_use_lprt && (LPRT == fcmd))
      /* if disabled, goto next */
      continue;

    switch (sa->sa_family) {
    case AF_INET:
      ap = (unsigned char *)&((struct sockaddr_in *)&ss)->sin_addr;
      alen = sizeof(((struct sockaddr_in *)&ss)->sin_addr);
      pp = (unsigned char *)&((struct sockaddr_in *)&ss)->sin_port;
      plen = sizeof(((struct sockaddr_in *)&ss)->sin_port);
      lprtaf = 4;
      eprtaf = 1;
      break;
    case AF_INET6:
      ap = (unsigned char *)&((struct sockaddr_in6 *)&ss)->sin6_addr;
      alen = sizeof(((struct sockaddr_in6 *)&ss)->sin6_addr);
      pp = (unsigned char *)&((struct sockaddr_in6 *)&ss)->sin6_port;
      plen = sizeof(((struct sockaddr_in6 *)&ss)->sin6_port);
      lprtaf = 6;
      eprtaf = 2;
      break;
    default:
      ap = pp = NULL;
      lprtaf = eprtaf = -1;
      break;
    }

    if (EPRT == fcmd) {
      if (eprtaf < 0)
        continue;
      if (getnameinfo((struct sockaddr *)&ss, sslen,
                      portmsgbuf, sizeof(portmsgbuf), tmp, sizeof(tmp),
                      NIFLAGS))
        continue;

      /* do not transmit IPv6 scope identifier to the wire */
      if (sa->sa_family == AF_INET6) {
        char *q = strchr(portmsgbuf, '%');
        if (q)
          *q = '\0';
      }

      result = Curl_nbftpsendf(conn, "%s |%d|%s|%s|", mode[fcmd], eprtaf,
                               portmsgbuf, tmp);
      if(result)
        return result;
      break;
    }
    else if ((LPRT == fcmd) || (PORT == fcmd)) {
      int i;

      if ((LPRT == fcmd) && lprtaf < 0)
        continue;
      if ((PORT == fcmd) && sa->sa_family != AF_INET)
        continue;

      portmsgbuf[0] = '\0';
      if (LPRT == fcmd) {
        snprintf(tmp, sizeof(tmp), "%d,%d", lprtaf, alen);
        if (strlcat(portmsgbuf, tmp, sizeof(portmsgbuf)) >=
            sizeof(portmsgbuf)) {
          continue;
        }
      }

      for (i = 0; i < alen; i++) {
        if (portmsgbuf[0])
          snprintf(tmp, sizeof(tmp), ",%u", ap[i]);
        else
          snprintf(tmp, sizeof(tmp), "%u", ap[i]);

        if (strlcat(portmsgbuf, tmp, sizeof(portmsgbuf)) >=
            sizeof(portmsgbuf)) {
          continue;
        }
      }

      if (LPRT == fcmd) {
        snprintf(tmp, sizeof(tmp), ",%d", plen);

        if (strlcat(portmsgbuf, tmp, sizeof(portmsgbuf)) >= sizeof(portmsgbuf))
          continue;
      }

      for (i = 0; i < plen; i++) {
        snprintf(tmp, sizeof(tmp), ",%u", pp[i]);

        if (strlcat(portmsgbuf, tmp, sizeof(portmsgbuf)) >=
            sizeof(portmsgbuf)) {
          continue;
        }
      }

      result = Curl_nbftpsendf(conn, "%s %s", mode[fcmd], portmsgbuf);
      if(result)
        return result;
      break;
    }
  }

  /* store which command was sent */
  ftp->count1 = fcmd;

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
  char myhost[256] = "";
  bool sa_filled_in = FALSE;
  Curl_addrinfo *addr = NULL;
  unsigned short ip[4];
  (void)fcmd; /* not used in the IPv4 code */
  if(data->set.ftpport) {
    in_addr_t in;

    /* First check if the given name is an IP address */
    in=inet_addr(data->set.ftpport);

    if(in != CURL_INADDR_NONE)
      /* this is an IPv4 address */
      addr = Curl_ip2addr(in, data->set.ftpport, 0);
    else {
      if(Curl_if2ip(data->set.ftpport, myhost, sizeof(myhost))) {
        /* The interface to IP conversion provided a dotted address */
        in=inet_addr(myhost);
        addr = Curl_ip2addr(in, myhost, 0);
      }
      else if(strlen(data->set.ftpport)> 1) {
        /* might be a host name! */
        struct Curl_dns_entry *h=NULL;
        int rc = Curl_resolv(conn, myhost, 0, &h);
        if(rc == CURLRESOLV_PENDING)
          /* BLOCKING */
          rc = Curl_wait_for_resolv(conn, &h);
        if(h) {
          addr = h->addr;
          /* when we return from this function, we can forget about this entry
             so we can unlock it now already */
          Curl_resolv_unlock(data, h);
        } /* (h) */
      } /* strlen */
    } /* CURL_INADDR_NONE */
  } /* data->set.ftpport */

  if(!addr) {
    /* pick a suitable default here */

    socklen_t sslen;

    sslen = sizeof(sa);
    if (getsockname(conn->sock[FIRSTSOCKET],
                    (struct sockaddr *)&sa, &sslen) < 0) {
      failf(data, "getsockname() failed");
      return CURLE_FTP_PORT_FAILED;
    }

    sa_filled_in = TRUE; /* the sa struct is filled in */
  }

  if (addr || sa_filled_in) {
    portsock = socket(AF_INET, SOCK_STREAM, 0);
    if(CURL_SOCKET_BAD != portsock) {
      socklen_t size;

      /* we set the secondary socket variable to this for now, it
         is only so that the cleanup function will close it in case
         we fail before the true secondary stuff is made */
      if(CURL_SOCKET_BAD != conn->sock[SECONDARYSOCKET])
        sclose(conn->sock[SECONDARYSOCKET]);
      conn->sock[SECONDARYSOCKET] = portsock;

      if(!sa_filled_in) {
        memcpy(&sa, addr->ai_addr, sizeof(sa));
        sa.sin_addr.s_addr = INADDR_ANY;
      }

      sa.sin_port = 0;
      size = sizeof(sa);

      if(bind(portsock, (struct sockaddr *)&sa, size) >= 0) {
        /* we succeeded to bind */
        struct sockaddr_in add;
        socklen_t socksize = sizeof(add);

        if(getsockname(portsock, (struct sockaddr *) &add,
                       &socksize)<0) {
          failf(data, "getsockname() failed");
          return CURLE_FTP_PORT_FAILED;
        }
        porttouse = ntohs(add.sin_port);

        if ( listen(portsock, 1) < 0 ) {
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
    failf(data, "could't find IP address to use");
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

  Curl_freeaddrinfo(addr);

  ftp->count1 = PORT;

#endif /* end of ipv4-specific code */

  state(conn, FTP_PORT);
  return result;
}