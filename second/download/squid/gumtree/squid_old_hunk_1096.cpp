    if (clen < 0)
        return INCOMPLETE_MSG;

    /** \par
     * If the body size is known, we must wait until we've gotten all of it. */
    if (clen > 0) {
        // old technique:
        // if (entry->mem_obj->endOffset() < vrep->content_length + vrep->hdr_sz)
        const int64_t body_bytes_read = reply_bytes_read - header_bytes_read;
        debugs(11,5, "persistentConnStatus: body_bytes_read=" <<
               body_bytes_read << " content_length=" << vrep->content_length);

        if (body_bytes_read < vrep->content_length)
            return INCOMPLETE_MSG;

        if (body_bytes_truncated > 0) // already read more than needed
            return COMPLETE_NONPERSISTENT_MSG; // disable pconns
    }

    /** \par
     * If there is no message body or we got it all, we can be persistent */
    return statusIfComplete();
}

/*
 * This is the callback after some data has been read from the network
 */
/*
void
HttpStateData::ReadReplyWrapper(int fd, char *buf, size_t len, Comm::Flag flag, int xerrno, void *data)
{
    HttpStateData *httpState = static_cast<HttpStateData *>(data);
    assert (fd == httpState->serverConnection->fd);
    // assert(buf == readBuf->content());
    PROF_start(HttpStateData_readReply);
    httpState->readReply(len, flag, xerrno);
    PROF_stop(HttpStateData_readReply);
}
*/

/* XXX this function is too long! */
void
HttpStateData::readReply(const CommIoCbParams &io)
{
    int bin;
    int clen;
    int len = io.size;

    flags.do_next_read = false;

    debugs(11, 5, HERE << io.conn << ": len " << len << ".");

    // Bail out early on Comm::ERR_CLOSING - close handlers will tidy up for us
    if (io.flag == Comm::ERR_CLOSING) {
        debugs(11, 3, "http socket closing");
        return;
    }

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        abortTransaction("store entry aborted while reading reply");
        return;
    }

    // handle I/O errors
    if (io.flag != Comm::OK || len < 0) {
        debugs(11, 2, HERE << io.conn << ": read failure: " << xstrerror() << ".");

        if (ignoreErrno(io.xerrno)) {
            flags.do_next_read = true;
        } else {
            ErrorState *err = new ErrorState(ERR_READ_ERROR, Http::scBadGateway, fwd->request);
            err->xerrno = io.xerrno;
            fwd->fail(err);
            flags.do_next_read = false;
            closeServer();
            mustStop("HttpStateData::readReply");
        }

        return;
    }

    // update I/O stats
    if (len > 0) {
        readBuf->appended(len);
        reply_bytes_read += len;
#if USE_DELAY_POOLS
        DelayId delayId = entry->mem_obj->mostBytesAllowed();
        delayId.bytesIn(len);
#endif

        kb_incr(&(statCounter.server.all.kbytes_in), len);
        kb_incr(&(statCounter.server.http.kbytes_in), len);
        ++ IOStats.Http.reads;

        for (clen = len - 1, bin = 0; clen; ++bin)
            clen >>= 1;

        ++ IOStats.Http.read_hist[bin];

        // update peer response time stats (%<pt)
        const timeval &sent = request->hier.peer_http_request_sent;
        request->hier.peer_response_time =
            sent.tv_sec ? tvSubMsec(sent, current_time) : -1;
    }

    /** \par
     * Here the RFC says we should ignore whitespace between replies, but we can't as
     * doing so breaks HTTP/0.9 replies beginning with witespace, and in addition
     * the response splitting countermeasures is extremely likely to trigger on this,
     * not allowing connection reuse in the first place.
     *
     * 2012-02-10: which RFC? not 2068 or 2616,
     *     tolerance there is all about whitespace between requests and header tokens.
     */

    if (len == 0) { // reached EOF?
        eof = 1;
        flags.do_next_read = false;

        /* Bug 2879: Replies may terminate with \r\n then EOF instead of \r\n\r\n
         * Ensure here that we have at minimum two \r\n when EOF is seen.
         * TODO: Add eof parameter to headersEnd() and move this hack there.
         */
        if (readBuf->contentSize() && !flags.headers_parsed) {
            /*
             * Yes Henrik, there is a point to doing this.  When we
             * called httpProcessReplyHeader() before, we didn't find
             * the end of headers, but now we are definately at EOF, so
             * we want to process the reply headers.
             */
            /* Fake an "end-of-headers" to work around such broken servers */
            readBuf->append("\r\n", 2);
        }
    }

    processReply();
}

/// processes the already read and buffered response data, possibly after
/// waiting for asynchronous 1xx control message processing
void
