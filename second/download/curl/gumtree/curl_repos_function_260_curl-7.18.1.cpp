int main(int argc, char *argv[])
{
  struct sockaddr_in me;
#ifdef ENABLE_IPV6
  struct sockaddr_in6 me6;
#endif /* ENABLE_IPV6 */
  curl_socket_t sock, msgsock;
  int flag;
  unsigned short port = DEFAULT_PORT;
  char *pidname= (char *)".http.pid";
  struct httprequest req;
  int rc;
  int arg=1;
#ifdef CURL_SWS_FORK_ENABLED
  bool use_fork = FALSE;
#endif

  while(argc>arg) {
    if(!strcmp("--version", argv[arg])) {
      printf("sws IPv4%s"
#ifdef CURL_SWS_FORK_ENABLED
             " FORK"
#endif
             "\n"
             ,
#ifdef ENABLE_IPV6
             "/IPv6"
#else
             ""
#endif
             );
      return 0;
    }
    else if(!strcmp("--pidfile", argv[arg])) {
      arg++;
      if(argc>arg)
        pidname = argv[arg++];
    }
    else if(!strcmp("--ipv6", argv[arg])) {
#ifdef ENABLE_IPV6
      use_ipv6=TRUE;
#endif
      arg++;
    }
#ifdef CURL_SWS_FORK_ENABLED
    else if(!strcmp("--fork", argv[arg])) {
      use_fork=TRUE;
      arg++;
    }
#endif
    else if(argc>arg) {

      if(atoi(argv[arg]))
        port = (unsigned short)atoi(argv[arg++]);

      if(argc>arg)
        path = argv[arg++];
    }
  }

#ifdef WIN32
  win32_init();
  atexit(win32_cleanup);
#else

#ifdef SIGPIPE
#ifdef HAVE_SIGNAL
  signal(SIGPIPE, sigpipe_handler);
#endif
#ifdef HAVE_SIGINTERRUPT
  siginterrupt(SIGPIPE, 1);
#endif
#endif
#endif

#ifdef ENABLE_IPV6
  if(!use_ipv6)
#endif
    sock = socket(AF_INET, SOCK_STREAM, 0);
#ifdef ENABLE_IPV6
  else
    sock = socket(AF_INET6, SOCK_STREAM, 0);
#endif

  if (CURL_SOCKET_BAD == sock) {
    logmsg("Error opening socket: %d", SOCKERRNO);
    return 1;
  }

  flag = 1;
  if (0 != setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
            (void *) &flag, sizeof(flag))) {
    logmsg("setsockopt(SO_REUSEADDR) failed: %d", SOCKERRNO);
    sclose(sock);
    return 1;
  }

#ifdef ENABLE_IPV6
  if(!use_ipv6) {
#endif
    memset(&me, 0, sizeof(me));
    me.sin_family = AF_INET;
    me.sin_addr.s_addr = INADDR_ANY;
    me.sin_port = htons(port);
    rc = bind(sock, (struct sockaddr *) &me, sizeof(me));
#ifdef ENABLE_IPV6
  }
  else {
    memset(&me6, 0, sizeof(me6));
    me6.sin6_family = AF_INET6;
    me6.sin6_addr = in6addr_any;
    me6.sin6_port = htons(port);
    rc = bind(sock, (struct sockaddr *) &me6, sizeof(me6));
  }
#endif /* ENABLE_IPV6 */
  if(0 != rc) {
    logmsg("Error binding socket: %d", SOCKERRNO);
    sclose(sock);
    return 1;
  }

  if(!write_pidfile(pidname)) {
    sclose(sock);
    return 1;
  }

  logmsg("Running IPv%d version on port %d",
#ifdef ENABLE_IPV6
         (use_ipv6?6:4)
#else
         4
#endif
         , port );

  /* start accepting connections */
  rc = listen(sock, 5);
  if(0 != rc) {
    logmsg("listen() failed with error: %d", SOCKERRNO);
    sclose(sock);
    return 1;
  }

  while (1) {
    msgsock = accept(sock, NULL, NULL);

    if (CURL_SOCKET_BAD == msgsock) {
      printf("MAJOR ERROR: accept() failed with error: %d\n", SOCKERRNO);
      break;
    }

#ifdef CURL_SWS_FORK_ENABLED
    if(use_fork) {
      /* The fork enabled version just forks off the child and don't care
         about it anymore, so don't assume otherwise. Beware and don't do
         this at home. */
      rc = fork();
      if(-1 == rc) {
        printf("MAJOR ERROR: fork() failed!\n");
        break;
      }
    }
    else
      /* not a fork, just set rc so the following proceeds nicely */
      rc = 0;
    /* 0 is returned to the child */
    if(0 == rc) {
#endif
    logmsg("====> Client connect");

#ifdef TCP_NODELAY
    /*
     * Disable the Nagle algorithm to make it easier to send out a large
     * response in many small segments to torture the clients more.
     */
    flag = 1;
    if (setsockopt(msgsock, IPPROTO_TCP, TCP_NODELAY,
                   (void *)&flag, sizeof(flag)) == -1) {
      logmsg("====> TCP_NODELAY failed");
    }
#endif

    /* initialization of httprequest struct is done in get_request(), but due
       to pipelining treatment the pipelining struct field must be initialized
       previously to FALSE every time a new connection arrives. */

    req.pipelining = FALSE;

    do {
      if(get_request(msgsock, &req))
        /* non-zero means error, break out of loop */
        break;

      if(prevbounce) {
        /* bounce treatment requested */
        if((req.testno == prevtestno) &&
           (req.partno == prevpartno)) {
          req.partno++;
          logmsg("BOUNCE part number to %ld", req.partno);
        }
        else {
          prevbounce = FALSE;
          prevtestno = -1;
          prevpartno = -1;
        }
      }

      send_doc(msgsock, &req);

      if((req.testno < 0) && (req.testno != DOCNUMBER_CONNECT)) {
        logmsg("special request received, no persistancy");
        break;
      }
      if(!req.open) {
        logmsg("instructed to close connection after server-reply");
        break;
      }

      if(req.open)
        logmsg("=> persistant connection request ended, awaits new request");
      /* if we got a CONNECT, loop and get another request as well! */
    } while(req.open || (req.testno == DOCNUMBER_CONNECT));

    logmsg("====> Client disconnect");
    sclose(msgsock);

    if (req.testno == DOCNUMBER_QUIT)
      break;
#ifdef CURL_SWS_FORK_ENABLED
    }
#endif
  }

  sclose(sock);

  return 0;
}