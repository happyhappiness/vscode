void
FwdState::unregister(int fd)
{
    debugs(17, 3, HERE << entry->url() );
    assert(fd == serverConnection()->fd);
    unregister(serverConn);
}