int main(int argc, char **argv)
{
  struct sockaddr_in me;
#ifdef ENABLE_IPV6
  struct sockaddr_in6 me6;
#endif /* ENABLE_IPV6 */

  struct tftphdr *tp;
  int n = 0;
  int arg = 1;
  FILE *pidfile;
  char *pidname= (char *)".tftpd.pid";
  unsigned short port = DEFAULT_PORT;
  curl_socket_t sock;
  int flag;
  int rc;
  struct testcase test;

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
#endif

#ifdef ENABLE_IPV6
  if(!use_ipv6)
#endif
    sock = socket(AF_INET, SOCK_DGRAM, 0);
#ifdef ENABLE_IPV6
  else
    sock = socket(AF_INET6, SOCK_DGRAM, 0);
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

  logmsg("Running IPv%d version on port UDP/%d",
#ifdef ENABLE_IPV6
         (use_ipv6?6:4)
#else
         4
#endif
         , port );

  do {
    FILE *server;

    fromlen = sizeof(from);
    n = recvfrom(sock, buf, sizeof (buf), 0,
                 (struct sockaddr *)&from, &fromlen);
    if (n < 0) {
      logmsg("recvfrom:\n");
      return 3;
    }

    from.sin_family = AF_INET;

    peer = socket(AF_INET, SOCK_DGRAM, 0);
    if (peer < 0) {
      logmsg("socket:\n");
      return 2;
    }

    if (connect(peer, (struct sockaddr *)&from, sizeof(from)) < 0) {
      logmsg("connect: fail\n");
      return 1;
    }
    maxtimeout = 5*TIMEOUT;

    tp = (struct tftphdr *)buf;
    tp->th_opcode = ntohs(tp->th_opcode);
    if (tp->th_opcode == RRQ || tp->th_opcode == WRQ) {
      memset(&test, 0, sizeof(test));
      server = fopen(REQUEST_DUMP, "ab");
      if(!server)
        break;
      test.server = server;
      tftp(&test, tp, n);
      if(test.buffer)
        free(test.buffer);
    }
    fclose(server);
    sclose(peer);
  } while(1);
  return 0;
}