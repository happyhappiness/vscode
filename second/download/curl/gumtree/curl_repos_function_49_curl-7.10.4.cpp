int main(int argc, char *argv[])
{
  struct sockaddr_in me;
  int sock, msgsock, flag;
  unsigned short port = DEFAULT_PORT;
  const char *logfile = DEFAULT_LOGFILE;
  int part_no;
  FILE *pidfile;
  
  if(argc>1)
    port = atoi(argv[1]);

  logfp = fopen(logfile, "a");
  if (!logfp) {
    perror(logfile);
    exit(1);
  }

#ifdef HAVE_SIGNAL
  signal(SIGPIPE, sigpipe_handler);
  siginterrupt(SIGPIPE, 1);
#endif

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("opening stream socket");
    fprintf(logfp, "Error opening socket -- aborting\n");
    fclose(logfp);
    exit(1);
  }

  flag = 1;
  if (setsockopt
      (sock, SOL_SOCKET, SO_REUSEADDR, (const void *) &flag,
       sizeof(int)) < 0) {
    perror("setsockopt(SO_REUSEADDR)");
  }

  me.sin_family = AF_INET;
  me.sin_addr.s_addr = INADDR_ANY;
  me.sin_port = htons(port);
  if (bind(sock, (struct sockaddr *) &me, sizeof me) < 0) {
    perror("binding stream socket");
    fprintf(logfp, "Error binding socket -- aborting\n");
    fclose(logfp);
    exit(1);
  }

  pidfile = fopen(".http.pid", "w");
  if(pidfile) {
    fprintf(pidfile, "%d\n", (int)getpid());
    fclose(pidfile);
  }
  else
    fprintf(stderr, "Couldn't write pid file\n");

  /* start accepting connections */
  listen(sock, 5);

  while (1) {
    int doc;

    msgsock = accept(sock, NULL, NULL);
    
    if (msgsock == -1)
      continue;
    
    logmsg("New client connected");

    do {

      doc = get_request(msgsock, &part_no);
      logmsg("Received request, now send response");
      send_doc(msgsock, doc, part_no);

      /* if we got a CONNECT, loop and get another request as well! */
    } while(doc == DOCNUMBER_CONNECT);

    logmsg("Closing client connection");
    close(msgsock);
  }
  
  close(sock);
  fclose(logfp);
  
  return 0;
}