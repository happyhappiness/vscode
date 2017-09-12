    }
}

/* Read a length from the buffer pointed to by *p, store the length in *len,
 * and return the number of bytes that the cursor advanced. */
static int readLen(char *p, int *len) {
    char *tail = strstr(p,"\r\n");
    if (tail == NULL)
        return 0;
    *tail = '\0';
    *len = atoi(p+1);
    return tail+2-p;
}

static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask)
{
    char buf[1024], *p;
    int nread, pos=0, len=0;
    client c = privdata;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(fd);
    REDIS_NOTUSED(mask);

    nread = read(c->fd,buf,sizeof(buf));
    if (nread == -1) {
        fprintf(stderr, "Reading from socket: %s\n", strerror(errno));
        freeClient(c);
