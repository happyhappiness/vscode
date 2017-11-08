static
CURLcode ftp_use_port(struct connectdata *conn)
{
  struct SessionHandle *data=conn->data;
  int portsock=-1;
  ssize_t nread;
  int ftpcode; /* receive FTP response codes in this */
  CURLcode result;

#ifdef ENABLE_IPV6
  /******************************************************************
   *
   * Here's a piece of IPv6-specific code coming up
   *
   */

  struct addrinfo hints, *res, *ai;
  struct sockaddr_storage ss;
  socklen_t sslen;
  char hbuf[NI_MAXHOST];

  struct sockaddr *sa=(struct sockaddr *)&ss;
#ifdef NI_WITHSCOPEID
  const int niflags = NI_NUMERICHOST | NI_NUMERICSERV | NI_WITHSCOPEID;
#else
  const int niflags = NI_NUMERICHOST | NI_NUMERICSERV;
#endif
  unsigned char *ap;
  unsigned char *pp;
  char portmsgbuf[4096], tmp[4096];

  const char *mode[] = { "EPRT", "LPRT", "PORT", NULL };
  char **modep;

  /*
   * we should use Curl_if2ip?  given pickiness of recent ftpd,
   * I believe we should use the same address as the control connection.
   */
  sslen = sizeof(ss);
  if (getsockname(conn->firstsocket, (struct sockaddr *)&ss, &sslen) < 0)
    return CURLE_FTP_PORT_FAILED;
  
  if (getnameinfo((struct sockaddr *)&ss, sslen, hbuf, sizeof(hbuf), NULL, 0,
                  niflags))
    return CURLE_FTP_PORT_FAILED;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = sa->sa_family;
  /*hints.ai_family = ss.ss_family;
    this way can be used if sockaddr_storage is properly defined, as glibc 
    2.1.X doesn't do*/
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if (getaddrinfo(hbuf, (char *)"0", &hints, &res))
    return CURLE_FTP_PORT_FAILED;
  
  portsock = -1;
  for (ai = res; ai; ai = ai->ai_next) {
    portsock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (portsock < 0)
      continue;

    if (bind(portsock, ai->ai_addr, ai->ai_addrlen) < 0) {
      sclose(portsock);
      portsock = -1;
      continue;
    }
      
    if (listen(portsock, 1) < 0) {
      sclose(portsock);
      portsock = -1;
      continue;
    }
    
    break;
  }
  freeaddrinfo(res);
  if (portsock < 0) {
    failf(data, "%s", strerror(errno));
    return CURLE_FTP_PORT_FAILED;
  }

  sslen = sizeof(ss);
  if (getsockname(portsock, sa, &sslen) < 0) {
    failf(data, "%s", strerror(errno));
    return CURLE_FTP_PORT_FAILED;
  }

  for (modep = (char **)mode; modep && *modep; modep++) {
    int lprtaf, eprtaf;
    int alen=0, plen=0;
    
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

    if (strcmp(*modep, "EPRT") == 0) {
      if (eprtaf < 0)
        continue;
      if (getnameinfo((struct sockaddr *)&ss, sslen,
                      portmsgbuf, sizeof(portmsgbuf), tmp, sizeof(tmp), niflags))
        continue;

      /* do not transmit IPv6 scope identifier to the wire */
      if (sa->sa_family == AF_INET6) {
        char *q = strchr(portmsgbuf, '%');
          if (q)
            *q = '\0';
      }

      result = Curl_ftpsendf(conn, "%s |%d|%s|%s|", *modep, eprtaf,
                             portmsgbuf, tmp);
      if(result)
        return result;
    } else if (strcmp(*modep, "LPRT") == 0 ||
               strcmp(*modep, "PORT") == 0) {
      int i;
      
      if (strcmp(*modep, "LPRT") == 0 && lprtaf < 0)
        continue;
      if (strcmp(*modep, "PORT") == 0 && sa->sa_family != AF_INET)
        continue;

      portmsgbuf[0] = '\0';
      if (strcmp(*modep, "LPRT") == 0) {
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
      
      if (strcmp(*modep, "LPRT") == 0) {
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
      
      result = Curl_ftpsendf(conn, "%s %s", *modep, portmsgbuf);
      if(result)
        return result;
    }
    
    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
    if(result)
      return result;
    
    if (ftpcode != 200) {
      failf(data, "Server does not grok %s", *modep);
      continue;
    }
    else
      break;
  }
  
  if (!*modep) {
    sclose(portsock);
    return CURLE_FTP_PORT_FAILED;
  }
  /* we set the secondary socket variable to this for now, it
     is only so that the cleanup function will close it in case
     we fail before the true secondary stuff is made */
  conn->secondarysocket = portsock;
  
#else
  /******************************************************************
   *
   * Here's a piece of IPv4-specific code coming up
   *
   */
  struct sockaddr_in sa;
  struct Curl_dns_entry *h=NULL;
  unsigned short porttouse;
  char myhost[256] = "";
  bool sa_filled_in = FALSE;

  if(data->set.ftpport) {
    if(Curl_if2ip(data->set.ftpport, myhost, sizeof(myhost))) {
      h = Curl_resolv(data, myhost, 0);
    }
    else {
      int len = strlen(data->set.ftpport);
      if(len>1)
        h = Curl_resolv(data, data->set.ftpport, 0);
      if(h)
        strcpy(myhost, data->set.ftpport); /* buffer overflow risk */
    }
  }
  if(! *myhost) {
    /* pick a suitable default here */

    socklen_t sslen;
    
    sslen = sizeof(sa);
    if (getsockname(conn->firstsocket, (struct sockaddr *)&sa, &sslen) < 0) {
      failf(data, "getsockname() failed");
      return CURLE_FTP_PORT_FAILED;
    }

    sa_filled_in = TRUE; /* the sa struct is filled in */
  }

  if(h)
    /* when we return from here, we can forget about this */
    Curl_resolv_unlock(data, h);

  if ( h || sa_filled_in) {
    if( (portsock = socket(AF_INET, SOCK_STREAM, 0)) >= 0 ) {
      int size;
      
      /* we set the secondary socket variable to this for now, it
         is only so that the cleanup function will close it in case
         we fail before the true secondary stuff is made */
      conn->secondarysocket = portsock;

      if(!sa_filled_in) {
        memset((char *)&sa, 0, sizeof(sa));
        memcpy((char *)&sa.sin_addr,
               h->addr->h_addr,
               h->addr->h_length);
        sa.sin_family = AF_INET;
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
    failf(data, "could't find my own IP address (%s)", myhost);
    return CURLE_FTP_PORT_FAILED;
  }
  {
#ifdef HAVE_INET_NTOA_R
    char ntoa_buf[64];
#endif
    struct in_addr in;
    unsigned short ip[5];
    (void) memcpy(&in.s_addr,
                  h?*h->addr->h_addr_list:(char *)&sa.sin_addr.s_addr,
                  sizeof (in.s_addr));

#ifdef HAVE_INET_NTOA_R
    /* ignore the return code from inet_ntoa_r() as it is int or
       char * depending on system */
    inet_ntoa_r(in, ntoa_buf, sizeof(ntoa_buf));
    sscanf( ntoa_buf, "%hu.%hu.%hu.%hu",
            &ip[0], &ip[1], &ip[2], &ip[3]);
#else
    sscanf( inet_ntoa(in), "%hu.%hu.%hu.%hu",
            &ip[0], &ip[1], &ip[2], &ip[3]);
#endif
    infof(data, "Telling server to connect to %d.%d.%d.%d:%d\n",
          ip[0], ip[1], ip[2], ip[3], porttouse);
  
    result=Curl_ftpsendf(conn, "PORT %d,%d,%d,%d,%d,%d",
                         ip[0], ip[1], ip[2], ip[3],
                         porttouse >> 8,
                         porttouse & 255);
    if(result)
      return result;
  }

  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
  if(result)
    return result;

  if(ftpcode != 200) {
    failf(data, "Server does not grok PORT, try without it!");
    return CURLE_FTP_PORT_FAILED;
  }
#endif /* end of ipv4-specific code */

  return CURLE_OK;
}