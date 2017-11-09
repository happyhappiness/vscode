int main(int argc, char *argv[])
{
  srvr_sockaddr_union_t me;
  curl_socket_t sock = CURL_SOCKET_BAD;
  int wrotepidfile = 0;
  int flag;
  unsigned short port = DEFAULT_PORT;
#ifdef USE_UNIX_SOCKETS
  const char *unix_socket = NULL;
  bool unlink_socket = false;
#endif
  const char *pidname = ".http.pid";
  struct httprequest req;
  int rc = 0;
  int error;
  int arg = 1;
  long pid;
  const char *connecthost = "127.0.0.1";
  const char *socket_type = "IPv4";
  char port_str[11];
  const char *location_str = port_str;

  /* a default CONNECT port is basically pointless but still ... */
  size_t socket_idx;

  memset(&req, 0, sizeof(req));

  while(argc>arg) {
    if(!strcmp("--version", argv[arg])) {
      puts("sws IPv4"
#ifdef ENABLE_IPV6
             "/IPv6"
#endif
#ifdef USE_UNIX_SOCKETS
             "/unix"
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
    else if(!strcmp("--gopher", argv[arg])) {
      arg++;
      use_gopher = TRUE;
      end_of_headers = "\r\n"; /* gopher style is much simpler */
    }
    else if(!strcmp("--ipv4", argv[arg])) {
      socket_type = "IPv4";
      socket_domain = AF_INET;
      location_str = port_str;
      arg++;
    }
    else if(!strcmp("--ipv6", argv[arg])) {
#ifdef ENABLE_IPV6
      socket_type = "IPv6";
      socket_domain = AF_INET6;
      location_str = port_str;
#endif
      arg++;
    }
    else if(!strcmp("--unix-socket", argv[arg])) {
      arg++;
      if(argc>arg) {
#ifdef USE_UNIX_SOCKETS
        unix_socket = argv[arg];
        if(strlen(unix_socket) >= sizeof(me.sau.sun_path)) {
          fprintf(stderr, "sws: socket path must be shorter than %zu chars\n",
                  sizeof(me.sau.sun_path));
          return 0;
        }
        socket_type = "unix";
        socket_domain = AF_UNIX;
        location_str = unix_socket;
#endif
        arg++;
      }
    }
    else if(!strcmp("--port", argv[arg])) {
      arg++;
      if(argc>arg) {
        char *endptr;
        unsigned long ulnum = strtoul(argv[arg], &endptr, 10);
        if((endptr != argv[arg] + strlen(argv[arg])) ||
           (ulnum < 1025UL) || (ulnum > 65535UL)) {
          fprintf(stderr, "sws: invalid --port argument (%s)\n",
                  argv[arg]);
          return 0;
        }
        port = curlx_ultous(ulnum);
        arg++;
      }
    }
    else if(!strcmp("--srcdir", argv[arg])) {
      arg++;
      if(argc>arg) {
        path = argv[arg];
        arg++;
      }
    }
    else if(!strcmp("--connect", argv[arg])) {
      /* The connect host IP number that the proxy will connect to no matter
         what the client asks for, but also use this as a hint that we run as
         a proxy and do a few different internal choices */
      arg++;
      if(argc>arg) {
        connecthost = argv[arg];
        arg++;
        is_proxy = TRUE;
        logmsg("Run as proxy, CONNECT to host %s", connecthost);
      }
    }
    else {
      puts("Usage: sws [option]\n"
           " --version\n"
           " --logfile [file]\n"
           " --pidfile [file]\n"
           " --ipv4\n"
           " --ipv6\n"
           " --unix-socket [file]\n"
           " --port [port]\n"
           " --srcdir [path]\n"
           " --connect [ip4-addr]\n"
           " --gopher");
      return 0;
    }
  }

  snprintf(port_str, sizeof(port_str), "port %hu", port);

#ifdef WIN32
  win32_init();
  atexit(win32_cleanup);
#endif

  install_signal_handlers();

  pid = (long)getpid();

  sock = socket(socket_domain, SOCK_STREAM, 0);

  all_sockets[0] = sock;
  num_sockets = 1;

  if(CURL_SOCKET_BAD == sock) {
    error = SOCKERRNO;
    logmsg("Error creating socket: (%d) %s",
           error, strerror(error));
    goto sws_cleanup;
  }

  flag = 1;
  if(0 != setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
                     (void *)&flag, sizeof(flag))) {
    error = SOCKERRNO;
    logmsg("setsockopt(SO_REUSEADDR) failed with error: (%d) %s",
           error, strerror(error));
    goto sws_cleanup;
  }
  if(0 != curlx_nonblock(sock, TRUE)) {
    error = SOCKERRNO;
    logmsg("curlx_nonblock failed with error: (%d) %s",
           error, strerror(error));
    goto sws_cleanup;
  }

  switch(socket_domain) {
  case AF_INET:
    memset(&me.sa4, 0, sizeof(me.sa4));
    me.sa4.sin_family = AF_INET;
    me.sa4.sin_addr.s_addr = INADDR_ANY;
    me.sa4.sin_port = htons(port);
    rc = bind(sock, &me.sa, sizeof(me.sa4));
    break;
#ifdef ENABLE_IPV6
  case AF_INET6:
    memset(&me.sa6, 0, sizeof(me.sa6));
    me.sa6.sin6_family = AF_INET6;
    me.sa6.sin6_addr = in6addr_any;
    me.sa6.sin6_port = htons(port);
    rc = bind(sock, &me.sa, sizeof(me.sa6));
    break;
#endif /* ENABLE_IPV6 */
#ifdef USE_UNIX_SOCKETS
  case AF_UNIX:
    memset(&me.sau, 0, sizeof(me.sau));
    me.sau.sun_family = AF_UNIX;
    strncpy(me.sau.sun_path, unix_socket, sizeof(me.sau.sun_path));
    rc = bind(sock, &me.sa, sizeof(me.sau));
    if(0 != rc && errno == EADDRINUSE) {
      struct stat statbuf;
      /* socket already exists. Perhaps it is stale? */
      int unixfd = socket(AF_UNIX, SOCK_STREAM, 0);
      if(CURL_SOCKET_BAD == unixfd) {
        error = SOCKERRNO;
        logmsg("Error binding socket, failed to create socket at %s: (%d) %s",
               unix_socket, error, strerror(error));
        goto sws_cleanup;
      }
      /* check whether the server is alive */
      rc = connect(unixfd, &me.sa, sizeof(me.sau));
      error = errno;
      close(unixfd);
      if(ECONNREFUSED != error) {
        logmsg("Error binding socket, failed to connect to %s: (%d) %s",
               unix_socket, error, strerror(error));
        goto sws_cleanup;
      }
      /* socket server is not alive, now check if it was actually a socket.
       * Systems which have Unix sockets will also have lstat */
      rc = lstat(unix_socket, &statbuf);
      if(0 != rc) {
        logmsg("Error binding socket, failed to stat %s: (%d) %s",
               unix_socket, errno, strerror(errno));
        goto sws_cleanup;
      }
      if((statbuf.st_mode & S_IFSOCK) != S_IFSOCK) {
        logmsg("Error binding socket, failed to stat %s: (%d) %s",
               unix_socket, error, strerror(error));
        goto sws_cleanup;
      }
      /* dead socket, cleanup and retry bind */
      rc = unlink(unix_socket);
      if(0 != rc) {
        logmsg("Error binding socket, failed to unlink %s: (%d) %s",
               unix_socket, errno, strerror(errno));
        goto sws_cleanup;
      }
      /* stale socket is gone, retry bind */
      rc = bind(sock, &me.sa, sizeof(me.sau));
    }
    break;
#endif /* USE_UNIX_SOCKETS */
  }
  if(0 != rc) {
    error = SOCKERRNO;
    logmsg("Error binding socket on %s: (%d) %s",
           location_str, error, strerror(error));
    goto sws_cleanup;
  }

  logmsg("Running %s %s version on %s",
         use_gopher?"GOPHER":"HTTP", socket_type, location_str);

  /* start accepting connections */
  rc = listen(sock, 5);
  if(0 != rc) {
    error = SOCKERRNO;
    logmsg("listen() failed with error: (%d) %s",
           error, strerror(error));
    goto sws_cleanup;
  }

#ifdef USE_UNIX_SOCKETS
  /* listen succeeds, so let's assume a valid listening Unix socket */
  unlink_socket = true;
#endif

  /*
  ** As soon as this server writes its pid file the test harness will
  ** attempt to connect to this server and initiate its verification.
  */

  wrotepidfile = write_pidfile(pidname);
  if(!wrotepidfile)
    goto sws_cleanup;

  /* initialization of httprequest struct is done before get_request(), but
     the pipelining struct field must be initialized previously to FALSE
     every time a new connection arrives. */

  req.pipelining = FALSE;
  init_httprequest(&req);

  for(;;) {
    fd_set input;
    fd_set output;
    struct timeval timeout = {0, 250000L}; /* 250 ms */
    curl_socket_t maxfd = (curl_socket_t)-1;

    /* Clear out closed sockets */
    for(socket_idx = num_sockets - 1; socket_idx >= 1; --socket_idx) {
      if(CURL_SOCKET_BAD == all_sockets[socket_idx]) {
        char *dst = (char *) (all_sockets + socket_idx);
        char *src = (char *) (all_sockets + socket_idx + 1);
        char *end = (char *) (all_sockets + num_sockets);
        memmove(dst, src, end - src);
        num_sockets -= 1;
      }
    }

    if(got_exit_signal)
      goto sws_cleanup;

    /* Set up for select */
    FD_ZERO(&input);
    FD_ZERO(&output);

    for(socket_idx = 0; socket_idx < num_sockets; ++socket_idx) {
      /* Listen on all sockets */
      FD_SET(all_sockets[socket_idx], &input);
      if(all_sockets[socket_idx] > maxfd)
        maxfd = all_sockets[socket_idx];
    }

    if(got_exit_signal)
      goto sws_cleanup;

    rc = select((int)maxfd + 1, &input, &output, NULL, &timeout);
    if(rc < 0) {
      error = SOCKERRNO;
      logmsg("select() failed with error: (%d) %s",
             error, strerror(error));
      goto sws_cleanup;
    }

    if(got_exit_signal)
      goto sws_cleanup;

    if(rc == 0) {
      /* Timed out - try again */
      continue;
    }

    /* Check if the listening socket is ready to accept */
    if(FD_ISSET(all_sockets[0], &input)) {
      /* Service all queued connections */
      curl_socket_t msgsock;
      do {
        msgsock = accept_connection(sock);
        logmsg("accept_connection %d returned %d", sock, msgsock);
        if(CURL_SOCKET_BAD == msgsock)
          goto sws_cleanup;
      } while(msgsock > 0);
    }

    /* Service all connections that are ready */
    for(socket_idx = 1; socket_idx < num_sockets; ++socket_idx) {
      if(FD_ISSET(all_sockets[socket_idx], &input)) {
        if(got_exit_signal)
          goto sws_cleanup;

        /* Service this connection until it has nothing available */
        do {
          rc = service_connection(all_sockets[socket_idx], &req, sock,
                                  connecthost);
          if(got_exit_signal)
            goto sws_cleanup;

          if(rc < 0) {
            logmsg("====> Client disconnect %d", req.connmon);

            if(req.connmon) {
              const char *keepopen = "[DISCONNECT]\n";
              storerequest(keepopen, strlen(keepopen));
            }

            if(!req.open)
              /* When instructed to close connection after server-reply we
                 wait a very small amount of time before doing so. If this
                 is not done client might get an ECONNRESET before reading
                 a single byte of server-reply. */
              wait_ms(50);

            if(all_sockets[socket_idx] != CURL_SOCKET_BAD) {
              sclose(all_sockets[socket_idx]);
              all_sockets[socket_idx] = CURL_SOCKET_BAD;
            }

            serverlogslocked -= 1;
            if(!serverlogslocked)
              clear_advisor_read_lock(SERVERLOGS_LOCK);

            if(req.testno == DOCNUMBER_QUIT)
              goto sws_cleanup;
          }

          /* Reset the request, unless we're still in the middle of reading */
          if(rc != 0)
            init_httprequest(&req);
        } while(rc > 0);
      }
    }

    if(got_exit_signal)
      goto sws_cleanup;
  }

sws_cleanup:

  for(socket_idx = 1; socket_idx < num_sockets; ++socket_idx)
    if((all_sockets[socket_idx] != sock) &&
     (all_sockets[socket_idx] != CURL_SOCKET_BAD))
      sclose(all_sockets[socket_idx]);

  if(sock != CURL_SOCKET_BAD)
    sclose(sock);

#ifdef USE_UNIX_SOCKETS
  if(unlink_socket && socket_domain == AF_UNIX) {
    rc = unlink(unix_socket);
    logmsg("unlink(%s) = %d (%s)", unix_socket, rc, strerror(rc));
  }
#endif

  if(got_exit_signal)
    logmsg("signalled to die");

  if(wrotepidfile)
    unlink(pidname);

  if(serverlogslocked) {
    serverlogslocked = 0;
    clear_advisor_read_lock(SERVERLOGS_LOCK);
  }

  restore_signal_handlers();

  if(got_exit_signal) {
    logmsg("========> %s sws (%s pid: %ld) exits with signal (%d)",
           socket_type, location_str, pid, exit_signal);
    /*
     * To properly set the return status of the process we
     * must raise the same signal SIGINT or SIGTERM that we
     * caught and let the old handler take care of it.
     */
    raise(exit_signal);
  }

  logmsg("========> sws quits");
  return 0;
}