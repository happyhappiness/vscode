static void
helperDispatch(helper_server * srv, Helper::Xaction * r)
{
    helper *hlp = srv->parent;
    const uint64_t reqId = ++srv->nextRequestId;

    if (!cbdataReferenceValid(r->request.data)) {
        debugs(84, DBG_IMPORTANT, "helperDispatch: invalid callback data");
        delete r;
        return;
    }

    r->request.Id = reqId;
    helper_server::Requests::iterator it = srv->requests.insert(srv->requests.end(), r);
    r->request.dispatch_time = current_time;

    if (srv->wqueue->isNull())
        srv->wqueue->init();

    if (hlp->childs.concurrency) {
        srv->requestsIndex.insert(helper_server::RequestIndex::value_type(reqId, it));
        assert(srv->requestsIndex.size() == srv->requests.size());
        srv->wqueue->appendf("%" PRIu64 " %s", reqId, r->request.buf);
    } else
        srv->wqueue->append(r->request.buf, strlen(r->request.buf));

    if (!srv->flags.writing) {
        assert(NULL == srv->writebuf);
        srv->writebuf = srv->wqueue;
        srv->wqueue = new MemBuf;
        srv->flags.writing = true;
        AsyncCall::Pointer call = commCbCall(5,5, "helperDispatchWriteDone",
                                             CommIoCbPtrFun(helperDispatchWriteDone, srv));
        Comm::Write(srv->writePipe, srv->writebuf->content(), srv->writebuf->contentSize(), call, NULL);
    }

    debugs(84, 5, "helperDispatch: Request sent to " << hlp->id_name << " #" << srv->index << ", " << strlen(r->request.buf) << " bytes");

    ++ srv->stats.uses;
    ++ srv->stats.pending;
    ++ hlp->stats.requests;
}