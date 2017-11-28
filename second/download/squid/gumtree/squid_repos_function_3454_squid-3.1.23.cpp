void
ClientSocketContext::keepaliveNextRequest()
{
    ConnStateData * conn = http->getConn();
    bool do_next_read = false;

    debugs(33, 3, "ClientSocketContext::keepaliveNextRequest: FD " << conn->fd);
    connIsFinished();

    if (conn->pinning.pinned && conn->pinning.fd == -1) {
        debugs(33, 2, "clientKeepaliveNextRequest: FD " << conn->fd << " Connection was pinned but server side gone. Terminating client connection");
        comm_close(conn->fd);
        return;
    }

    /** \par
     * We are done with the response, and we are either still receiving request
     * body (early response!) or have already stopped receiving anything.
     *
     * If we are still receiving, then clientParseRequest() below will fail.
     * (XXX: but then we will call readNextRequest() which may succeed and
     * execute a smuggled request as we are not done with the current request).
     *
     * If we stopped because we got everything, then try the next request.
     *
     * If we stopped receiving because of an error, then close now to avoid
     * getting stuck and to prevent accidental request smuggling.
     */

    if (const char *reason = conn->stoppedReceiving()) {
        debugs(33, 3, HERE << "closing for earlier request error: " << reason);
        comm_close(conn->fd);
        return;
    }

    /** \par
     * Attempt to parse a request from the request buffer.
     * If we've been fed a pipelined request it may already
     * be in our read buffer.
     *
     \par
     * This needs to fall through - if we're unlucky and parse the _last_ request
     * from our read buffer we may never re-register for another client read.
     */

    if (clientParseRequest(conn, do_next_read)) {
        debugs(33, 3, "clientSocketContext::keepaliveNextRequest: FD " << conn->fd << ": parsed next request from buffer");
    }

    /** \par
     * Either we need to kick-start another read or, if we have
     * a half-closed connection, kill it after the last request.
     * This saves waiting for half-closed connections to finished being
     * half-closed _AND_ then, sometimes, spending "Timeout" time in
     * the keepalive "Waiting for next request" state.
     */
    if (commIsHalfClosed(conn->fd) && (conn->getConcurrentRequestCount() == 0)) {
        debugs(33, 3, "ClientSocketContext::keepaliveNextRequest: half-closed client with no pending requests, closing");
        comm_close(conn->fd);
        return;
    }

    ClientSocketContext::Pointer deferredRequest;

    /** \par
     * At this point we either have a parsed request (which we've
     * kicked off the processing for) or not. If we have a deferred
     * request (parsed but deferred for pipeling processing reasons)
     * then look at processing it. If not, simply kickstart
     * another read.
     */

    if ((deferredRequest = conn->getCurrentContext()).getRaw()) {
        debugs(33, 3, "ClientSocketContext:: FD " << conn->fd << ": calling PushDeferredIfNeeded");
        ClientSocketContextPushDeferredIfNeeded(deferredRequest, conn);
    } else {
        debugs(33, 3, "ClientSocketContext:: FD " << conn->fd << ": calling conn->readNextRequest()");
        conn->readNextRequest();
    }
}