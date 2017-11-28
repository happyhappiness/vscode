void
FwdState::connectedToPeer(Security::EncryptorAnswer &answer)
{
    if (ErrorState *error = answer.error.get()) {
        fail(error);
        answer.error.clear(); // preserve error for errorSendComplete()
        if (CachePeer *p = serverConnection()->getPeer())
            peerConnectFailed(p);
        serverConnection()->close();
        return;
    }

    if (answer.tunneled) {
        // TODO: When ConnStateData establishes tunnels, its state changes
        // [in ways that may affect logging?]. Consider informing
        // ConnStateData about our tunnel or otherwise unifying tunnel
        // establishment [side effects].
        unregister(serverConn); // async call owns it now
        complete(); // destroys us
        return;
    }

    // should reach ConnStateData before the dispatched Client job starts
    CallJobHere1(17, 4, request->clientConnectionManager, ConnStateData,
                 ConnStateData::notePeerConnection, serverConnection());

    if (serverConnection()->getPeer())
        peerConnectSucceded(serverConnection()->getPeer());

    flags.connected_okay = true;
    dispatch();
}