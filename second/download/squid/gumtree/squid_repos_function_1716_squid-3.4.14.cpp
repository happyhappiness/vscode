static void
helperReturnBuffer(int request_number, helper_server * srv, helper * hlp, char * msg, char * msg_end)
{
    helper_request *r = srv->requests[request_number];
    if (r) {
        HLPCB *callback = r->callback;

        srv->requests[request_number] = NULL;

        r->callback = NULL;

        void *cbdata = NULL;
        if (cbdataReferenceValidDone(r->data, &cbdata)) {
            HelperReply response(msg, (msg_end-msg));
            callback(cbdata, response);
        }

        -- srv->stats.pending;
        ++ srv->stats.replies;

        ++ hlp->stats.replies;

        srv->answer_time = current_time;

        srv->dispatch_time = r->dispatch_time;

        hlp->stats.avg_svc_time =
            Math::intAverage(hlp->stats.avg_svc_time,
                             tvSubMsec(r->dispatch_time, current_time),
                             hlp->stats.replies, REDIRECT_AV_FACTOR);

        helperRequestFree(r);
    } else {
        debugs(84, DBG_IMPORTANT, "helperHandleRead: unexpected reply on channel " <<
               request_number << " from " << hlp->id_name << " #" << srv->index <<
               " '" << srv->rbuf << "'");
    }

    if (!srv->flags.shutdown) {
        helperKickQueue(hlp);
    } else if (!srv->flags.closing && !srv->stats.pending) {
        srv->flags.closing=true;
        srv->writePipe->close();
    }
}