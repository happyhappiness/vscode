bool
TunnelStateData::noConnections() const
{
    return fd_closed(server.fd()) && fd_closed(client.fd());
}