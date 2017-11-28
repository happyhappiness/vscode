void
helperStatefulOpenServers(statefulhelper * hlp)
{
    char *shortname;
    const char *args[HELPER_MAX_ARGS+1]; // save space for a NULL terminator
    char fd_note_buf[FD_DESC_SZ];
    int nargs = 0;

    if (hlp->cmdline == NULL)
        return;

    char *progname = hlp->cmdline->key;

    char *s;
    if ((s = strrchr(progname, '/')))
        shortname = xstrdup(s + 1);
    else
        shortname = xstrdup(progname);

    /* dont ever start more than hlp->n_to_start processes. */
    /* n_active are the helpers which have not been shut down. */
    int need_new = hlp->n_to_start - hlp->n_active;

    debugs(84, 1, "helperOpenServers: Starting " << need_new << "/" << hlp->n_to_start << " '" << shortname << "' processes");

    if (need_new < 1) {
        debugs(84, 1, "helperStatefulOpenServers: No '" << shortname << "' processes needed.");
    }

    char *procname = (char *)xmalloc(strlen(shortname) + 3);

    snprintf(procname, strlen(shortname) + 3, "(%s)", shortname);

    args[nargs++] = procname;

    for (wordlist *w = hlp->cmdline->next; w && nargs < HELPER_MAX_ARGS; w = w->next)
        args[nargs++] = w->key;

    args[nargs++] = NULL;

    assert(nargs <= HELPER_MAX_ARGS);

    for (int k = 0; k < need_new; k++) {
        getCurrentTime();
        int rfd = -1;
        int wfd = -1;
        void * hIpc;
        pid_t pid = ipcCreate(hlp->ipc_type,
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
        CBDATA_INIT_TYPE(helper_stateful_server);
        helper_stateful_server *srv = cbdataAlloc(helper_stateful_server);
        srv->hIpc = hIpc;
        srv->pid = pid;
        srv->flags.reserved = 0;
        srv->stats.submits = 0;
        srv->stats.releases = 0;
        srv->index = k;
        srv->addr = hlp->addr;
        srv->rfd = rfd;
        srv->wfd = wfd;
        srv->rbuf = (char *)memAllocBuf(ReadBufMinSize, &srv->rbuf_sz);
        srv->roffset = 0;
        srv->parent = cbdataReference(hlp);

        if (hlp->datapool != NULL)
            srv->data = hlp->datapool->alloc();

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

        comm_add_close_handler(rfd, helperStatefulServerFree, srv);

        comm_read(srv->rfd, srv->rbuf, srv->rbuf_sz - 1, helperStatefulHandleRead, srv);
    }

    hlp->last_restart = squid_curtime;
    safe_free(shortname);
    safe_free(procname);
    helperStatefulKickQueue(hlp);
}