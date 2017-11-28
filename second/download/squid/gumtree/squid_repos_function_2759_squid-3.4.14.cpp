void
TunnelStateData::Connection::closeIfOpen()
{
    if (Comm::IsConnOpen(conn))
        conn->close();
}