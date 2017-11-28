static void
helperStatefulServerFree(helper_stateful_server *srv)
{
    statefulhelper *hlp = srv->parent;

    if (srv->rbuf) {
        memFreeBuf(srv->rbuf_sz, srv->rbuf);
        srv->rbuf = NULL;
    }

#if 0
    srv->wqueue->clean();

    delete srv->wqueue;

#endif

    /* TODO: walk the local queue of requests and carry them all out */
    if (Comm::IsConnOpen(srv->writePipe))
        srv->closeWritePipeSafely(hlp->id_name);

    dlinkDelete(&srv->link, &hlp->servers);

    assert(hlp->childs.n_running > 0);
    -- hlp->childs.n_running;

    if (!srv->flags.shutdown) {
        assert( hlp->childs.n_active > 0);
        -- hlp->childs.n_active;
        debugs(84, DBG_CRITICAL, "WARNING: " << hlp->id_name << " #" << srv->index << " exited");

        if (hlp->childs.needNew() > 0) {
            debugs(80, DBG_IMPORTANT, "Too few " << hlp->id_name << " processes are running (need " << hlp->childs.needNew() << "/" << hlp->childs.n_max << ")");

            if (hlp->childs.n_active < hlp->childs.n_startup && hlp->last_restart > squid_curtime - 30) {
                if (srv->stats.replies < 1)
                    fatalf("The %s helpers are crashing too rapidly, need help!\n", hlp->id_name);
                else
                    debugs(80, DBG_CRITICAL, "ERROR: The " << hlp->id_name << " helpers are crashing too rapidly, need help!");
            }

            debugs(80, DBG_IMPORTANT, "Starting new helpers");
            helperStatefulOpenServers(hlp);
        }
    }

    while (!srv->requests.empty()) {
        // XXX: re-schedule these on another helper?
        Helper::Xaction *r = srv->requests.front();
        srv->requests.pop_front();
        void *cbdata;

        if (cbdataReferenceValidDone(r->request.data, &cbdata)) {
            r->reply.result = Helper::Unknown;
            r->request.callback(cbdata, r->reply);
        }

        delete r;
    }

    if (srv->data != NULL)
        hlp->datapool->freeOne(srv->data);

    cbdataReferenceDone(srv->parent);

    delete srv;
}