void
helperOpenServers(helper * hlp)
{
    char *s;
    char *progname;
    char *shortname;
    char *procname;
    const char *args[HELPER_MAX_ARGS+1]; // save space for a NULL terminator
    char fd_note_buf[FD_DESC_SZ];
    helper_server *srv;
    int nargs = 0;
    int k;
    pid_t pid;
    int rfd;
    int wfd;
    void * hIpc;
    wordlist *w;

    if (hlp->cmdline == NULL)
        return;

    progname = hlp->cmdline->key;

    if ((s = strrchr(progname, '/')))
        shortname = xstrdup(s + 1);
    else
        shortname = xstrdup(progname);

    /* dont ever start more than hlp->n_to_start processes. */
    int need_new = hlp->n_to_start - hlp->n_active;

    debugs(84, 1, "helperOpenServers: Starting " << need_new << "/" << hlp->n_to_start << " '" << shortname << "' processes");

    if (need_new < 1) {
        debugs(84, 1, "helperOpenServers: No '" << shortname << "' processes needed.");
    }

    procname = (char *)xmalloc(strlen(shortname) + 3);

    snprintf(procname, strlen(shortname) + 3, "(%s)", shortname);

    args[nargs++] = procname;

    for (w = hlp->cmdline->next; w && nargs < HELPER_MAX_ARGS; w = w->next)
        args[nargs++] = w->key;

    args[nargs++] = NULL;

    assert(nargs <= HELPER_MAX_ARGS);

    for (k = 0; k < need_new; k++) {
        getCurrentTime();
        rfd = wfd = -1;
        pid = ipcCreate(hlp->ipc_type,
                        progname,
                        args,
                        shortname,
                        hlp->addr,
                        &rfd,
                        &wfd,
                        &hIpc);

        if (pid < 0) {
            debugs(84, 1, "WARNING: Cannot run '" << progname << "' process.");
            continue;
        }

        hlp->n_running++;
        hlp->n_active++;
        CBDATA_INIT_TYPE(helper_server);
        srv = cbdataAlloc(helper_server);
        srv->hIpc = hIpc;
        srv->pid = pid;
        srv->index = k;
        srv->addr = hlp->addr;
        srv->rfd = rfd;
        srv->wfd = wfd;
        srv->rbuf = (char *)memAllocBuf(ReadBufMinSize, &srv->rbuf_sz);
        srv->wqueue = new MemBuf;
        srv->roffset = 0;
        srv->requests = (helper_request **)xcalloc(hlp->concurrency ? hlp->concurrency : 1, sizeof(*srv->requests));
        srv->parent = cbdataReference(hlp);
        dlinkAddTail(srv, &srv->link, &hlp->servers);

        if (rfd == wfd) {
            snprintf(fd_note_buf, FD_DESC_SZ, "%s #%d", shortname, k + 1);
            fd_note(rfd, fd_note_buf);
        } else {
            snprintf(fd_note_buf, FD_DESC_SZ, "reading %s #%d", shortname, k + 1);
            fd_note(rfd, fd_note_buf);
            snprintf(fd_note_buf, FD_DESC_SZ, "writing %s #%d", shortname, k + 1);
            fd_note(wfd, fd_note_buf);
        }

        commSetNonBlocking(rfd);

        if (wfd != rfd)
            commSetNonBlocking(wfd);

        comm_add_close_handler(rfd, helperServerFree, srv);

        comm_read(srv->rfd, srv->rbuf, srv->rbuf_sz - 1, helperHandleRead, srv);
    }

    hlp->last_restart = squid_curtime;
    safe_free(shortname);
    safe_free(procname);
    helperKickQueue(hlp);
}