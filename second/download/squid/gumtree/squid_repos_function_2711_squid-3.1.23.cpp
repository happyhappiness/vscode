void
TunnelStateData::Connection::closeIfOpen()
{
    if (!fd_closed(fd()))
        comm_close(fd());
}