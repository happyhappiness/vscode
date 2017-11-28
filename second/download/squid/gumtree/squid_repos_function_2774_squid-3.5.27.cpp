void
TunnelStateData::connectToPeer()
{
    const Comm::ConnectionPointer &srv = server.conn;

#if USE_OPENSSL
    if (CachePeer *p = srv->getPeer()) {
        if (p->use_ssl) {
            AsyncCall::Pointer callback = asyncCall(5,4,
                                                    "TunnelStateData::ConnectedToPeer",
                                                    MyAnswerDialer(&TunnelStateData::connectedToPeer, this));
            Ssl::PeerConnector *connector =
                new Ssl::PeerConnector(request, srv, client.conn, callback);
            AsyncJob::Start(connector); // will call our callback
            return;
        }
    }
#endif

    tunnelRelayConnectRequest(srv, this);
}