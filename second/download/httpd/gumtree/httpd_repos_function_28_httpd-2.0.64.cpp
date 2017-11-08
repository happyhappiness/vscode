void start_connect(struct connection *c)
{
  c->read = 0;
  c->bread = 0;
  c->keepalive = 0;
  c->cbx = 0; 
  c->gotheader = 0;

  c->fd = socket(AF_INET, SOCK_STREAM, 0);
  if(c->fd<0) err("socket");

  nonblock(c->fd);
  gettimeofday(&c->start,0);

  if(connect(c->fd, (struct sockaddr *) &server, sizeof(server))<0) {
    if(errno==EINPROGRESS) {
      c->state = STATE_CONNECTING;
      FD_SET(c->fd, &writebits);
      return;
    }
    else {
      close(c->fd);
      err_conn++;
      if(bad++>10) {
	printf("\nTest aborted after 10 failures\n\n");
	exit(1);
      } 
      start_connect(c);
    }      
  }
  
  /* connected first time */
  write_request(c);
}