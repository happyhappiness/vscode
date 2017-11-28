static void
helperReturnBuffer(helper_server * srv, helper * hlp, char * msg, size_t msgSize, char * msgEnd)
{
    if (Helper::Xaction *r = srv->replyXaction) {
        const bool hasSpace = r->reply.accumulate(msg, msgSize);
        if (!hasSpace) {
            debugs(84, DBG_IMPORTANT, "ERROR: Disconnecting from a " <<
                   "helper that overflowed " << srv->rbuf_sz << "-byte " <<
                   "Squid input buffer: " << hlp->id_name << " #" << srv->index);
            srv->closePipesSafely(hlp->id_name);
            return;
        }

        if (!msgEnd)
            return; // We are waiting for more data.

        bool retry = false;
        if (cbdataReferenceValid(r->request.data)) {
            r->reply.finalize();
            if (r->reply.result == Helper::BrokenHelper && r->request.retries < MAX_RETRIES) {
                debugs(84, DBG_IMPORTANT, "ERROR: helper: " << r->reply << ", attempt #" << (r->request.retries + 1) << " of 2");
                retry = true;
            } else {
                HLPCB *callback = r->request.callback;
                r->request.callback = nullptr;
                void *cbdata = nullptr;
                if (cbdataReferenceValidDone(r->request.data, &cbdata))
                    callback(cbdata, r->reply);
            }
        }

        -- srv->stats.pending;
        ++ srv->stats.replies;

        ++ hlp->stats.replies;

        srv->answer_time = current_time;

        srv->dispatch_time = r->request.dispatch_time;

        hlp->stats.avg_svc_time =
            Math::intAverage(hlp->stats.avg_svc_time,
                             tvSubMsec(r->request.dispatch_time, current_time),
                             hlp->stats.replies, REDIRECT_AV_FACTOR);

        // release or re-submit parsedRequestXaction object
        srv->replyXaction = nullptr;
        if (retry) {
            ++r->request.retries;
            hlp->submitRequest(r);
        } else
            delete r;
    }

    if (hlp->timeout && hlp->childs.concurrency)
        srv->checkForTimedOutRequests(hlp->retryTimedOut);

    if (!srv->flags.shutdown) {
        helperKickQueue(hlp);
    } else if (!srv->flags.closing && !srv->stats.pending) {
        srv->flags.closing=true;
        srv->writePipe->close();
    }
}