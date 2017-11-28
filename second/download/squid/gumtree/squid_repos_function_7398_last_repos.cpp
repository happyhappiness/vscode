void
Security::PeerConnector::noteWantWrite()
{
    const int fd = serverConnection()->fd;
    debugs(83, 5, serverConnection());
    Comm::SetSelect(fd, COMM_SELECT_WRITE, &NegotiateSsl, this, 0);
    return;
}