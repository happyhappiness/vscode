int main(int argc, char *argv[])
{
  struct sockaddr_in me;
#ifdef ENABLE_IPV6
  struct sockaddr_in6 me6;
#endif /* ENABLE_IPV6 */
  int sock, msgsock, flag;
  unsigned short port = DEFAULT_PORT;
  FILE *pidfile;
  char *pidname= (char *)".http.pid";
  struct httprequest req;
  int rc;
  int arg=1;

  while(argc>arg) {
    if(!strcmp("--version", argv[arg])) {
      printf("sws IPv4%s\n",
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
    else if(argc>arg) {

      if(atoi(argv[arg]))
        port = (unsigned short)atoi(argv[arg++]);

      if(argc>arg)
        path = argv[arg++];
    }
  }

#if defined(WIN32) && !defined(__GNUC__) || defined(__MINGW32__)
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

  if (sock < 0) {
    perror("opening stream socket");
    logmsg("Error opening socket");
    exit(1);
  }

  flag = 1;
  if (setsockopt
      (sock, SOL_SOCKET, SO_REUSEADDR, (const void *) &flag,
       sizeof(int)) < 0) {
    perror("setsockopt(SO_REUSEADDR)");
  }

#ifdef ENABLE_IPV6
  if(!use_ipv6) {
#endif
    me.sin_family = AF_INET;
    me.sin_addr.s_addr = INADDR_ANY;
    me.sin_port = htons(port);
    rc = bind(sock, (struct sockaddr *) &me, sizeof(me));
#ifdef ENABLE_IPV6
  }
  else {
    memset(&me6, 0, sizeof(struct sockaddr_in6));
    me6.sin6_family = AF_INET6;
    me6.sin6_addr = in6addr_any;
    me6.sin6_port = htons(port);
    rc = bind(sock, (struct sockaddr *) &me6, sizeof(me6));
  }
#endif /* ENABLE_IPV6 */
  if(rc < 0) {
    perror("binding stream socket");
    logmsg("Error binding socket");
    exit(1);
  }

  pidfile = fopen(pidname, "w");
  if(pidfile) {
    fprintf(pidfile, "%d\n", (int)getpid());
    fclose(pidfile);
  }
  else
    fprintf(stderr, "Couldn't write pid file\n");

  logmsg("Running IPv%d version on port %d",
#ifdef ENABLE_IPV6
         (use_ipv6?6:4)
#else
         4
#endif
	 , port );

  /* start accepting connections */
  listen(sock, 5);

  while (1) {
    msgsock = accept(sock, NULL, NULL);

    if (msgsock == -1)
      continue;

    logmsg("====> Client connect");

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
  }

  sclose(sock);

  return 0;
}