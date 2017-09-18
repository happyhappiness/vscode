/* --------------------------------------------------------- */

/* simple little function to perror and exit */

static void err(char *s)
{
    perror(s);
    exit(errno);
}

/* --------------------------------------------------------- */

/* write out request to a connection - assumes we can write 
   (small) request out in one go into our new socket buffer  */

static void write_request(struct connection *c)
{
    gettimeofday(&c->connect, 0);
    write(c->fd, request, reqlen);
    c->state = STATE_READ;
    FD_SET(c->fd, &readbits);
    FD_CLR(c->fd, &writebits);
}

/* --------------------------------------------------------- */
