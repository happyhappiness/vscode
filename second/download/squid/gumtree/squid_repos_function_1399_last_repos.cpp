static void
helperHandleRead(const Comm::ConnectionPointer &conn, char *, size_t len, Comm::Flag flag, int, void *data)
{
    helper_server *srv = (helper_server *)data;
    helper *hlp = srv->parent;
    assert(cbdataReferenceValid(data));

    /* Bail out early on Comm::ERR_CLOSING - close handlers will tidy up for us */

    if (flag == Comm::ERR_CLOSING) {
        return;
    }

    assert(conn->fd == srv->readPipe->fd);

    debugs(84, 5, "helperHandleRead: " << len << " bytes from " << hlp->id_name << " #" << srv->index);

    if (flag != Comm::OK || len == 0) {
        srv->closePipesSafely(hlp->id_name);
        return;
    }

    srv->roffset += len;
    srv->rbuf[srv->roffset] = '\0';
    debugs(84, DBG_DATA, Raw("accumulated", srv->rbuf, srv->roffset));

    if (!srv->stats.pending && !srv->stats.timedout) {
        /* someone spoke without being spoken to */
        debugs(84, DBG_IMPORTANT, "helperHandleRead: unexpected read from " <<
               hlp->id_name << " #" << srv->index << ", " << (int)len <<
               " bytes '" << srv->rbuf << "'");

        srv->roffset = 0;
        srv->rbuf[0] = '\0';
    }

    bool needsMore = false;
    char *msg = srv->rbuf;
    while (*msg && !needsMore) {
        int skip = 0;
        char *eom = strchr(msg, hlp->eom);
        if (eom) {
            skip = 1;
            debugs(84, 3, "helperHandleRead: end of reply found");
            if (eom > msg && eom[-1] == '\r' && hlp->eom == '\n') {
                *eom = '\0';
                // rewind to the \r octet which is the real terminal now
                // and remember that we have to skip forward 2 places now.
                skip = 2;
                --eom;
            }
            *eom = '\0';
        }

        if (!srv->ignoreToEom && !srv->replyXaction) {
            int i = 0;
            if (hlp->childs.concurrency) {
                char *e = NULL;
                i = strtol(msg, &e, 10);
                // Do we need to check for e == msg? Means wrong response from helper.
                // Will be droped as "unexpected reply on channel 0"
                needsMore = !(xisspace(*e) || (eom && e == eom));
                if (!needsMore) {
                    msg = e;
                    while (*msg && xisspace(*msg))
                        ++msg;
                } // else not enough data to compute request number
            }
            if (!(srv->replyXaction = srv->popRequest(i))) {
                if (srv->stats.timedout) {
                    debugs(84, 3, "Timedout reply received for request-ID: " << i << " , ignore");
                } else {
                    debugs(84, DBG_IMPORTANT, "helperHandleRead: unexpected reply on channel " <<
                           i << " from " << hlp->id_name << " #" << srv->index <<
                           " '" << srv->rbuf << "'");
                }
                srv->ignoreToEom = true;
            }
        } // else we need to just append reply data to the current Xaction

        if (!needsMore) {
            size_t msgSize  = eom ? eom - msg : (srv->roffset - (msg - srv->rbuf));
            assert(msgSize <= srv->rbuf_sz);
            helperReturnBuffer(srv, hlp, msg, msgSize, eom);
            msg += msgSize + skip;
            assert(static_cast<size_t>(msg - srv->rbuf) <= srv->rbuf_sz);

            // The next message should not ignored.
            if (eom && srv->ignoreToEom)
                srv->ignoreToEom = false;
        } else
            assert(skip == 0 && eom == NULL);
    }

    if (needsMore) {
        size_t msgSize = (srv->roffset - (msg - srv->rbuf));
        assert(msgSize <= srv->rbuf_sz);
        memmove(srv->rbuf, msg, msgSize);
        srv->roffset = msgSize;
        srv->rbuf[srv->roffset] = '\0';
    } else {
        // All of the responses parsed and msg points at the end of read data
        assert(static_cast<size_t>(msg - srv->rbuf) == srv->roffset);
        srv->roffset = 0;
    }

    if (Comm::IsConnOpen(srv->readPipe) && !fd_table[srv->readPipe->fd].closing()) {
        int spaceSize = srv->rbuf_sz - srv->roffset - 1;
        assert(spaceSize >= 0);

        AsyncCall::Pointer call = commCbCall(5,4, "helperHandleRead",
                                             CommIoCbPtrFun(helperHandleRead, srv));
        comm_read(srv->readPipe, srv->rbuf + srv->roffset, spaceSize, call);
    }
}