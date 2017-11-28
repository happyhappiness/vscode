HttpStateData::readReply(const CommIoCbParams &io)
{
    int bin;
    int clen;
    int len = io.size;

    assert(fd == io.fd);

    flags.do_next_read = 0;

    debugs(11, 5, "httpReadReply: FD " << fd << ": len " << len << ".");

    // Bail out early on COMM_ERR_CLOSING - close handlers will tidy up for us
    if (io.flag == COMM_ERR_CLOSING) {
        debugs(11, 3, "http socket closing");
        return;
    }

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        maybeReadVirginBody();
        return;
    }

    // handle I/O errors
    if (io.flag != COMM_OK || len < 0) {
        debugs(11, 2, "httpReadReply: FD " << fd << ": read failure: " << xstrerror() << ".");

        if (ignoreErrno(io.xerrno)) {
            flags.do_next_read = 1;
        } else {
            ErrorState *err;
            err = errorCon(ERR_READ_ERROR, HTTP_BAD_GATEWAY, fwd->request);
            err->xerrno = io.xerrno;
            fwd->fail(err);
            flags.do_next_read = 0;
            comm_close(fd);
        }

        return;
    }

    // update I/O stats
    if (len > 0) {
        readBuf->appended(len);
        reply_bytes_read += len;
#if DELAY_POOLS

        DelayId delayId = entry->mem_obj->mostBytesAllowed();
        delayId.bytesIn(len);
#endif

        kb_incr(&statCounter.server.all.kbytes_in, len);
        kb_incr(&statCounter.server.http.kbytes_in, len);
        IOStats.Http.reads++;

        for (clen = len - 1, bin = 0; clen; bin++)
            clen >>= 1;

        IOStats.Http.read_hist[bin]++;

        // update peer response time stats (%<pt)
        const timeval &sent = orig_request->hier.peer_http_request_sent;
        orig_request->hier.peer_response_time =
            sent.tv_sec ? tvSubMsec(sent, current_time) : -1;
    }

    /** \par
     * Here the RFC says we should ignore whitespace between replies, but we can't as
     * doing so breaks HTTP/0.9 replies beginning with witespace, and in addition
     * the response splitting countermeasures is extremely likely to trigger on this,
     * not allowing connection reuse in the first place.
     */
#if DONT_DO_THIS
    if (!flags.headers_parsed && len > 0 && fd_table[fd].uses > 1) {
        /* Skip whitespace between replies */

        while (len > 0 && xisspace(*buf))
            xmemmove(buf, buf + 1, len--);

        if (len == 0) {
            /* Continue to read... */
            /* Timeout NOT increased. This whitespace was from previous reply */
            flags.do_next_read = 1;
            maybeReadVirginBody();
            return;
        }
    }

#endif

    if (len == 0) { // reached EOF?
        eof = 1;
        flags.do_next_read = 0;

        /* Bug 2879: Replies may terminate with \r\n then EOF instead of \r\n\r\n
