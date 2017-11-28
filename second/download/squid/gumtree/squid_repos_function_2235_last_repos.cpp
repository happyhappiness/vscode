void
TunnelStateData::connectToPeer()
{
    if (CachePeer *p = server.conn->getPeer()) {
        if (p->secure.encryptTransport) {
            AsyncCall::Pointer callback = asyncCall(5,4,
                                                    "TunnelStateData::ConnectedToPeer",
                                                    MyAnswerDialer(&TunnelStateData::connectedToPeer, this));
            auto *connector = new Security::BlindPeerConnector(request, server.conn, callback, al);
            AsyncJob::Start(connector); // will call our callback
            return;
        }
    }

    Security::EncryptorAnswer nil;
    connectedToPeer(nil);
}