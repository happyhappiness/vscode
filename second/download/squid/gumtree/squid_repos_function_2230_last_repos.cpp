void
TunnelStateData::connectExchangeCheckpoint()
{
    if (waitingForConnectResponse()) {
        debugs(26, 5, "still reading CONNECT response on " << server.conn);
    } else if (waitingForConnectRequest()) {
        debugs(26, 5, "still writing CONNECT request on " << server.conn);
    } else {
        assert(!waitingForConnectExchange());
        debugs(26, 3, "done with CONNECT exchange on " << server.conn);
        tunnelConnected(server.conn, this);
    }
}