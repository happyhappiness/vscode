static int init_fifo(GlobalInfo *g)
{
  struct stat st;
  curl_socket_t sockfd;

  fprintf(MSG_OUT, "Creating named pipe \"%s\"\n", fifo);
  if(lstat (fifo, &st) == 0) {
    if((st.st_mode & S_IFMT) == S_IFREG) {
      errno = EEXIST;
      perror("lstat");
      exit(1);
    }
  }
  unlink(fifo);
  if(mkfifo (fifo, 0600) == -1) {
    perror("mkfifo");
    exit(1);
  }
  sockfd = open(fifo, O_RDWR | O_NONBLOCK, 0);
  if(sockfd == -1) {
    perror("open");
    exit(1);
  }
  g->input = fdopen(sockfd, "r");

  fprintf(MSG_OUT, "Now, pipe some URL's into > %s\n", fifo);
  g->fifo_event = event_new(g->evbase, sockfd, EV_READ|EV_PERSIST, fifo_cb, g);
  event_add(g->fifo_event, NULL);
  return (0);
}