bool
TunnelStateData::noConnections() const
{
    return !Comm::IsConnOpen(server.conn) && !Comm::IsConnOpen(client.conn);
}