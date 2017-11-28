void
FwdState::connectedToPeer(Ssl::PeerConnectorAnswer &answer)
{
    if (ErrorState *error = answer.error.get()) {
        fail(error);
        answer.error.clear(); // preserve error for errorSendComplete()
        if (CachePeer *p = serverConnection()->getPeer())
            peerConnectFailed(p);
        serverConnection()->close();
        return;
    }

    if (serverConnection()->getPeer())
        peerConnectSucceded(serverConnection()->getPeer());

    flags.connected_okay = true;
    dispatch();
}