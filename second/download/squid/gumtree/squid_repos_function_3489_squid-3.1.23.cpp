void
ConnStateData::clientReadRequest(const CommIoCbParams &io)
{
    debugs(33,5,HERE << "clientReadRequest FD " << io.fd << " size " << io.size);
    Must(reading());
    reader = NULL;
    bool do_next_read = 1; /* the default _is_ to read data! - adrian */

    assert (io.fd == fd);

    /* Bail out quickly on COMM_ERR_CLOSING - close handlers will tidy up */

    if (io.flag == COMM_ERR_CLOSING) {
        debugs(33,5, HERE  << " FD " << fd << " closing Bailout.");
        return;
    }

    /*
     * Don't reset the timeout value here.  The timeout value will be
     * set to Config.Timeout.request by httpAccept() and
     * clientWriteComplete(), and should apply to the request as a
     * whole, not individual read() calls.  Plus, it breaks our
     * lame half-close detection
     */
    if (connReadWasError(io.flag, io.size, io.xerrno)) {
        comm_close(fd);
        return;
    }

    if (io.flag == COMM_OK) {
        if (io.size > 0) {
            kb_incr(&statCounter.client_http.kbytes_in, io.size);

            handleReadData(io.buf, io.size);

            /* The above may close the connection under our feets */
            if (!isOpen())
                return;

        } else if (io.size == 0) {
            debugs(33, 5, "clientReadRequest: FD " << fd << " closed?");

            if (connFinishedWithConn(io.size)) {
                comm_close(fd);
                return;
            }

            /* It might be half-closed, we can't tell */
            fd_table[fd].flags.socket_eof = 1;

            commMarkHalfClosed(fd);

            do_next_read = 0;

            fd_note(fd, "half-closed");

            /* There is one more close check at the end, to detect aborted
             * (partial) requests. At this point we can't tell if the request
             * is partial.
             */
            /* Continue to process previously read data */
        }
    }

    /* Process next request */
    if (getConcurrentRequestCount() == 0)
        fd_note(fd, "Reading next request");

    if (! clientParseRequest(this, do_next_read)) {
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
        if (getConcurrentRequestCount() == 0 && commIsHalfClosed(fd)) {
            debugs(33, 5, "clientReadRequest: FD " << fd << ": half-closed connection, no completed request parsed, connection closing.");
            comm_close(fd);
            return;
        }
    }

    if (!isOpen())
        return;

    clientAfterReadingRequests(do_next_read);
}