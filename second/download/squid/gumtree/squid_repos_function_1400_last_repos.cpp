static void
helperStatefulHandleRead(const Comm::ConnectionPointer &conn, char *, size_t len, Comm::Flag flag, int, void *data)
{
    char *t = NULL;
    helper_stateful_server *srv = (helper_stateful_server *)data;
    statefulhelper *hlp = srv->parent;
    assert(cbdataReferenceValid(data));

    /* Bail out early on Comm::ERR_CLOSING - close handlers will tidy up for us */

    if (flag == Comm::ERR_CLOSING) {
        return;
    }

    assert(conn->fd == srv->readPipe->fd);

    debugs(84, 5, "helperStatefulHandleRead: " << len << " bytes from " <<
           hlp->id_name << " #" << srv->index);

    if (flag != Comm::OK || len == 0) {
        srv->closePipesSafely(hlp->id_name);
        return;
    }

    srv->roffset += len;
    srv->rbuf[srv->roffset] = '\0';
    Helper::Xaction *r = srv->requests.front();
    debugs(84, DBG_DATA, Raw("accumulated", srv->rbuf, srv->roffset));

    if (r == NULL) {
        /* someone spoke without being spoken to */
        debugs(84, DBG_IMPORTANT, "helperStatefulHandleRead: unexpected read from " <<
               hlp->id_name << " #" << srv->index << ", " << (int)len <<
               " bytes '" << srv->rbuf << "'");

        srv->roffset = 0;
    }

    if ((t = strchr(srv->rbuf, hlp->eom))) {
        debugs(84, 3, "helperStatefulHandleRead: end of reply found");

        if (t > srv->rbuf && t[-1] == '\r' && hlp->eom == '\n') {
            *t = '\0';
            // rewind to the \r octet which is the real terminal now
            --t;
        }

        *t = '\0';
    }

    if (r && !r->reply.accumulate(srv->rbuf, t ? (t - srv->rbuf) : srv->roffset)) {
        debugs(84, DBG_IMPORTANT, "ERROR: Disconnecting from a " <<
               "helper that overflowed " << srv->rbuf_sz << "-byte " <<
               "Squid input buffer: " << hlp->id_name << " #" << srv->index);
        srv->closePipesSafely(hlp->id_name);
        return;
    }
    /**
     * BUG: the below assumes that only one response per read() was received and discards any octets remaining.
     *      Doing this prohibits concurrency support with multiple replies per read().
     * TODO: check that read() setup on these buffers pays attention to roffest!=0
     * TODO: check that replies bigger than the buffer are discarded and do not to affect future replies
     */
    srv->roffset = 0;

    if (t) {
        /* end of reply found */
        srv->requests.pop_front(); // we already have it in 'r'
        int called = 1;

        if (r && cbdataReferenceValid(r->request.data)) {
            r->reply.finalize();
            r->reply.whichServer = srv;
            r->request.callback(r->request.data, r->reply);
        } else {
            debugs(84, DBG_IMPORTANT, "StatefulHandleRead: no callback data registered");
            called = 0;
        }

        delete r;

        -- srv->stats.pending;
        ++ srv->stats.replies;

        ++ hlp->stats.replies;
        srv->answer_time = current_time;
        hlp->stats.avg_svc_time =
            Math::intAverage(hlp->stats.avg_svc_time,
                             tvSubMsec(srv->dispatch_time, current_time),
                             hlp->stats.replies, REDIRECT_AV_FACTOR);

        if (called)
            helperStatefulServerDone(srv);
        else
            helperStatefulReleaseServer(srv);
    }

    if (Comm::IsConnOpen(srv->readPipe) && !fd_table[srv->readPipe->fd].closing()) {
        int spaceSize = srv->rbuf_sz - 1;

        AsyncCall::Pointer call = commCbCall(5,4, "helperStatefulHandleRead",
                                             CommIoCbPtrFun(helperStatefulHandleRead, srv));
        comm_read(srv->readPipe, srv->rbuf, spaceSize, call);
    }
}