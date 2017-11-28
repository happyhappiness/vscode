
    if (keepGoingAfterRead(len, errcode, xerrno, server, client))
        handleConnectResponse(len);
}

void
TunnelStateData::informUserOfPeerError(const char *errMsg)
{
    server.len = 0;
    if (!clientExpectsConnectResponse()) {
        // closing the connection is the best we can do here
        debugs(50, 3, server.conn << " closing on error: " << errMsg);
        server.conn->close();
        return;
    }
    ErrorState *err  = new ErrorState(ERR_CONNECT_FAIL, Http::scBadGateway, request.getRaw());
    err->callback = tunnelErrorComplete;
    err->callback_data = this;
    *status_ptr = Http::scBadGateway;
    errorSend(http->getConn()->clientConnection, err);
}

/* Read from client side and queue it for writing to the server */
void
TunnelStateData::ReadConnectResponseDone(const Comm::ConnectionPointer &, char *buf, size_t len, comm_err_t errcode, int xerrno, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    assert (cbdataReferenceValid (tunnelState));

    tunnelState->readConnectResponseDone(buf, len, errcode, xerrno);
}
