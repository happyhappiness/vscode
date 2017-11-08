int main(int argc, char *argv[])
{
  struct sockaddr_in me;
#ifdef ENABLE_IPV6
  struct sockaddr_in6 me6;
#endif /* ENABLE_IPV6 */
  curl_socket_t sock = CURL_SOCKET_BAD;
  curl_socket_t msgsock = CURL_SOCKET_BAD;
  int wrotepidfile = 0;
  char *pidname= (char *)".sockfilt.pid";
  int rc;
  int error;
  int arg=1;
  enum sockmode mode = PASSIVE_LISTEN; /* default */
  const char *addr = NULL;

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
    else if(!strcmp("--verbose", argv[arg])) {
      verbose = TRUE;
      arg++;
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
    else if(!strcmp("--addr", argv[arg])) {
      /* Set an IP address to use with --connect; otherwise use localhost */
      arg++;
      if(argc>arg) {
        addr = argv[arg];
        arg++;
      }
    }
    else {
      puts("Usage: sockfilt [option]\n"
           " --version\n"
           " --verbose\n"
           " --logfile [file]\n"
           " --pidfile [file]\n"
           " --ipv4\n"
           " --ipv6\n"
           " --port [port]\n"
           " --connect [port]\n"
           " --addr [address]");
      return 0;
    }
  }

#ifdef WIN32
  win32_init();
  atexit(win32_cleanup);
#endif

  install_signal_handlers();

#ifdef ENABLE_IPV6
  if(!use_ipv6)
#endif
    sock = socket(AF_INET, SOCK_STREAM, 0);
#ifdef ENABLE_IPV6
  else
    sock = socket(AF_INET6, SOCK_STREAM, 0);
#endif

  if(CURL_SOCKET_BAD == sock) {
    error = SOCKERRNO;
    logmsg("Error creating socket: (%d) %s",
           error, strerror(error));
    goto sockfilt_cleanup;
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
      if (!addr)
        addr = "127.0.0.1";
      Curl_inet_pton(AF_INET, addr, &me.sin_addr);

      rc = connect(sock, (struct sockaddr *) &me, sizeof(me));
#ifdef ENABLE_IPV6
    }
    else {
      memset(&me6, 0, sizeof(me6));
      me6.sin6_family = AF_INET6;
      me6.sin6_port = htons(connectport);
      if (!addr)
        addr = "::1";
      Curl_inet_pton(AF_INET6, addr, &me6.sin6_addr);

      rc = connect(sock, (struct sockaddr *) &me6, sizeof(me6));
    }
#endif /* ENABLE_IPV6 */
    if(rc) {
      error = SOCKERRNO;
      logmsg("Error connecting to port %d: (%d) %s",
             connectport, error, strerror(error));
      goto sockfilt_cleanup;
    }
    logmsg("====> Client connect");
    msgsock = sock; /* use this as stream */
  }
  else {
    /* passive daemon style */
    sock = sockdaemon(sock, &port);
    if(CURL_SOCKET_BAD == sock)
      goto sockfilt_cleanup;
    msgsock = CURL_SOCKET_BAD; /* no stream socket yet */
  }

  logmsg("Running IPv%d version",
         (use_ipv6?6:4));

  if(connectport)
    logmsg("Connected to port %d", connectport);
  else
    logmsg("Listening on port %d", port);

  wrotepidfile = write_pidfile(pidname);
  if(!wrotepidfile)
    goto sockfilt_cleanup;

  while(juggle(&msgsock, sock, &mode));

sockfilt_cleanup:

  if((msgsock != sock) && (msgsock != CURL_SOCKET_BAD))
    sclose(msgsock);

  if(sock != CURL_SOCKET_BAD)
    sclose(sock);

  if(wrotepidfile)
    unlink(pidname);

  restore_signal_handlers();

  if(got_exit_signal) {
    logmsg("============> sockfilt exits with signal (%d)", exit_signal);
    /*
     * To properly set the return status of the process we
     * must raise the same signal SIGINT or SIGTERM that we
     * caught and let the old handler take care of it.
     */
    raise(exit_signal);
  }

  logmsg("============> sockfilt quits");
  return 0;
}