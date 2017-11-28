static void
netdbReloadState(void)
{
    if (strcmp(Config.netdbFilename, "none") == 0)
        return;

    char *s;
    int fd;
    int l;

    struct stat sb;
    netdbEntry *n;
    netdbEntry N;

    Ip::Address addr;
    int count = 0;

    struct timeval start = current_time;
    /*
     * This was nicer when we were using stdio, but thanks to
     * Solaris bugs, its a bad idea.  fopen can fail if more than
     * 256 FDs are open.
     */
    fd = file_open(Config.netdbFilename, O_RDONLY | O_BINARY);

    if (fd < 0)
        return;

    if (fstat(fd, &sb) < 0) {
        file_close(fd);
        return;
    }

    char *t;
    char *buf = (char *)xcalloc(1, sb.st_size + 1);
    t = buf;
    l = FD_READ_METHOD(fd, buf, sb.st_size);
    file_close(fd);

    if (l <= 0) {
        safe_free (buf);
        return;
    };

    while ((s = strchr(t, '\n'))) {
        char *q;
        assert(s - buf < l);
        *s = '\0';
        memset(&N, '\0', sizeof(netdbEntry));
        q = strtok(t, w_space);
        t = s + 1;

        if (NULL == q)
            continue;

        if (! (addr = q) )
            continue;

        if (netdbLookupAddr(addr) != NULL)  /* no dups! */
            continue;

        if ((q = strtok(NULL, w_space)) == NULL)
            continue;

        N.pings_sent = atoi(q);

        if ((q = strtok(NULL, w_space)) == NULL)
            continue;

        N.pings_recv = atoi(q);

        if (N.pings_recv == 0)
            continue;

        /* give this measurement low weight */
        N.pings_sent = 1;

        N.pings_recv = 1;

        if ((q = strtok(NULL, w_space)) == NULL)
            continue;

        N.hops = atof(q);

        if ((q = strtok(NULL, w_space)) == NULL)
            continue;

        N.rtt = atof(q);

        if ((q = strtok(NULL, w_space)) == NULL)
            continue;

        N.next_ping_time = (time_t) atoi(q);

        if ((q = strtok(NULL, w_space)) == NULL)
            continue;

        N.last_use_time = (time_t) atoi(q);

        n = new netdbEntry;

        memcpy(n, &N, sizeof(netdbEntry));

        netdbHashInsert(n, addr);

        while ((q = strtok(NULL, w_space)) != NULL) {
            if (netdbLookupHost(q) != NULL) /* no dups! */
                continue;

            netdbHostInsert(n, q);
        }

        ++count;
    }

    xfree(buf);
    getCurrentTime();
    debugs(38, DBG_IMPORTANT, "NETDB state reloaded; " <<
           count << " entries, " <<
           tvSubMsec(start, current_time) << " msec" );
}