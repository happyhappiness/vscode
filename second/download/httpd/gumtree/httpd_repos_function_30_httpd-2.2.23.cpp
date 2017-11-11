void read_connection(struct connection *c)
{
  int r;

  r=read(c->fd,buffer,sizeof(buffer));
  if(r==0 || (r<0 && errno!=EAGAIN)) {
    good++;
    close_connection(c);
    return;
  }

  if(r<0 && errno==EAGAIN) return;

  c->read += r;
  totalread += r;

  if(!c->gotheader) {
    char *s;
    int l=4;
    int space = CBUFFSIZE - c->cbx - 1; /* -1 to allow for 0 terminator */
    int tocopy = (space<r)?space:r;
    memcpy(c->cbuff+c->cbx, buffer, space);
    c->cbx += tocopy; space -= tocopy;
    c->cbuff[c->cbx] = 0; /* terminate for benefit of strstr */
    s = strstr(c->cbuff, "\r\n\r\n");
    /* this next line is so that we talk to NCSA 1.5 which blatantly breaks
       the http specifaction */
    if(!s) { s = strstr(c->cbuff,"\n\n"); l=2; }

    if(!s) {
       /* read rest next time */
      if(space)
        return;
      else {
        /* header is in invalid or too big - close connection */
        close(c->fd);
        if(bad++>10) {
          printf("\nTest aborted after 10 failures\n\n");
          exit(1);
        }
        FD_CLR(c->fd, &writebits);
        start_connect(c);
      }
    }
    else {
      /* have full header */
      if(!good) {
        /* this is first time, extract some interesting info */
        char *p, *q;
        p = strstr(c->cbuff, "Server:");
        q = server_name;
        if(p) { p+=8; while(*p>32) *q++ = *p++; }
        *q = 0;
      }

      c->gotheader = 1;
      *s = 0; /* terminate at end of header */
      if(keepalive &&
         (strstr(c->cbuff, "Keep-Alive")
          || strstr(c->cbuff, "keep-alive")))  /* for benefit of MSIIS */
        {
        char *cl;
        cl = strstr(c->cbuff, "Content-Length:");
        /* for cacky servers like NCSA which break the spec and send a
           lower case 'l' */
        if(!cl) cl = strstr(c->cbuff, "Content-length:");
        if(cl) {
          c->keepalive=1;
          c->length = atoi(cl+16);
        }
      }
      c->bread += c->cbx - (s+l-c->cbuff) + r-tocopy;
      totalbread += c->bread;
    }
  }
  else {
    /* outside header, everything we have read is entity body */
    c->bread += r;
    totalbread += r;
  }

  if(c->keepalive && (c->bread >= c->length)) {
    /* finished a keep-alive connection */
    good++; doneka++;
    /* save out time */
    if(good==1) {
      /* first time here */
      doclen = c->bread;
    } else if(c->bread!=doclen) { bad++; err_length++; }
    if(done < requests) {
      struct data s;
      gettimeofday(&c->done,0);
      s.read = c->read;
      s.ctime = timedif(c->connect, c->start);
      s.time = timedif(c->done, c->start);
      stats[done++] = s;
    }
    c->keepalive = 0; c->length = 0; c->gotheader=0; c->cbx = 0;
    c->read = c->bread = 0;
    write_request(c);
    c->start = c->connect; /* zero connect time with keep-alive */
  }
}