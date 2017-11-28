                                             CommIoCbPtrFun(helperDispatchWriteDone, srv));
        Comm::Write(srv->writePipe, srv->writebuf->content(), srv->writebuf->contentSize(), call, NULL);
    }
}

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

static void
helperStatefulDispatchWriteDone(const Comm::ConnectionPointer &, char *, size_t, Comm::Flag, int, void *)
{}

static void
helperStatefulDispatch(helper_stateful_server * srv, Helper::Xaction * r)
{
    statefulhelper *hlp = srv->parent;

    if (!cbdataReferenceValid(r->request.data)) {
        debugs(84, DBG_IMPORTANT, "helperStatefulDispatch: invalid callback data");
        delete r;
        helperStatefulReleaseServer(srv);
        return;
    }

    debugs(84, 9, "helperStatefulDispatch busying helper " << hlp->id_name << " #" << srv->index);

    if (r->request.placeholder == 1) {
        /* a callback is needed before this request can _use_ a helper. */
        /* we don't care about releasing this helper. The request NEVER
         * gets to the helper. So we throw away the return code */
        r->reply.result = Helper::Unknown;
        r->reply.whichServer = srv;
        r->request.callback(r->request.data, r->reply);
        /* throw away the placeholder */
        delete r;
        /* and push the queue. Note that the callback may have submitted a new
         * request to the helper which is why we test for the request */

        if (!srv->requests.size())
            helperStatefulServerDone(srv);

        return;
    }

    srv->flags.reserved = true;
    srv->requests.push_back(r);
    srv->dispatch_time = current_time;
    AsyncCall::Pointer call = commCbCall(5,5, "helperStatefulDispatchWriteDone",
                                         CommIoCbPtrFun(helperStatefulDispatchWriteDone, hlp));
    Comm::Write(srv->writePipe, r->request.buf, strlen(r->request.buf), call, NULL);
    debugs(84, 5, "helperStatefulDispatch: Request sent to " <<
           hlp->id_name << " #" << srv->index << ", " <<
           (int) strlen(r->request.buf) << " bytes");

    ++ srv->stats.uses;
    ++ srv->stats.pending;
    ++ hlp->stats.requests;
}

static void
helperKickQueue(helper * hlp)
{
    Helper::Xaction *r;
    helper_server *srv;

    while ((srv = GetFirstAvailable(hlp)) && (r = hlp->nextRequest()))
        helperDispatch(srv, r);
}

static void
helperStatefulKickQueue(statefulhelper * hlp)
{
    Helper::Xaction *r;
    helper_stateful_server *srv;

    while ((srv = StatefulGetFirstAvailable(hlp)) && (r = hlp->nextRequest()))
        helperStatefulDispatch(srv, r);
}

static void
helperStatefulServerDone(helper_stateful_server * srv)
{
