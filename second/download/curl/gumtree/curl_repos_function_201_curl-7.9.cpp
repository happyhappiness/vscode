static
CURLcode _ftp(struct connectdata *conn)
{
  /* this is FTP and no proxy */
  ssize_t nread;
  CURLcode result;
  struct SessionHandle *data=conn->data;
  char *buf = data->state.buffer; /* this is our buffer */
  /* for the ftp PORT mode */
  int portsock=-1;
#if defined (HAVE_INET_NTOA_R)
  char ntoa_buf[64];
#endif
#ifdef ENABLE_IPV6
  struct addrinfo *ai;
#else
  struct sockaddr_in serv_addr;
  char hostent_buf[8192];
#endif

  /* the ftp struct is already inited in ftp_connect() */
  struct FTP *ftp = conn->proto.ftp;

  long *bytecountp = ftp->bytecountp;
  int ftpcode; /* for ftp status */

  /* Send any QUOTE strings? */
  if(data->set.quote) {
    if ((result = _ftp_sendquote(conn, data->set.quote)) != CURLE_OK)
      return result;
  }
    
  /* This is a re-used connection. Since we change directory to where the
     transfer is taking place, we must now get back to the original dir
     where we ended up after login: */
  if (conn->bits.reuse) {
    if ((result = _ftp_cwd(conn, ftp->entrypath)) != CURLE_OK)
      return result;
  }

  /* change directory first! */
  if(ftp->dir && ftp->dir[0]) {
    if ((result = _ftp_cwd(conn, ftp->dir)) != CURLE_OK)
        return result;
  }

  /* Requested time of file? */
  if(data->set.get_filetime && ftp->file) {
    result = _ftp_getfiletime(conn, ftp->file);
    if(result)
      return result;
  }

  /* If we have selected NOBODY, it means that we only want file information.
     Which in FTP can't be much more than the file size! */
  if(data->set.no_body) {
    /* The SIZE command is _not_ RFC 959 specified, and therefor many servers
       may not support it! It is however the only way we have to get a file's
       size! */
    ssize_t filesize;

    /* Some servers return different sizes for different modes, and thus we
       must set the proper type before we check the size */
    result = _ftp_transfertype(conn, data->set.ftp_ascii);
    if(result)
      return result;

    /* failing to get size is not a serious error */
    result = _ftp_getsize(conn, ftp->file, &filesize);

    if(CURLE_OK == result) {
      sprintf(buf, "Content-Length: %d\r\n", filesize);
      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
      if(result)
        return result;
    }

    /* If we asked for a time of the file and we actually got one as
       well, we "emulate" a HTTP-style header in our output. */

#ifdef HAVE_STRFTIME
    if(data->set.get_filetime && data->info.filetime) {
      struct tm *tm;
#ifdef HAVE_LOCALTIME_R
      struct tm buffer;
      tm = (struct tm *)localtime_r(&data->info.filetime, &buffer);
#else
      tm = localtime(&data->info.filetime);
#endif
      /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
      strftime(buf, BUFSIZE-1, "Last-Modified: %a, %d %b %Y %H:%M:%S %Z\r\n",
               tm);
      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
      if(result)
        return result;
    }
#endif

    return CURLE_OK;
  }

  /* We have chosen to use the PORT command */
  if(data->set.ftp_use_port) {
#ifdef ENABLE_IPV6
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
    int alen, plen;
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
    if (getaddrinfo(hbuf, "0", &hints, &res))
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
    if (portsock < 0) {
      failf(data, strerror(errno));
      freeaddrinfo(res);
      return CURLE_FTP_PORT_FAILED;
    }

    sslen = sizeof(ss);
    if (getsockname(portsock, sa, &sslen) < 0) {
      failf(data, strerror(errno));
      freeaddrinfo(res);
      return CURLE_FTP_PORT_FAILED;
    }

    for (modep = (char *)mode; modep && *modep; modep++) {
      int lprtaf, eprtaf;

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

        ftpsendf(conn->firstsocket, conn, "%s |%d|%s|%s|", *modep, eprtaf,
                 portmsgbuf, tmp);
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
          if (strlcat(portmsgbuf, tmp, sizeof(portmsgbuf)) >= sizeof(portmsgbuf)) {
            continue;
          }
        }

        for (i = 0; i < alen; i++) {
          if (portmsgbuf[0])
            snprintf(tmp, sizeof(tmp), ",%u", ap[i]);
          else
            snprintf(tmp, sizeof(tmp), "%u", ap[i]);

          if (strlcat(portmsgbuf, tmp, sizeof(portmsgbuf)) >= sizeof(portmsgbuf)) {
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

          if (strlcat(portmsgbuf, tmp, sizeof(portmsgbuf)) >= sizeof(portmsgbuf)) {
              continue;
          }
        }

        ftpsendf(conn->firstsocket, conn, "%s %s", *modep, portmsgbuf);
      }

      nread = Curl_GetFTPResponse(conn->firstsocket, buf, conn, &ftpcode);
      if(nread < 0)
        return CURLE_OPERATION_TIMEOUTED;

      if (ftpcode != 200) {
        failf(data, "Server does not grok %s", *modep);
        continue;
      } else
        break;
    }

    if (!*modep) {
      sclose(portsock);
      freeaddrinfo(res);
      return CURLE_FTP_PORT_FAILED;
    }
    /* we set the secondary socket variable to this for now, it
       is only so that the cleanup function will close it in case
       we fail before the true secondary stuff is made */
    conn->secondarysocket = portsock;

#else
    struct sockaddr_in sa;
    struct hostent *h=NULL;
    char *hostdataptr=NULL;
    size_t size;
    unsigned short porttouse;
    char myhost[256] = "";

    if(data->set.ftpport) {
      if(Curl_if2ip(data->set.ftpport, myhost, sizeof(myhost))) {
        h = Curl_gethost(data, myhost, &hostdataptr);
      }
      else {
        if(strlen(data->set.ftpport)>1)
          h = Curl_gethost(data, data->set.ftpport, &hostdataptr);
        if(h)
          strcpy(myhost, data->set.ftpport); /* buffer overflow risk */
      }
    }
    if(! *myhost) {
      h=Curl_gethost(data,
                     getmyhost(myhost, sizeof(myhost)),
                     &hostdataptr);
    }
    infof(data, "We connect from %s\n", myhost);

    if ( h ) {
      if( (portsock = socket(AF_INET, SOCK_STREAM, 0)) >= 0 ) {

        /* we set the secondary socket variable to this for now, it
           is only so that the cleanup function will close it in case
           we fail before the true secondary stuff is made */
        conn->secondarysocket = portsock;

        memset((char *)&sa, 0, sizeof(sa));
        memcpy((char *)&sa.sin_addr,
               h->h_addr,
               h->h_length);
        sa.sin_family = AF_INET;
        sa.sin_addr.s_addr = INADDR_ANY;
        sa.sin_port = 0;
        size = sizeof(sa);

        if(bind(portsock, (struct sockaddr *)&sa, size) >= 0) {
          /* we succeeded to bind */
          struct sockaddr_in add;
          size = sizeof(add);

          if(getsockname(portsock, (struct sockaddr *) &add,
                         (socklen_t *)&size)<0) {
            failf(data, "getsockname() failed");
            return CURLE_FTP_PORT_FAILED;
          }
          porttouse = ntohs(add.sin_port);

          if ( listen(portsock, 1) < 0 ) {
            failf(data, "listen(2) failed on socket");
            free(hostdataptr);
            return CURLE_FTP_PORT_FAILED;
          }
        }
        else {
          failf(data, "bind(2) failed on socket");
          free(hostdataptr);
          return CURLE_FTP_PORT_FAILED;
        }
      }
      else {
        failf(data, "socket(2) failed (%s)");
        free(hostdataptr);
        return CURLE_FTP_PORT_FAILED;
      }
      if(hostdataptr)
        /* free the memory used for name lookup */
        free(hostdataptr);
    }
    else {
      failf(data, "could't find my own IP address (%s)", myhost);
      return CURLE_FTP_PORT_FAILED;
    }
    {
      struct in_addr in;
      unsigned short ip[5];
      (void) memcpy(&in.s_addr, *h->h_addr_list, sizeof (in.s_addr));
#if defined (HAVE_INET_NTOA_R)
      /* ignore the return code from inet_ntoa_r() as it is int or
         char * depending on system */
      inet_ntoa_r(in, ntoa_buf, sizeof(ntoa_buf));
      sscanf( ntoa_buf, "%hu.%hu.%hu.%hu",
              &ip[0], &ip[1], &ip[2], &ip[3]);
#else
      sscanf( inet_ntoa(in), "%hu.%hu.%hu.%hu",
              &ip[0], &ip[1], &ip[2], &ip[3]);
#endif
      ftpsendf(conn->firstsocket, conn, "PORT %d,%d,%d,%d,%d,%d",
            ip[0], ip[1], ip[2], ip[3],
            porttouse >> 8,
            porttouse & 255);
    }

    nread = Curl_GetFTPResponse(conn->firstsocket, buf, conn, &ftpcode);
    if(nread < 0)
      return CURLE_OPERATION_TIMEOUTED;

    if(ftpcode != 200) {
      failf(data, "Server does not grok PORT, try without it!");
      return CURLE_FTP_PORT_FAILED;
    }     
#endif /* ENABLE_IPV6 */
  }
  else { /* we use the PASV command */
#if 0
    /* no support for IPv6 passive mode yet */
    char *mode[] = { "EPSV", "LPSV", "PASV", NULL };
    int results[] = { 229, 228, 227, 0 };
#else
    const char *mode[] = { "PASV", NULL };
    int results[] = { 227, 0 };
#endif
    int modeoff;

    for (modeoff = 0; mode[modeoff]; modeoff++) {
      ftpsendf(conn->firstsocket, conn, mode[modeoff]);
      nread = Curl_GetFTPResponse(conn->firstsocket, buf, conn, &ftpcode);
      if(nread < 0)
        return CURLE_OPERATION_TIMEOUTED;

      if (ftpcode == results[modeoff])
        break;
    }

    if (!mode[modeoff]) {
      failf(data, "Odd return code after PASV");
      return CURLE_FTP_WEIRD_PASV_REPLY;
    }
    else if (strcmp(mode[modeoff], "PASV") == 0) {
      int ip[4];
      int port[2];
      unsigned short newport; /* remote port, not necessary the local one */
      unsigned short connectport; /* the local port connect() should use! */
      char newhost[32];
#ifdef ENABLE_IPV6
      struct addrinfo *res;
#else
      struct hostent *he;
      char *hostdataptr=NULL;
      char *ip_addr;
#endif
      char *str=buf;

      /*
       * New 227-parser June 3rd 1999.
       * It now scans for a sequence of six comma-separated numbers and
       * will take them as IP+port indicators.
       *
       * Found reply-strings include:
       * "227 Entering Passive Mode (127,0,0,1,4,51)"
       * "227 Data transfer will passively listen to 127,0,0,1,4,51"
       * "227 Entering passive mode. 127,0,0,1,4,51"
       */
      
      while(*str) {
	      if (6 == sscanf(str, "%d,%d,%d,%d,%d,%d",
                        &ip[0], &ip[1], &ip[2], &ip[3],
                        &port[0], &port[1]))
    	    break;
        str++;
      }

      if(!*str) {
        failf(data, "Couldn't interpret this 227-reply: %s", buf);
        return CURLE_FTP_WEIRD_227_FORMAT;
      }

      sprintf(newhost, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
      newport = (port[0]<<8) + port[1];
      if(data->change.proxy) {
        /*
         * This is a tunnel through a http proxy and we need to connect to the
         * proxy again here. We already have the name info for it since the
         * previous lookup.
         */
#ifdef ENABLE_IPV6
        res = conn->hp;
#else
        he = conn->hp;
#endif
        connectport =
          (unsigned short)conn->port; /* we connect to the proxy's port */
      }
      else {
        /* normal, direct, ftp connection */
#ifdef ENABLE_IPV6
        res = Curl_getaddrinfo(data, newhost, newport);
        if(!res)
#else
        he = Curl_gethost(data, newhost, &hostdataptr);
        if(!he)
#endif
        {
          failf(data, "Can't resolve new host %s", newhost);
          return CURLE_FTP_CANT_GET_HOST;
        }
        connectport = newport; /* we connect to the remote port */
      }
	
#ifdef ENABLE_IPV6
      conn->secondarysocket = -1;
      for (ai = res; ai; ai = ai->ai_next) {
        /* XXX for now, we can do IPv4 only */
        if (ai->ai_family != AF_INET)
          continue;

        conn->secondarysocket = socket(ai->ai_family, ai->ai_socktype,
                                       ai->ai_protocol);
        if (conn->secondarysocket < 0)
          continue;

      	if(data->set.verbose) {
          char hbuf[NI_MAXHOST];
          char nbuf[NI_MAXHOST];
          char sbuf[NI_MAXSERV];
#ifdef NI_WITHSCOPEID
          const int niflags = NI_NUMERICHOST | NI_NUMERICSERV | NI_WITHSCOPEID;
#else
          const int niflags = NI_NUMERICHOST | NI_NUMERICSERV;
#endif
          if (getnameinfo(res->ai_addr, res->ai_addrlen, nbuf, sizeof(nbuf),
                          sbuf, sizeof(sbuf), niflags)) {
            snprintf(nbuf, sizeof(nbuf), "?");
            snprintf(sbuf, sizeof(sbuf), "?");
          }
        
          if (getnameinfo(res->ai_addr, res->ai_addrlen, hbuf, sizeof(hbuf),
                          NULL, 0, 0)) {
            infof(data, "Connecting to %s port %s\n", nbuf, sbuf);
          } else {
            infof(data, "Connecting to %s (%s) port %s\n", hbuf, nbuf, sbuf);
          }
        }

        if (connect(conn->secondarysocket, ai->ai_addr, ai->ai_addrlen) < 0) {
          close(conn->secondarysocket);
          conn->secondarysocket = -1;
          continue;
        }

      	break;
      }

      if (conn->secondarysocket < 0) {
        failf(data, strerror(errno));
        return CURLE_FTP_CANT_RECONNECT;
      }
#else
      conn->secondarysocket = socket(AF_INET, SOCK_STREAM, 0);

      memset((char *) &serv_addr, '\0', sizeof(serv_addr));
      memcpy((char *)&(serv_addr.sin_addr), he->h_addr, he->h_length);
      serv_addr.sin_family = he->h_addrtype;

      serv_addr.sin_port = htons(connectport);

      if(data->set.verbose) {
        struct in_addr in;
        struct hostent * answer;

#if defined(HAVE_INET_ADDR)
        unsigned long address;
# if defined(HAVE_GETHOSTBYADDR_R)
        int h_errnop;
# endif

        address = inet_addr(newhost);
# ifdef HAVE_GETHOSTBYADDR_R

#  ifdef HAVE_GETHOSTBYADDR_R_5
        /* AIX, Digital Unix style:
           extern int gethostbyaddr_r(char *addr, size_t len, int type,
           struct hostent *htent, struct hostent_data *ht_data); */

        /* Fred Noz helped me try this out, now it at least compiles! */

        if(gethostbyaddr_r((char *) &address,
                           sizeof(address), AF_INET,
                           (struct hostent *)hostent_buf,
                           hostent_buf + sizeof(*answer)))
           answer=NULL;
                           
#  endif
#  ifdef HAVE_GETHOSTBYADDR_R_7
        /* Solaris and IRIX */
        answer = gethostbyaddr_r((char *) &address, sizeof(address), AF_INET,
                                 (struct hostent *)hostent_buf,
                                 hostent_buf + sizeof(*answer),
                                 sizeof(hostent_buf) - sizeof(*answer),
                                 &h_errnop);
#  endif
#  ifdef HAVE_GETHOSTBYADDR_R_8
        /* Linux style */
        if(gethostbyaddr_r((char *) &address, sizeof(address), AF_INET,
                           (struct hostent *)hostent_buf,
                           hostent_buf + sizeof(*answer),
                           sizeof(hostent_buf) - sizeof(*answer),
                           &answer,
                           &h_errnop))
           answer=NULL; /* error */
#  endif
        
# else
        answer = gethostbyaddr((char *) &address, sizeof(address), AF_INET);
# endif
#else
        answer = NULL;
#endif
        (void) memcpy(&in.s_addr, *he->h_addr_list, sizeof (in.s_addr));
        infof(data, "Connecting to %s (%s) port %u\n",
              answer?answer->h_name:newhost,
#if defined(HAVE_INET_NTOA_R)
              inet_ntoa_r(in, ip_addr=ntoa_buf, sizeof(ntoa_buf)),
#else
              ip_addr = inet_ntoa(in),
#endif
              connectport);
      }
	
      if(hostdataptr)
        free(hostdataptr);

      if (connect(conn->secondarysocket, (struct sockaddr *) &serv_addr,
                  sizeof(serv_addr)) < 0) {
        switch(errno) {
#ifdef ECONNREFUSED
          /* this should be made nicer */
        case ECONNREFUSED:
          failf(data, "Connection refused by ftp server");
          break;
#endif
#ifdef EINTR
        case EINTR:
          failf(data, "Connection timed out to ftp server");
          break;
#endif
        default:
          failf(data, "Can't connect to ftp server");
          break;
        }
        return CURLE_FTP_CANT_RECONNECT;
      }
#endif /*ENABLE_IPV6*/

      if (data->set.tunnel_thru_httpproxy) {
        /* We want "seamless" FTP operations through HTTP proxy tunnel */
        result = Curl_ConnectHTTPProxyTunnel(conn, conn->secondarysocket,
                                             newhost, newport);
        if(CURLE_OK != result)
          return result;
      }
    } else {
      return CURLE_FTP_CANT_RECONNECT;
    }
  }
  /* we have the (new) data connection ready */
  infof(data, "Connected the data stream!\n");

  if(data->set.upload) {

    /* Set type to binary (unless specified ASCII) */
    result = _ftp_transfertype(conn, data->set.ftp_ascii);
    if(result)
      return result;

    if(conn->resume_from) {
      /* we're about to continue the uploading of a file */
      /* 1. get already existing file's size. We use the SIZE
         command for this which may not exist in the server!
         The SIZE command is not in RFC959. */

      /* 2. This used to set REST. But since we can do append, we
         don't another ftp command. We just skip the source file
         offset and then we APPEND the rest on the file instead */

      /* 3. pass file-size number of bytes in the source file */
      /* 4. lower the infilesize counter */
      /* => transfer as usual */

      if(conn->resume_from < 0 ) {
        /* we could've got a specified offset from the command line,
           but now we know we didn't */

        if(CURLE_OK != _ftp_getsize(conn, ftp->file, &conn->resume_from)) {
          failf(data, "Couldn't get remote file size");
          return CURLE_FTP_COULDNT_GET_SIZE;
        }
      }

      if(conn->resume_from) {
        /* do we still game? */
        int passed=0;
        /* enable append instead */
        data->set.ftp_append = 1;

        /* Now, let's read off the proper amount of bytes from the
           input. If we knew it was a proper file we could've just
           fseek()ed but we only have a stream here */
        do {
          int readthisamountnow = (conn->resume_from - passed);
          int actuallyread;

          if(readthisamountnow > BUFSIZE)
            readthisamountnow = BUFSIZE;

          actuallyread =
            data->set.fread(data->state.buffer, 1, readthisamountnow,
                            data->set.in);

          passed += actuallyread;
          if(actuallyread != readthisamountnow) {
            failf(data, "Could only read %d bytes from the input\n", passed);
            return CURLE_FTP_COULDNT_USE_REST;
          }
        }
        while(passed != conn->resume_from);

        /* now, decrease the size of the read */
        if(data->set.infilesize>0) {
          data->set.infilesize -= conn->resume_from;

          if(data->set.infilesize <= 0) {
            infof(data, "File already completely uploaded\n");

            /* no data to transfer */
            result=Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
            
            /* Set resume done so that we won't get any error in
             * Curl_ftp_done() because we didn't transfer the amount of bytes
             * that the local file file obviously is */
            conn->bits.resume_done = TRUE; 

            return CURLE_OK;
          }
        }
        /* we've passed, proceed as normal */
      }
    }

    /* Send everything on data->set.in to the socket */
    if(data->set.ftp_append)
      /* we append onto the file instead of rewriting it */
      ftpsendf(conn->firstsocket, conn, "APPE %s", ftp->file);
    else
      ftpsendf(conn->firstsocket, conn, "STOR %s", ftp->file);

    nread = Curl_GetFTPResponse(conn->firstsocket, buf, conn, &ftpcode);
    if(nread < 0)
      return CURLE_OPERATION_TIMEOUTED;

    if(ftpcode>=400) {
      failf(data, "Failed FTP upload:%s", buf+3);
      /* oops, we never close the sockets! */
      return CURLE_FTP_COULDNT_STOR_FILE;
    }

    if(data->set.ftp_use_port) {
      /* PORT means we are now awaiting the server to connect to us. */
      result = AllowServerConnect(data, conn, portsock);
      if( result )
        return result;
    }

    *bytecountp=0;

    /* When we know we're uploading a specified file, we can get the file
       size prior to the actual upload. */

    Curl_pgrsSetUploadSize(data, data->set.infilesize);

    result = Curl_Transfer(conn, -1, -1, FALSE, NULL, /* no download */
                      conn->secondarysocket, bytecountp);
    if(result)
      return result;
      
  }
  else {
    /* Retrieve file or directory */
    bool dirlist=FALSE;
    long downloadsize=-1;

    if(conn->bits.use_range && conn->range) {
      long from, to;
      int totalsize=-1;
      char *ptr;
      char *ptr2;

      from=strtol(conn->range, &ptr, 0);
      while(ptr && *ptr && (isspace((int)*ptr) || (*ptr=='-')))
        ptr++;
      to=strtol(ptr, &ptr2, 0);
      if(ptr == ptr2) {
        /* we didn't get any digit */
        to=-1;
      }
      if((-1 == to) && (from>=0)) {
        /* X - */
        conn->resume_from = from;
        infof(data, "FTP RANGE %d to end of file\n", from);
      }
      else if(from < 0) {
        /* -Y */
        totalsize = -from;
        conn->maxdownload = -from;
        conn->resume_from = from;
        infof(data, "FTP RANGE the last %d bytes\n", totalsize);
      }
      else {
        /* X-Y */
        totalsize = to-from;
        conn->maxdownload = totalsize+1; /* include the last mentioned byte */
        conn->resume_from = from;
        infof(data, "FTP RANGE from %d getting %d bytes\n", from,
              conn->maxdownload);
      }
      infof(data, "range-download from %d to %d, totally %d bytes\n",
            from, to, totalsize);
    }

    if((data->set.ftp_list_only) || !ftp->file) {
      /* The specified path ends with a slash, and therefore we think this
         is a directory that is requested, use LIST. But before that we
         need to set ASCII transfer mode. */
      dirlist = TRUE;

      /* Set type to ASCII */
      result = _ftp_transfertype(conn, TRUE /* ASCII enforced */);
      if(result)
        return result;

      /* if this output is to be machine-parsed, the NLST command will be
         better used since the LIST command output is not specified or
         standard in any way */

      ftpsendf(conn->firstsocket, conn, "%s",
            data->set.customrequest?data->set.customrequest:
            (data->set.ftp_list_only?"NLST":"LIST"));
    }
    else {
      /* Set type to binary (unless specified ASCII) */
      result = _ftp_transfertype(conn, data->set.ftp_ascii);
      if(result)
        return result;

      if(conn->resume_from) {

        /* Daniel: (August 4, 1999)
         *
         * We start with trying to use the SIZE command to figure out the size
         * of the file we're gonna get. If we can get the size, this is by far
         * the best way to know if we're trying to resume beyond the EOF.  */
        int foundsize=-1;
        
        result = _ftp_getsize(conn, ftp->file, &foundsize);

        if(CURLE_OK != result) {
          infof(data, "ftp server doesn't support SIZE\n");
          /* We couldn't get the size and therefore we can't know if there
             really is a part of the file left to get, although the server
             will just close the connection when we start the connection so it
             won't cause us any harm, just not make us exit as nicely. */
        }
        else {
          /* We got a file size report, so we check that there actually is a
             part of the file left to get, or else we go home.  */
          if(conn->resume_from< 0) {
            /* We're supposed to download the last abs(from) bytes */
            if(foundsize < -conn->resume_from) {
              failf(data, "Offset (%d) was beyond file size (%d)",
                    conn->resume_from, foundsize);
              return CURLE_FTP_BAD_DOWNLOAD_RESUME;
            }
            /* convert to size to download */
            downloadsize = -conn->resume_from;
            /* download from where? */
            conn->resume_from = foundsize - downloadsize;
          }
          else {
            if(foundsize < conn->resume_from) {
              failf(data, "Offset (%d) was beyond file size (%d)",
                    conn->resume_from, foundsize);
              return CURLE_FTP_BAD_DOWNLOAD_RESUME;
            }
            /* Now store the number of bytes we are expected to download */
            downloadsize = foundsize-conn->resume_from;
          }
        }

        if (downloadsize == 0) {
          /* no data to transfer */
          result=Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
          infof(data, "File already completely downloaded\n");

          /* Set resume done so that we won't get any error in Curl_ftp_done()
           * because we didn't transfer the amount of bytes that the remote
           * file obviously is */
          conn->bits.resume_done = TRUE; 

          return CURLE_OK;
        }
	
        /* Set resume file transfer offset */
        infof(data, "Instructs server to resume from offset %d\n",
              conn->resume_from);

        ftpsendf(conn->firstsocket, conn, "REST %d", conn->resume_from);

        nread = Curl_GetFTPResponse(conn->firstsocket, buf, conn, &ftpcode);
        if(nread < 0)
          return CURLE_OPERATION_TIMEOUTED;

        if(ftpcode != 350) {
          failf(data, "Couldn't use REST: %s", buf+4);
          return CURLE_FTP_COULDNT_USE_REST;
        }
      }

      ftpsendf(conn->firstsocket, conn, "RETR %s", ftp->file);
    }

    nread = Curl_GetFTPResponse(conn->firstsocket, buf, conn, &ftpcode);
    if(nread < 0)
      return CURLE_OPERATION_TIMEOUTED;

    if((ftpcode == 150) || (ftpcode == 125)) {

      /*
        A;
        150 Opening BINARY mode data connection for /etc/passwd (2241
        bytes).  (ok, the file is being transfered)
	
        B:
        150 Opening ASCII mode data connection for /bin/ls 

        C:
        150 ASCII data connection for /bin/ls (137.167.104.91,37445) (0 bytes).

        D:
        150 Opening ASCII mode data connection for /linux/fisk/kpanelrc (0.0.0.0,0) (545 bytes).
          
        E:
        125 Data connection already open; Transfer starting. */

      int size=-1; /* default unknown size */

      if(!dirlist &&
         !data->set.ftp_ascii &&
         (-1 == downloadsize)) {
        /*
         * It seems directory listings either don't show the size or very
         * often uses size 0 anyway. ASCII transfers may very well turn out
         * that the transfered amount of data is not the same as this line
         * tells, why using this number in those cases only confuses us.
         *
         * Example D above makes this parsing a little tricky */
        char *bytes;
        bytes=strstr(buf, " bytes");
        if(bytes--) {
          int index=bytes-buf;
          /* this is a hint there is size information in there! ;-) */
          while(--index) {
            /* scan for the parenthesis and break there */
            if('(' == *bytes)
              break;
            /* if only skip digits, or else we're in deep trouble */
            if(!isdigit((int)*bytes)) {
              bytes=NULL;
              break;
            }
            /* one more estep backwards */
            bytes--;
          }
          /* only if we have nothing but digits: */
          if(bytes++) {
            /* get the number! */
            size = atoi(bytes);
          }
            
        }
      }
      else if(downloadsize > -1)
        size = downloadsize;

      if(data->set.ftp_use_port) {
        result = AllowServerConnect(data, conn, portsock);
        if( result )
          return result;
      }

      infof(data, "Getting file with size: %d\n", size);

      /* FTP download: */
      result=Curl_Transfer(conn, conn->secondarysocket, size, FALSE,
                           bytecountp,
                           -1, NULL); /* no upload here */
      if(result)
        return result;
    }
    else {
      failf(data, "%s", buf+4);
      return CURLE_FTP_COULDNT_RETR_FILE;
    }
	
  }
  /* end of transfer */

  return CURLE_OK;
}