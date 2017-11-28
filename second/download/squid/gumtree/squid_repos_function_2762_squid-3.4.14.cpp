static void
tunnelStartShoveling(TunnelStateData *tunnelState)
{
    assert(!tunnelState->waitingForConnectExchange());
    *tunnelState->status_ptr = Http::scOkay;
    if (cbdataReferenceValid(tunnelState)) {

        // Shovel any payload already pushed into reply buffer by the server response
        if (!tunnelState->server.len)
            tunnelState->copyRead(tunnelState->server, TunnelStateData::ReadServer);
        else {
            debugs(26, DBG_DATA, "Tunnel server PUSH Payload: \n" << Raw("", tunnelState->server.buf, tunnelState->server.len) << "\n----------");
            tunnelState->copy(tunnelState->server.len, tunnelState->server, tunnelState->client, TunnelStateData::WriteClientDone);
        }

        // Bug 3371: shovel any payload already pushed into ConnStateData by the client request
        if (tunnelState->http.valid() && tunnelState->http->getConn() && tunnelState->http->getConn()->in.notYetUsed) {
            struct ConnStateData::In *in = &tunnelState->http->getConn()->in;
            debugs(26, DBG_DATA, "Tunnel client PUSH Payload: \n" << Raw("", in->buf, in->notYetUsed) << "\n----------");

            // We just need to ensure the bytes from ConnStateData are in client.buf already to deliver
            memcpy(tunnelState->client.buf, in->buf, in->notYetUsed);
            // NP: readClient() takes care of buffer length accounting.
            tunnelState->readClient(tunnelState->client.buf, in->notYetUsed, COMM_OK, 0);
            in->notYetUsed = 0; // ConnStateData buffer accounting after the shuffle.
        } else
            tunnelState->copyRead(tunnelState->client, TunnelStateData::ReadClient);
    }
}