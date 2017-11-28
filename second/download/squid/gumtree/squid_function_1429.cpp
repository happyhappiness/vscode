static void
helperDispatch(helper_server * srv, Helper::Request * r)
{
    helper *hlp = srv->parent;
    Helper::Request **ptr = NULL;
    unsigned int slot;

    if (!cbdataReferenceValid(r->data)) {
        debugs(84, DBG_IMPORTANT, "helperDispatch: invalid callback data");
        delete r;
        return;
    }

    for (slot = 0; slot < (hlp->childs.concurrency ? hlp->childs.concurrency : 1); ++slot) {
        if (!srv->requests[slot]) {
            ptr = &srv->requests[slot];
            break;
        }
    }

    assert(ptr);
    *ptr = r;
    r->dispatch_time = current_time;

    if (srv->wqueue->isNull())
        srv->wqueue->init();

    if (hlp->childs.concurrency)
        srv->wqueue->Printf("%d %s", slot, r->buf);
    else
        srv->wqueue->append(r->buf, strlen(r->buf));

    if (!srv->flags.writing) {
        assert(NULL == srv->writebuf);
        srv->writebuf = srv->wqueue;
        srv->wqueue = new MemBuf;
        srv->flags.writing = true;
        AsyncCall::Pointer call = commCbCall(5,5, "helperDispatchWriteDone",
                                             CommIoCbPtrFun(helperDispatchWriteDone, srv));
        Comm::Write(srv->writePipe, srv->writebuf->content(), srv->writebuf->contentSize(), call, NULL);
    }

    debugs(84, 5, "helperDispatch: Request sent to " << hlp->id_name << " #" << srv->index << ", " << strlen(r->buf) << " bytes");

    ++ srv->stats.uses;
    ++ srv->stats.pending;
    ++ hlp->stats.requests;
}