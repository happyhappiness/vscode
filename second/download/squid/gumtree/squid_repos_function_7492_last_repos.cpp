void
Security::BlindPeerConnector::noteNegotiationDone(ErrorState *error)
{
    if (error) {
        debugs(83, 5, "error=" << (void*)error);
        // XXX: forward.cc calls peerConnectSucceeded() after an OK TCP connect but
        // we call peerConnectFailed() if SSL failed afterwards. Is that OK?
        // It is not clear whether we should call peerConnectSucceeded/Failed()
        // based on TCP results, SSL results, or both. And the code is probably not
        // consistent in this aspect across tunnelling and forwarding modules.
        if (CachePeer *p = serverConnection()->getPeer())
            peerConnectFailed(p);
        return;
    }

    if (auto *peer = serverConnection()->getPeer()) {
        const int fd = serverConnection()->fd;
        Security::MaybeGetSessionResumeData(fd_table[fd].ssl, peer->sslSession);
    }
}