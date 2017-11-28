static void
gopherReadReply(const Comm::ConnectionPointer &conn, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    GopherStateData *gopherState = (GopherStateData *)data;
    StoreEntry *entry = gopherState->entry;
    int clen;
    int bin;
    size_t read_sz = BUFSIZ;
#if USE_DELAY_POOLS
    DelayId delayId = entry->mem_obj->mostBytesAllowed();
#endif

    /* Bail out early on COMM_ERR_CLOSING - close handlers will tidy up for us */

    if (flag == COMM_ERR_CLOSING) {
        return;
    }

    assert(buf == gopherState->replybuf);

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        gopherState->serverConn->close();
        return;
    }

#if USE_DELAY_POOLS
    read_sz = delayId.bytesWanted(1, read_sz);
#endif

    /* leave one space for \0 in gopherToHTML */

    if (flag == COMM_OK && len > 0) {
#if USE_DELAY_POOLS
        delayId.bytesIn(len);
#endif

        kb_incr(&(statCounter.server.all.kbytes_in), len);
        kb_incr(&(statCounter.server.other.kbytes_in), len);
    }

    debugs(10, 5, HERE << conn << " read len=" << len);

    if (flag == COMM_OK && len > 0) {
        AsyncCall::Pointer nil;
        commSetConnTimeout(conn, Config.Timeout.read, nil);
        ++IOStats.Gopher.reads;

        for (clen = len - 1, bin = 0; clen; ++bin)
            clen >>= 1;

        ++IOStats.Gopher.read_hist[bin];

        HttpRequest *req = gopherState->fwd->request;
        if (req->hier.bodyBytesRead < 0)
            req->hier.bodyBytesRead = 0;

        req->hier.bodyBytesRead += len;
    }

    if (flag != COMM_OK) {
        debugs(50, DBG_IMPORTANT, "gopherReadReply: error reading: " << xstrerror());

        if (ignoreErrno(xerrno)) {
            AsyncCall::Pointer call = commCbCall(5,4, "gopherReadReply",
                                                 CommIoCbPtrFun(gopherReadReply, gopherState));
            comm_read(conn, buf, read_sz, call);
        } else {
            ErrorState *err = new ErrorState(ERR_READ_ERROR, HTTP_INTERNAL_SERVER_ERROR, gopherState->fwd->request);
            err->xerrno = xerrno;
            gopherState->fwd->fail(err);
            gopherState->serverConn->close();
        }
    } else if (len == 0 && entry->isEmpty()) {
        gopherState->fwd->fail(new ErrorState(ERR_ZERO_SIZE_OBJECT, HTTP_SERVICE_UNAVAILABLE, gopherState->fwd->request));
        gopherState->serverConn->close();
    } else if (len == 0) {
        /* Connection closed; retrieval done. */
        /* flush the rest of data in temp buf if there is one. */

        if (gopherState->conversion != gopher_ds::NORMAL)
            gopherEndHTML(gopherState);

        entry->timestampsSet();
        entry->flush();
        gopherState->fwd->complete();
        gopherState->serverConn->close();
    } else {
        if (gopherState->conversion != gopher_ds::NORMAL) {
            gopherToHTML(gopherState, buf, len);
        } else {
            entry->append(buf, len);
        }
        AsyncCall::Pointer call = commCbCall(5,4, "gopherReadReply",
                                             CommIoCbPtrFun(gopherReadReply, gopherState));
        comm_read(conn, buf, read_sz, call);
    }
}