void
FwdState::connectTimeout(int fd)
{
    debugs(17, 2, "fwdConnectTimeout: FD " << fd << ": '" << entry->url() << "'" );
    assert(serverDestinations[0] != NULL);
    assert(fd == serverDestinations[0]->fd);

    if (entry->isEmpty()) {
        ErrorState *anErr = new ErrorState(ERR_CONNECT_FAIL, HTTP_GATEWAY_TIMEOUT, request);
        anErr->xerrno = ETIMEDOUT;
        fail(anErr);

        /* This marks the peer DOWN ... */
        if (serverDestinations[0]->getPeer())
            peerConnectFailed(serverDestinations[0]->getPeer());
    }

    if (Comm::IsConnOpen(serverDestinations[0])) {
        serverDestinations[0]->close();
    }
}