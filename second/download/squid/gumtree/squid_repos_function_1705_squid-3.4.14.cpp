void
helperStatefulOpenServers(statefulhelper * hlp)
{
    char *shortname;
    const char *args[HELPER_MAX_ARGS+1]; // save space for a NULL terminator
    char fd_note_buf[FD_DESC_SZ];
    int nargs = 0;

    if (hlp->cmdline == NULL)
        return;

    if (hlp->childs.concurrency)
        debugs(84, DBG_CRITICAL, "ERROR: concurrency= is not yet supported for stateful helpers ('" << hlp->cmdline << "')");

    char *progname = hlp->cmdline->key;

    char *s;
    if ((s = strrchr(progname, '/')))
        shortname = xstrdup(s + 1);
    else
        shortname = xstrdup(progname);

    /* figure out haw mant new helpers are needed. */
    int need_new = hlp->childs.needNew();

    debugs(84, DBG_IMPORTANT, "helperOpenServers: Starting " << need_new << "/" << hlp->childs.n_max << " '" << shortname << "' processes");

    if (need_new < 1) {
        debugs(84, DBG_IMPORTANT, "helperStatefulOpenServers: No '" << shortname << "' processes needed.");
    }

    char *procname = (char *)xmalloc(strlen(shortname) + 3);

    snprintf(procname, strlen(shortname) + 3, "(%s)", shortname);

    args[nargs] = procname;
    ++nargs;

    for (wordlist *w = hlp->cmdline->next; w && nargs < HELPER_MAX_ARGS; w = w->next) {
        args[nargs] = w->key;
        ++nargs;
    }

    args[nargs] = NULL;
    ++nargs;

    assert(nargs <= HELPER_MAX_ARGS);

    for (int k = 0; k < need_new; ++k) {
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
            debugs(84, DBG_IMPORTANT, "WARNING: Cannot run '" << progname << "' process.");
            continue;
        }

        ++ hlp->childs.n_running;
        ++ hlp->childs.n_active;
        CBDATA_INIT_TYPE(helper_stateful_server);
        helper_stateful_server *srv = cbdataAlloc(helper_stateful_server);
        srv->hIpc = hIpc;
        srv->pid = pid;
        srv->flags.reserved = false;
        srv->initStats();
        srv->addr = hlp->addr;
        srv->readPipe = new Comm::Connection;
        srv->readPipe->fd = rfd;
        srv->writePipe = new Comm::Connection;
        srv->writePipe->fd = wfd;
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

        AsyncCall::Pointer closeCall = asyncCall(5,4, "helperStatefulServerFree", cbdataDialer(helperStatefulServerFree, srv));
        comm_add_close_handler(rfd, closeCall);

        AsyncCall::Pointer call = commCbCall(5,4, "helperStatefulHandleRead",
                                             CommIoCbPtrFun(helperStatefulHandleRead, srv));
        comm_read(srv->readPipe, srv->rbuf, srv->rbuf_sz - 1, call);
    }

    hlp->last_restart = squid_curtime;
    safe_free(shortname);
    safe_free(procname);
    helperStatefulKickQueue(hlp);
}