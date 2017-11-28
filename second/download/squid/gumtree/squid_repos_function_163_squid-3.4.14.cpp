void
read_url(int fd, void *junk)
{
    struct _request *r;
    static char buf[8192];
    char *t;
    buf[0] = '\0';
    if (fgets(buf, 8191, stdin) == NULL) {
        printf("Done Reading URLS\n");
        fd_close(0);
        nfds++;
        return;
    }
    if (buf[0] == '\0')
        return;
    if ((t = strchr(buf, '\n')))
        *t = '\0';
    r = request(buf);
    if (!r) {
        max_connections = nfds - 1;
        printf("NOTE: max_connections set at %d\n", max_connections);
    } else {
        fd_open(r->fd, read_reply, r, reply_done);
    }
}