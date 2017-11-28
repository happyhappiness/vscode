void
ConnStateData::clientReadRequest(const CommIoCbParams &io)
{
    debugs(33,5, io.conn);
    Must(reading());
    reader = NULL;

    /* Bail out quickly on Comm::ERR_CLOSING - close handlers will tidy up */
    if (io.flag == Comm::ERR_CLOSING) {
        debugs(33,5, io.conn << " closing Bailout.");
        return;
    }

    assert(Comm::IsConnOpen(clientConnection));
    assert(io.conn->fd == clientConnection->fd);

    /*
     * Don't reset the timeout value here. The value should be
     * counting Config.Timeout.request and applies to the request
     * as a whole, not individual read() calls.
     * Plus, it breaks our lame *HalfClosed() detection
     */

    in.maybeMakeSpaceAvailable();
    CommIoCbParams rd(this); // will be expanded with ReadNow results
    rd.conn = io.conn;
    switch (Comm::ReadNow(rd, in.buf)) {
    case Comm::INPROGRESS:
        if (in.buf.isEmpty())
            debugs(33, 2, io.conn << ": no data to process, " << xstrerr(rd.xerrno));
        readSomeData();
        return;

    case Comm::OK:
        kb_incr(&(statCounter.client_http.kbytes_in), rd.size);
        // may comm_close or setReplyToError
        if (!handleReadData())
            return;

        /* Continue to process previously read data */
        break;

    case Comm::ENDFILE: // close detected by 0-byte read
        debugs(33, 5, io.conn << " closed?");

        if (connFinishedWithConn(rd.size)) {
            clientConnection->close();
            return;
        }

        /* It might be half-closed, we can't tell */
        fd_table[io.conn->fd].flags.socket_eof = true;
        commMarkHalfClosed(io.conn->fd);
        fd_note(io.conn->fd, "half-closed");

        /* There is one more close check at the end, to detect aborted
         * (partial) requests. At this point we can't tell if the request
         * is partial.
         */

        /* Continue to process previously read data */
        break;

    // case Comm::COMM_ERROR:
    default: // no other flags should ever occur
        debugs(33, 2, io.conn << ": got flag " << rd.flag << "; " << xstrerr(rd.xerrno));
        notifyAllContexts(rd.xerrno);
        io.conn->close();
        return;
    }

    /* Process next request */
    if (getConcurrentRequestCount() == 0)
        fd_note(io.fd, "Reading next request");

    if (!clientParseRequests()) {
        if (!isOpen())
            return;
        /*
         * If the client here is half closed and we failed
         * to parse a request, close the connection.
         * The above check with connFinishedWithConn() only
         * succeeds _if_ the buffer is empty which it won't
         * be if we have an incomplete request.
         * XXX: This duplicates ClientSocketContext::keepaliveNextRequest
         */
        if (getConcurrentRequestCount() == 0 && commIsHalfClosed(io.fd)) {
            debugs(33, 5, HERE << io.conn << ": half-closed connection, no completed request parsed, connection closing.");
            clientConnection->close();
            return;
        }
    }

    if (!isOpen())
        return;

    clientAfterReadingRequests();
}