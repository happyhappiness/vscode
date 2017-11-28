/* This is a handler normally called by comm_close() */
void ConnStateData::connStateClosed(const CommCloseCbParams &io)
{
    deleteThis("ConnStateData::connStateClosed");
}

#if USE_AUTH
void
ConnStateData::setAuth(const Auth::UserRequest::Pointer &aur, const char *by)
{
    if (auth_ == NULL) {
        if (aur != NULL) {
            debugs(33, 2, "Adding connection-auth to " << clientConnection << " from " << by);
            auth_ = aur;
        }
        return;
    }

    // clobered with self-pointer
    // NP: something nasty is going on in Squid, but harmless.
    if (aur == auth_) {
        debugs(33, 2, "WARNING: Ignoring duplicate connection-auth for " << clientConnection << " from " << by);
        return;
    }

    /*
     * Connection-auth relies on a single set of credentials being preserved
     * for all requests on a connection once they have been setup.
     * There are several things which need to happen to preserve security
     * when connection-auth credentials change unexpectedly or are unset.
     *
     * 1) auth helper released from any active state
     *
     * They can only be reserved by a handshake process which this
     * connection can now never complete.
     * This prevents helpers hanging when their connections close.
     *
     * 2) pinning is expected to be removed and server conn closed
     *
     * The upstream link is authenticated with the same credentials.
     * Expecting the same level of consistency we should have received.
     * This prevents upstream being faced with multiple or missing
     * credentials after authentication.
     * NP: un-pin is left to the cleanup in ConnStateData::swanSong()
     *     we just trigger that cleanup here via comm_reset_close() or
     *     ConnStateData::stopReceiving()
     *
     * 3) the connection needs to close.
     *
     * This prevents attackers injecting requests into a connection,
     * or gateways wrongly multiplexing users into a single connection.
     *
     * When credentials are missing closure needs to follow an auth
     * challenge for best recovery by the client.
     *
     * When credentials change there is nothing we can do but abort as
     * fast as possible. Sending TCP RST instead of an HTTP response
     * is the best-case action.
     */

    // clobbered with nul-pointer
    if (aur == NULL) {
        debugs(33, 2, "WARNING: Graceful closure on " << clientConnection << " due to connection-auth erase from " << by);
        auth_->releaseAuthServer();
        auth_ = NULL;
        // XXX: need to test whether the connection re-auth challenge is sent. If not, how to trigger it from here.
        // NP: the current situation seems to fix challenge loops in Safari without visible issues in others.
        // we stop receiving more traffic but can leave the Job running to terminate after the error or challenge is delivered.
        stopReceiving("connection-auth removed");
        return;
    }

    // clobbered with alternative credentials
    if (aur != auth_) {
        debugs(33, 2, "ERROR: Closing " << clientConnection << " due to change of connection-auth from " << by);
        auth_->releaseAuthServer();
        auth_ = NULL;
        // this is a fatal type of problem.
        // Close the connection immediately with TCP RST to abort all traffic flow
        comm_reset_close(clientConnection);
        return;
    }

    /* NOT REACHABLE */
}
#endif

// cleans up before destructor is called
void
ConnStateData::swanSong()
{
    debugs(33, 2, HERE << clientConnection);
    flags.readMore = false;
    clientdbEstablished(clientConnection->remote, -1);	/* decrement */
    assert(areAllContextsForThisConnection());
    freeAllContexts();

    unpinConnection();

    if (Comm::IsConnOpen(clientConnection))
        clientConnection->close();

#if USE_AUTH
    // NP: do this bit after closing the connections to avoid side effects from unwanted TCP RST
    setAuth(NULL, "ConnStateData::SwanSong cleanup");
#endif

    BodyProducer::swanSong();
    flags.swanSang = true;
}

bool
