static void
tunnelStartShoveling(TunnelStateData *tunnelState)
{
    assert(!tunnelState->waitingForConnectExchange());
    *tunnelState->status_ptr = Http::scOkay;
    if (tunnelState->logTag_ptr)
        *tunnelState->logTag_ptr = LOG_TCP_TUNNEL;
    if (cbdataReferenceValid(tunnelState)) {

        // Shovel any payload already pushed into reply buffer by the server response
        if (!tunnelState->server.len)
            tunnelState->copyServerBytes();
        else {
            debugs(26, DBG_DATA, "Tunnel server PUSH Payload: \n" << Raw("", tunnelState->server.buf, tunnelState->server.len) << "\n----------");
            tunnelState->copy(tunnelState->server.len, tunnelState->server, tunnelState->client, TunnelStateData::WriteClientDone);
        }

        if (tunnelState->http.valid() && tunnelState->http->getConn() && !tunnelState->http->getConn()->inBuf.isEmpty()) {
            SBuf * const in = &tunnelState->http->getConn()->inBuf;
            debugs(26, DBG_DATA, "Tunnel client PUSH Payload: \n" << *in << "\n----------");
            tunnelState->preReadClientData.append(*in);
            in->consume(); // ConnStateData buffer accounting after the shuffle.
        }
        tunnelState->copyClientBytes();
    }
}