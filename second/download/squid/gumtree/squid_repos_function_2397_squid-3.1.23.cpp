void
FwdState::unregister(int fd)
{
    debugs(17, 3, HERE << entry->url()  );
    assert(fd == server_fd);
    assert(fd > -1);
    comm_remove_close_handler(fd, fwdServerClosedWrapper, this);
    server_fd = -1;
}