static void
helperServerFree(int fd, void *data)
{
    helper_server *srv = (helper_server *)data;
    helper *hlp = srv->parent;
    helper_request *r;
    int i, concurrency = hlp->concurrency;

    if (!concurrency)
        concurrency = 1;

    if (srv->rbuf) {
        memFreeBuf(srv->rbuf_sz, srv->rbuf);
        srv->rbuf = NULL;
    }

    srv->wqueue->clean();
    delete srv->wqueue;

    if (srv->writebuf) {
        srv->writebuf->clean();
        delete srv->writebuf;
        srv->writebuf = NULL;
    }

    if (srv->wfd != srv->rfd && srv->wfd != -1)
        comm_close(srv->wfd);

    dlinkDelete(&srv->link, &hlp->servers);

    hlp->n_running--;

    assert(hlp->n_running >= 0);

    if (!srv->flags.shutdown) {
        hlp->n_active--;
        assert(hlp->n_active >= 0);
        debugs(84, 0, "WARNING: " << hlp->id_name << " #" << srv->index + 1 <<
               " (FD " << fd << ") exited");

        if (hlp->n_active < hlp->n_to_start / 2) {
            debugs(80, 0, "Too few " << hlp->id_name << " processes are running");

            if (hlp->last_restart > squid_curtime - 30)
                fatalf("The %s helpers are crashing too rapidly, need help!\n", hlp->id_name);

            debugs(80, 0, "Starting new helpers");

            helperOpenServers(hlp);
        }
    }

    for (i = 0; i < concurrency; i++) {
        if ((r = srv->requests[i])) {
            void *cbdata;

            if (cbdataReferenceValidDone(r->data, &cbdata))
                r->callback(cbdata, NULL);

            helperRequestFree(r);

            srv->requests[i] = NULL;
        }
    }
    safe_free(srv->requests);

    cbdataReferenceDone(srv->parent);
    cbdataFree(srv);
}