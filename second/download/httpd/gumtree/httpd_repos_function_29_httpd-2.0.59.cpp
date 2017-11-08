void close_connection(struct connection *c)
{
  if(c->read == 0 && c->keepalive) {
    /* server has legitiamately shut down an idle keep alive request */
    good--;  /* connection never happend */
  } 
  else {
    if(good==1) {
      /* first time here */
      doclen = c->bread;
    } else if (c->bread!=doclen) { 
      bad++; 
      err_length++; 
    }
    
    /* save out time */
    if(done < requests) {
      struct data s;
      gettimeofday(&c->done,0);
      s.read = c->read;
      s.ctime = timedif(c->connect, c->start);
      s.time = timedif(c->done, c->start);
      stats[done++] = s;
    }
  }

  close(c->fd);
  FD_CLR(c->fd, &readbits);
  FD_CLR(c->fd, &writebits);

  /* connect again */
  start_connect(c); 
  return;
}