int main(int argc, char *argv[])
{
  struct sockaddr_in me;
#ifdef ENABLE_IPV6
  struct sockaddr_in6 me6;
#endif /* ENABLE_IPV6 */
  int sock;
  int msgsock = CURL_SOCKET_BAD; /* no stream socket yet */
  int flag;
  FILE *pidfile;
  char *pidname= (char *)".sockfilt.pid";
  int rc;
  int arg=1;
  bool ok = FALSE;
  enum sockmode mode = PASSIVE_LISTEN; /* default */

  while(argc>arg) {
    if(!strcmp("--version", argv[arg])) {
      printf("sockfilt IPv4%s\n",
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
    else if(!strcmp("--logfile", argv[arg])) {
      arg++;
      if(argc>arg)
        serverlogfile = argv[arg++];
    }
    else if(!strcmp("--ipv6", argv[arg])) {
#ifdef ENABLE_IPV6
      use_ipv6=TRUE;
#endif
      arg++;
    }
    else if(!strcmp("--ipv4", argv[arg])) {
      /* for completeness, we support this option as well */
      use_ipv6=FALSE;
      arg++;
    }
    else if(!strcmp("--port", argv[arg])) {
      arg++;
      if(argc>arg) {
        port = (unsigned short)atoi(argv[arg]);
        arg++;
      }
    }
    else if(!strcmp("--connect", argv[arg])) {
      /* Asked to actively connect to the specified local port instead of
         doing a passive server-style listening. */
      arg++;
      if(argc>arg) {
        connectport = (unsigned short)atoi(argv[arg]);
        arg++;
      }
    }
    else {
      puts("Usage: sockfilt [option]\n"
           " --version\n"
           " --logfile [file]\n"
           " --pidfile [file]\n"
           " --ipv4\n"
           " --ipv6\n"
           " --port [port]");
      return 0;
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
    return 1;
  }

  if(connectport) {
    /* Active mode, we should connect to the given port number */
    mode = ACTIVE;
#ifdef ENABLE_IPV6
    if(!use_ipv6) {
#endif
      memset(&me, 0, sizeof(me));
      me.sin_family = AF_INET;
      me.sin_port = htons(connectport);
      me.sin_addr.s_addr = INADDR_ANY;
      Curl_inet_pton(AF_INET, "127.0.0.1", &me.sin_addr);

      rc = connect(sock, (struct sockaddr *) &me, sizeof(me));
#ifdef ENABLE_IPV6
    }
    else {
      memset(&me6, 0, sizeof(me6));
      me6.sin6_family = AF_INET6;
      me6.sin6_port = htons(connectport);
      Curl_inet_pton(AF_INET6, "::1", &me6.sin6_addr);

      rc = connect(sock, (struct sockaddr *) &me6, sizeof(me6));
    }
#endif /* ENABLE_IPV6 */
    if(rc) {
      perror("connecting stream socket");
      logmsg("Error connecting to port %d", port);
      return 1;
    }
    logmsg("====> Client connect");
    msgsock = sock; /* use this as stream */
  }
  else {
    /* passive daemon style */

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
      return 1;
    }

    if(!port) {
      /* The system picked a port number, now figure out which port we actually
         got */
      /* we succeeded to bind */
      struct sockaddr_in add;
      socklen_t socksize = sizeof(add);

      if(getsockname(sock, (struct sockaddr *) &add,
                     &socksize)<0) {
        fprintf(stderr, "getsockname() failed");
        return 1;
      }
      port = ntohs(add.sin_port);
    }

    /* start accepting connections */
    listen(sock, 1);

  }

  logmsg("Running IPv%d version",
         (use_ipv6?6:4));

  if(connectport)
    logmsg("Connected to port %d", connectport);
  else
    logmsg("Listening on port %d", port);

  pidfile = fopen(pidname, "w");
  if(pidfile) {
    int pid = (int)getpid();
    fprintf(pidfile, "%d\n", pid);
    fclose(pidfile);
    logmsg("Wrote pid %d to %s", pid, pidname);
  }
  else
    fprintf(stderr, "Couldn't write pid file\n");

  do {
    ok = juggle(&msgsock, sock, &mode);
  } while(ok);

  sclose(sock);

  return 0;
}