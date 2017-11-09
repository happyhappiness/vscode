static int
inetsocketpair(int sv[2])
{
  int lfd;      /* Listening socket. */
  int sfd;      /* Server socket. */
  int cfd;      /* Client socket. */
  int len;
  struct sockaddr_in addr1;
  struct sockaddr_in addr2;

  /* Create listening socket on a local dynamic port. */
  lfd = socket(AF_INET, SOCK_STREAM, 0);
  if(lfd < 0)
    return -1;
  memset((char *) &addr1, 0, sizeof addr1);
  addr1.sin_family = AF_INET;
  addr1.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  addr1.sin_port = 0;
  if(bind(lfd, (struct sockaddr *) &addr1, sizeof addr1) ||
     listen(lfd, 2) < 0) {
    close(lfd);
    return -1;
  }

  /* Get the allocated port. */
  len = sizeof addr1;
  if(getsockname(lfd, (struct sockaddr *) &addr1, &len) < 0) {
    close(lfd);
    return -1;
  }

  /* Create the client socket. */
  cfd = socket(AF_INET, SOCK_STREAM, 0);
  if(cfd < 0) {
    close(lfd);
    return -1;
  }

  /* Request unblocking connection to the listening socket. */
  curlx_nonblock(cfd, TRUE);
  if(connect(cfd, (struct sockaddr *) &addr1, sizeof addr1) < 0 &&
     errno != EINPROGRESS) {
    close(lfd);
    close(cfd);
    return -1;
  }

  /* Get the client dynamic port for intrusion check below. */
  len = sizeof addr2;
  if(getsockname(cfd, (struct sockaddr *) &addr2, &len) < 0) {
    close(lfd);
    close(cfd);
    return -1;
  }

  /* Accept the incoming connection and get the server socket. */
  curlx_nonblock(lfd, TRUE);
  for(;;) {
    len = sizeof addr1;
    sfd = accept(lfd, (struct sockaddr *) &addr1, &len);
    if(sfd < 0) {
      close(lfd);
      close(cfd);
      return -1;
    }

    /* Check for possible intrusion from an external process. */
    if(addr1.sin_addr.s_addr == addr2.sin_addr.s_addr &&
       addr1.sin_port == addr2.sin_port)
      break;

    /* Intrusion: reject incoming connection. */
    close(sfd);
  }

  /* Done, return sockets and succeed. */
  close(lfd);
  curlx_nonblock(cfd, FALSE);
  sv[0] = cfd;
  sv[1] = sfd;
  return 0;
}