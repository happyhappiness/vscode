void
FwdState::selectPeerForIntercepted()
{
    // use pinned connection if available
    Comm::ConnectionPointer p;
    if (ConnStateData *client = request->pinnedConnection()) {
        p = client->validatePinnedConnection(request, NULL);
        if (Comm::IsConnOpen(p)) {
            /* duplicate peerSelectPinned() effects */
            p->peerType = PINNED;
            entry->ping_status = PING_DONE;     /* Skip ICP */

            debugs(17, 3, "reusing a pinned conn: " << *p);
            serverDestinations.push_back(p);
        } else {
            debugs(17,2, "Pinned connection is not valid: " << p);
            ErrorState *anErr = new ErrorState(ERR_ZERO_SIZE_OBJECT, Http::scServiceUnavailable, request);
            fail(anErr);
        }
        // Either use the valid pinned connection or fail if it is invalid.
        return;
    }

    // use client original destination as second preferred choice
    p = new Comm::Connection();
    p->peerType = ORIGINAL_DST;
    p->remote = clientConn->local;
    getOutgoingAddress(request, p);

    debugs(17, 3, HERE << "using client original destination: " << *p);
    serverDestinations.push_back(p);
}