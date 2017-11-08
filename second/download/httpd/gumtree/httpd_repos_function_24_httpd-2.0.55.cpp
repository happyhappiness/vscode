void write_request(struct connection *c)
{
  gettimeofday(&c->connect,0);
  write(c->fd,request, reqlen);  
  c->state = STATE_READ;
  FD_SET(c->fd, &readbits);
  FD_CLR(c->fd, &writebits);
}