void
TunnelStateData::connectedToPeer(Ssl::PeerConnectorAnswer &answer)
{
    if (ErrorState *error = answer.error.get()) {
        *status_ptr = error->httpStatus;
        error->callback = tunnelErrorComplete;
        error->callback_data = this;
        errorSend(client.conn, error);
        answer.error.clear(); // preserve error for errorSendComplete()
        return;
    }

    tunnelRelayConnectRequest(server.conn, this);
}