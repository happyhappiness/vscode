void
FwdState::serverClosed(int fd)
{
    debugs(17, 2, "fwdServerClosed: FD " << fd << " " << entry->url());
    assert(server_fd == fd);
    server_fd = -1;

    retryOrBail();
}