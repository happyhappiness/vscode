static void
helperStatefulHandleRead(const Comm::ConnectionPointer &conn, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    char *t = NULL;
    helper_stateful_server *srv = (helper_stateful_server *)data;
    helper_stateful_request *r;
    statefulhelper *hlp = srv->parent;
    assert(cbdataReferenceValid(data));

    /* Bail out early on COMM_ERR_CLOSING - close handlers will tidy up for us */

    if (flag == COMM_ERR_CLOSING) {
        return;
    }

    assert(conn->fd == srv->readPipe->fd);

    debugs(84, 5, "helperStatefulHandleRead: " << len << " bytes from " <<
           hlp->id_name << " #" << srv->index + 1);

    if (flag != COMM_OK || len == 0) {
        srv->closePipesSafely();
        return;
    }

    srv->roffset += len;
    srv->rbuf[srv->roffset] = '\0';
    r = srv->request;

    if (r == NULL) {
        /* someone spoke without being spoken to */
        debugs(84, DBG_IMPORTANT, "helperStatefulHandleRead: unexpected read from " <<
               hlp->id_name << " #" << srv->index + 1 << ", " << (int)len <<
               " bytes '" << srv->rbuf << "'");

        srv->roffset = 0;
    }

    if ((t = strchr(srv->rbuf, hlp->eom))) {
        /* end of reply found */
        int called = 1;
        debugs(84, 3, "helperStatefulHandleRead: end of reply found");

        if (t > srv->rbuf && t[-1] == '\r' && hlp->eom == '\n')
            t[-1] = '\0';

        *t = '\0';

        if (r && cbdataReferenceValid(r->data)) {
            r->callback(r->data, srv, srv->rbuf);
        } else {
            debugs(84, DBG_IMPORTANT, "StatefulHandleRead: no callback data registered");
            called = 0;
        }

        srv->flags.busy = 0;
        srv->roffset = 0;
        helperStatefulRequestFree(r);
        srv->request = NULL;

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
        int spaceSize = srv->rbuf_sz - srv->roffset - 1;
        assert(spaceSize >= 0);

        // grow the input buffer if needed and possible
        if (!spaceSize && srv->rbuf_sz + 4096 <= ReadBufMaxSize) {
            srv->rbuf = (char *)memReallocBuf(srv->rbuf, srv->rbuf_sz + 4096, &srv->rbuf_sz);
            debugs(84, 3, HERE << "Grew read buffer to " << srv->rbuf_sz);
            spaceSize = srv->rbuf_sz - srv->roffset - 1;
            assert(spaceSize >= 0);
        }

        // quit reading if there is no space left
        if (!spaceSize) {
            debugs(84, DBG_IMPORTANT, "ERROR: Disconnecting from a " <<
                   "helper that overflowed " << srv->rbuf_sz << "-byte " <<
                   "Squid input buffer: " << hlp->id_name << " #" <<
                   (srv->index + 1));
            srv->closePipesSafely();
            return;
        }

        AsyncCall::Pointer call = commCbCall(5,4, "helperStatefulHandleRead",
                                             CommIoCbPtrFun(helperStatefulHandleRead, srv));
        comm_read(srv->readPipe, srv->rbuf + srv->roffset, spaceSize, call);
    }
}