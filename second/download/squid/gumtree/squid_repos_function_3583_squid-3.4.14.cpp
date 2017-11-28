void
ConnStateData::clientReadRequest(const CommIoCbParams &io)
{
    debugs(33,5,HERE << io.conn << " size " << io.size);
    Must(reading());
    reader = NULL;

    /* Bail out quickly on COMM_ERR_CLOSING - close handlers will tidy up */

    if (io.flag == COMM_ERR_CLOSING) {
        debugs(33,5, HERE << io.conn << " closing Bailout.");
        return;
    }

    assert(Comm::IsConnOpen(clientConnection));
    assert(io.conn->fd == clientConnection->fd);

    /*
     * Don't reset the timeout value here.  The timeout value will be
     * set to Config.Timeout.request by httpAccept() and
     * clientWriteComplete(), and should apply to the request as a
     * whole, not individual read() calls.  Plus, it breaks our
     * lame half-close detection
     */
    if (connReadWasError(io.flag, io.size, io.xerrno)) {
        notifyAllContexts(io.xerrno);
        io.conn->close();
        return;
    }

    if (io.flag == COMM_OK) {
        if (io.size > 0) {
            kb_incr(&(statCounter.client_http.kbytes_in), io.size);

            // may comm_close or setReplyToError
            if (!handleReadData(io.buf, io.size))
                return;

        } else if (io.size == 0) {
            debugs(33, 5, HERE << io.conn << " closed?");

            if (connFinishedWithConn(io.size)) {
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
        }
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