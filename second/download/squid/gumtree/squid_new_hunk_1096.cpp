    if (clen < 0)
        return INCOMPLETE_MSG;

    /** \par
     * If the body size is known, we must wait until we've gotten all of it. */
    if (clen > 0) {
        debugs(11,5, "payloadSeen=" << payloadSeen << " content_length=" << vrep->content_length);

        if (payloadSeen < vrep->content_length)
            return INCOMPLETE_MSG;

        if (payloadTruncated > 0) // already read more than needed
            return COMPLETE_NONPERSISTENT_MSG; // disable pconns
    }

    /** \par
     * If there is no message body or we got it all, we can be persistent */
    return statusIfComplete();
}

static void
readDelayed(void *context, CommRead const &)
{
    HttpStateData *state = static_cast<HttpStateData*>(context);
    state->flags.do_next_read = true;
    state->maybeReadVirginBody();
}

void
HttpStateData::readReply(const CommIoCbParams &io)
{
    Must(!flags.do_next_read); // XXX: should have been set false by mayReadVirginBody()
    flags.do_next_read = false;

    debugs(11, 5, io.conn);

    // Bail out early on Comm::ERR_CLOSING - close handlers will tidy up for us
    if (io.flag == Comm::ERR_CLOSING) {
        debugs(11, 3, "http socket closing");
        return;
    }

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        abortTransaction("store entry aborted while reading reply");
        return;
    }

    Must(Comm::IsConnOpen(serverConnection));
    Must(io.conn->fd == serverConnection->fd);

    /*
     * Don't reset the timeout value here. The value should be
     * counting Config.Timeout.request and applies to the request
     * as a whole, not individual read() calls.
     * Plus, it breaks our lame *HalfClosed() detection
     */

    Must(maybeMakeSpaceAvailable(true));
    CommIoCbParams rd(this); // will be expanded with ReadNow results
    rd.conn = io.conn;
    rd.size = entry->bytesWanted(Range<size_t>(0, inBuf.spaceSize()));

    if (rd.size <= 0) {
        assert(entry->mem_obj);
        AsyncCall::Pointer nilCall;
        entry->mem_obj->delayRead(DeferredRead(readDelayed, this, CommRead(io.conn, NULL, 0, nilCall)));
        return;
    }

    switch (Comm::ReadNow(rd, inBuf)) {
    case Comm::INPROGRESS:
        if (inBuf.isEmpty())
            debugs(33, 2, io.conn << ": no data to process, " << xstrerr(rd.xerrno));
        flags.do_next_read = true;
        maybeReadVirginBody();
        return;

    case Comm::OK:
    {
        payloadSeen += rd.size;
#if USE_DELAY_POOLS
        DelayId delayId = entry->mem_obj->mostBytesAllowed();
        delayId.bytesIn(rd.size);
#endif

        statCounter.server.all.kbytes_in += rd.size;
        statCounter.server.http.kbytes_in += rd.size;
        ++ IOStats.Http.reads;

        int bin = 0;
        for (int clen = rd.size - 1; clen; ++bin)
            clen >>= 1;

        ++ IOStats.Http.read_hist[bin];

        // update peer response time stats (%<pt)
        const timeval &sent = request->hier.peer_http_request_sent;
        if (sent.tv_sec)
            tvSub(request->hier.peer_response_time, sent, current_time);
        else
            request->hier.peer_response_time.tv_sec = -1;
    }

        /* Continue to process previously read data */
    break;

    case Comm::ENDFILE: // close detected by 0-byte read
        eof = 1;
        flags.do_next_read = false;

        /* Continue to process previously read data */
        break;

    // case Comm::COMM_ERROR:
    default: // no other flags should ever occur
        debugs(11, 2, io.conn << ": read failure: " << xstrerr(rd.xerrno));
        ErrorState *err = new ErrorState(ERR_READ_ERROR, Http::scBadGateway, fwd->request);
        err->xerrno = rd.xerrno;
        fwd->fail(err);
        flags.do_next_read = false;
        closeServer();
        mustStop("HttpStateData::readReply");
        return;
    }

    /* Process next response from buffer */
    processReply();
}

/// processes the already read and buffered response data, possibly after
/// waiting for asynchronous 1xx control message processing
void
