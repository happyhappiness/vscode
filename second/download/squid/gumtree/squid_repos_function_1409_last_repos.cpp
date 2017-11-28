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