int test()
{
  struct timeval timeout, now;
  fd_set sel_read, sel_except, sel_write;
  int i;

  {
    /* get server information */
    struct hostent *he;
    he = gethostbyname(machine);
    if (!he) err("gethostbyname");
    server.sin_family      = he->h_addrtype;
    server.sin_port        = htons(port);
    server.sin_addr.s_addr = ((unsigned long *)(he->h_addr_list[0]))[0];
  }

  con = malloc(concurrency*sizeof(struct connection));
  memset(con,0,concurrency*sizeof(struct connection));

  stats = malloc(requests * sizeof(struct data));

  FD_ZERO(&readbits);
  FD_ZERO(&writebits);

  /* setup request */
  sprintf(request,"GET %s HTTP/1.0\r\nUser-Agent: ZeusBench/1.0\r\n"
          "%sHost: %s\r\nAccept: */*\r\n\r\n", file,
          keepalive?"Connection: Keep-Alive\r\n":"", machine );

  reqlen = strlen(request);

  /* ok - lets start */
  gettimeofday(&start,0);

  /* initialise lots of requests */
  for(i=0; i<concurrency; i++) start_connect(&con[i]);

  while(done<requests) {
    int n;
    /* setup bit arrays */
    memcpy(&sel_except, &readbits, sizeof(readbits));
    memcpy(&sel_read, &readbits, sizeof(readbits));
    memcpy(&sel_write, &writebits, sizeof(readbits));

    /* check for time limit expiry */
    gettimeofday(&now,0);
    if(tlimit && timedif(now,start) > (tlimit*1000)) {
      requests=done;   /* so stats are correct */
      output_results();
    }

    /* Timeout of 30 seconds. */
    timeout.tv_sec=30; timeout.tv_usec=0;
    n=select(256, &sel_read, &sel_write, &sel_except, &timeout);
    if(!n) {
      printf("\nServer timed out\n\n");
      exit(1);
    }
    if(n<1) err("select");

    for(i=0; i<concurrency; i++) {
      int s = con[i].fd;
      if(FD_ISSET(s, &sel_except)) {
        bad++;
        err_except++;
        start_connect(&con[i]);
        continue;
      }
      if(FD_ISSET(s, &sel_read)) read_connection(&con[i]);
      if(FD_ISSET(s, &sel_write)) write_request(&con[i]);
    }
    if(done>=requests) output_results();
  }
  return 0;
}