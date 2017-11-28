static void
helperHandleRead(const Comm::ConnectionPointer &conn, char *buf, size_t len, Comm::Flag flag, int xerrno, void *data)
{
    char *t = NULL;
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

    if (!srv->stats.pending) {
        /* someone spoke without being spoken to */
        debugs(84, DBG_IMPORTANT, "helperHandleRead: unexpected read from " <<
               hlp->id_name << " #" << srv->index << ", " << (int)len <<
               " bytes '" << srv->rbuf << "'");

        srv->roffset = 0;
        srv->rbuf[0] = '\0';
    }

    while ((t = strchr(srv->rbuf, hlp->eom))) {
        /* end of reply found */
        char *msg = srv->rbuf;
        int i = 0;
        int skip = 1;
        debugs(84, 3, "helperHandleRead: end of reply found");

        if (t > srv->rbuf && t[-1] == '\r' && hlp->eom == '\n') {
            *t = '\0';
            // rewind to the \r octet which is the real terminal now
            // and remember that we have to skip forward 2 places now.
            skip = 2;
            --t;
        }

        *t = '\0';

        if (hlp->childs.concurrency) {
            i = strtol(msg, &msg, 10);

            while (*msg && xisspace(*msg))
                ++msg;
        }

        helperReturnBuffer(i, srv, hlp, msg, t);
        srv->roffset -= (t - srv->rbuf) + skip;
        memmove(srv->rbuf, t + skip, srv->roffset);
        srv->rbuf[srv->roffset] = '\0';
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
                   "Squid input buffer: " << hlp->id_name << " #" << srv->index);
            srv->closePipesSafely(hlp->id_name);
            return;
        }

        AsyncCall::Pointer call = commCbCall(5,4, "helperHandleRead",
                                             CommIoCbPtrFun(helperHandleRead, srv));
        comm_read(srv->readPipe, srv->rbuf + srv->roffset, spaceSize, call);
    }
}