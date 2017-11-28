
    delete srv->wqueue;

#endif

    /* TODO: walk the local queue of requests and carry them all out */
    if (srv->wfd != srv->rfd && srv->wfd != -1)
        comm_close(srv->wfd);

    dlinkDelete(&srv->link, &hlp->servers);

    hlp->n_running--;

    assert(hlp->n_running >= 0);

    if (!srv->flags.shutdown) {
        hlp->n_active--;
        assert( hlp->n_active >= 0);
        debugs(84, 0, "WARNING: " << hlp->id_name << " #" << srv->index + 1 << " (FD " << fd << ") exited");

        if (hlp->n_active <= hlp->n_to_start / 2) {
            debugs(80, 0, "Too few " << hlp->id_name << " processes are running");

            if (hlp->last_restart > squid_curtime - 30)
                fatalf("The %s helpers are crashing too rapidly, need help!\n", hlp->id_name);

            debugs(80, 0, "Starting new helpers");

            helperStatefulOpenServers(hlp);
        }
    }

    if ((r = srv->request)) {
        void *cbdata;
