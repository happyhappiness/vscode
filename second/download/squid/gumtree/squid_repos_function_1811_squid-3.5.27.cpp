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

    /* figure out how many new child are actually needed. */
    int need_new = hlp->childs.needNew();

    debugs(84, DBG_IMPORTANT, "helperOpenServers: Starting " << need_new << "/" << hlp->childs.n_max << " '" << shortname << "' processes");

    if (need_new < 1) {
        debugs(84, DBG_IMPORTANT, "helperOpenServers: No '" << shortname << "' processes needed.");
    }

    procname = (char *)xmalloc(strlen(shortname) + 3);

    snprintf(procname, strlen(shortname) + 3, "(%s)", shortname);

    args[nargs] = procname;
    ++nargs;

    for (w = hlp->cmdline->next; w && nargs < HELPER_MAX_ARGS; w = w->next) {
        args[nargs] = w->key;
        ++nargs;
    }

    args[nargs] = NULL;
    ++nargs;

    assert(nargs <= HELPER_MAX_ARGS);

    for (k = 0; k < need_new; ++k) {
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
            debugs(84, DBG_IMPORTANT, "WARNING: Cannot run '" << progname << "' process.");
            continue;
        }

        ++ hlp->childs.n_running;
        ++ hlp->childs.n_active;
        srv = new helper_server;
        srv->hIpc = hIpc;
        srv->pid = pid;
        srv->initStats();
        srv->addr = hlp->addr;
        srv->readPipe = new Comm::Connection;
        srv->readPipe->fd = rfd;
        srv->writePipe = new Comm::Connection;
        srv->writePipe->fd = wfd;
        srv->rbuf = (char *)memAllocBuf(ReadBufMinSize, &srv->rbuf_sz);
        srv->wqueue = new MemBuf;
        srv->roffset = 0;
        srv->requests = (Helper::Request **)xcalloc(hlp->childs.concurrency ? hlp->childs.concurrency : 1, sizeof(*srv->requests));
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

        AsyncCall::Pointer closeCall = asyncCall(5,4, "helperServerFree", cbdataDialer(helperServerFree, srv));
        comm_add_close_handler(rfd, closeCall);

        AsyncCall::Pointer call = commCbCall(5,4, "helperHandleRead",
                                             CommIoCbPtrFun(helperHandleRead, srv));
        comm_read(srv->readPipe, srv->rbuf, srv->rbuf_sz - 1, call);
    }

    hlp->last_restart = squid_curtime;
    safe_free(shortname);
    safe_free(procname);
    helperKickQueue(hlp);
}