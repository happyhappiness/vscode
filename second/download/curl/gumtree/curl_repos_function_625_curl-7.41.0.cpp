int main(int argc, char **argv)
{
  srvr_sockaddr_union_t me;
  struct tftphdr *tp;
  ssize_t n = 0;
  int arg = 1;
  unsigned short port = DEFAULT_PORT;
  curl_socket_t sock = CURL_SOCKET_BAD;
  int flag;
  int rc;
  int error;
  long pid;
  struct testcase test;
  int result = 0;

  memset(&test, 0, sizeof(test));

  while(argc>arg) {
    if(!strcmp("--version", argv[arg])) {
      printf("tftpd IPv4%s\n",
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
    else if(!strcmp("--ipv4", argv[arg])) {
#ifdef ENABLE_IPV6
      ipv_inuse = "IPv4";
      use_ipv6 = FALSE;
#endif
      arg++;
    }
    else if(!strcmp("--ipv6", argv[arg])) {
#ifdef ENABLE_IPV6
      ipv_inuse = "IPv6";
      use_ipv6 = TRUE;
#endif
      arg++;
    }
    else if(!strcmp("--port", argv[arg])) {
      arg++;
      if(argc>arg) {
        char *endptr;
        unsigned long ulnum = strtoul(argv[arg], &endptr, 10);
        if((endptr != argv[arg] + strlen(argv[arg])) ||
           (ulnum < 1025UL) || (ulnum > 65535UL)) {
          fprintf(stderr, "tftpd: invalid --port argument (%s)\n",
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
    else {
      puts("Usage: tftpd [option]\n"
           " --version\n"
           " --logfile [file]\n"
           " --pidfile [file]\n"
           " --ipv4\n"
           " --ipv6\n"
           " --port [port]\n"
           " --srcdir [path]");
      return 0;
    }
  }

#ifdef WIN32
  win32_init();
  atexit(win32_cleanup);
#endif

  install_signal_handlers();

  pid = (long)getpid();

#ifdef ENABLE_IPV6
  if(!use_ipv6)
#endif
    sock = socket(AF_INET, SOCK_DGRAM, 0);
#ifdef ENABLE_IPV6
  else
    sock = socket(AF_INET6, SOCK_DGRAM, 0);
#endif

  if(CURL_SOCKET_BAD == sock) {
    error = SOCKERRNO;
    logmsg("Error creating socket: (%d) %s",
           error, strerror(error));
    result = 1;
    goto tftpd_cleanup;
  }

  flag = 1;
  if (0 != setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
            (void *)&flag, sizeof(flag))) {
    error = SOCKERRNO;
    logmsg("setsockopt(SO_REUSEADDR) failed with error: (%d) %s",
           error, strerror(error));
    result = 1;
    goto tftpd_cleanup;
  }

#ifdef ENABLE_IPV6
  if(!use_ipv6) {
#endif
    memset(&me.sa4, 0, sizeof(me.sa4));
    me.sa4.sin_family = AF_INET;
    me.sa4.sin_addr.s_addr = INADDR_ANY;
    me.sa4.sin_port = htons(port);
    rc = bind(sock, &me.sa, sizeof(me.sa4));
#ifdef ENABLE_IPV6
  }
  else {
    memset(&me.sa6, 0, sizeof(me.sa6));
    me.sa6.sin6_family = AF_INET6;
    me.sa6.sin6_addr = in6addr_any;
    me.sa6.sin6_port = htons(port);
    rc = bind(sock, &me.sa, sizeof(me.sa6));
  }
#endif /* ENABLE_IPV6 */
  if(0 != rc) {
    error = SOCKERRNO;
    logmsg("Error binding socket on port %hu: (%d) %s",
           port, error, strerror(error));
    result = 1;
    goto tftpd_cleanup;
  }

  wrotepidfile = write_pidfile(pidname);
  if(!wrotepidfile) {
    result = 1;
    goto tftpd_cleanup;
  }

  logmsg("Running %s version on port UDP/%d", ipv_inuse, (int)port);

  for (;;) {
    fromlen = sizeof(from);
#ifdef ENABLE_IPV6
    if(!use_ipv6)
#endif
      fromlen = sizeof(from.sa4);
#ifdef ENABLE_IPV6
    else
      fromlen = sizeof(from.sa6);
#endif
    n = (ssize_t)recvfrom(sock, &buf.storage[0], sizeof(buf.storage), 0,
                          &from.sa, &fromlen);
    if(got_exit_signal)
      break;
    if (n < 0) {
      logmsg("recvfrom");
      result = 3;
      break;
    }

    set_advisor_read_lock(SERVERLOGS_LOCK);
    serverlogslocked = 1;

#ifdef ENABLE_IPV6
    if(!use_ipv6) {
#endif
      from.sa4.sin_family = AF_INET;
      peer = socket(AF_INET, SOCK_DGRAM, 0);
      if(CURL_SOCKET_BAD == peer) {
        logmsg("socket");
        result = 2;
        break;
      }
      if(connect(peer, &from.sa, sizeof(from.sa4)) < 0) {
        logmsg("connect: fail");
        result = 1;
        break;
      }
#ifdef ENABLE_IPV6
    }
    else {
      from.sa6.sin6_family = AF_INET6;
      peer = socket(AF_INET6, SOCK_DGRAM, 0);
      if(CURL_SOCKET_BAD == peer) {
        logmsg("socket");
        result = 2;
        break;
      }
      if(connect(peer, &from.sa, sizeof(from.sa6)) < 0) {
        logmsg("connect: fail");
        result = 1;
        break;
      }
    }
#endif

    maxtimeout = 5*TIMEOUT;

    tp = &buf.hdr;
    tp->th_opcode = ntohs(tp->th_opcode);
    if (tp->th_opcode == opcode_RRQ || tp->th_opcode == opcode_WRQ) {
      memset(&test, 0, sizeof(test));
      if (do_tftp(&test, tp, n) < 0)
        break;
      if(test.buffer)
        free(test.buffer);
    }
    sclose(peer);
    peer = CURL_SOCKET_BAD;

    if(test.ofile > 0) {
      close(test.ofile);
      test.ofile = 0;
    }

    if(got_exit_signal)
      break;

    if(serverlogslocked) {
      serverlogslocked = 0;
      clear_advisor_read_lock(SERVERLOGS_LOCK);
    }

    logmsg("end of one transfer");

  }

tftpd_cleanup:

  if(test.ofile > 0)
    close(test.ofile);

  if((peer != sock) && (peer != CURL_SOCKET_BAD))
    sclose(peer);

  if(sock != CURL_SOCKET_BAD)
    sclose(sock);

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
    logmsg("========> %s tftpd (port: %d pid: %ld) exits with signal (%d)",
           ipv_inuse, (int)port, pid, exit_signal);
    /*
     * To properly set the return status of the process we
     * must raise the same signal SIGINT or SIGTERM that we
     * caught and let the old handler take care of it.
     */
    raise(exit_signal);
  }

  logmsg("========> tftpd quits");
  return result;
}