void
FtpChannel::opened(int aFd, const AsyncCall::Pointer &aCloser)
{
    assert(fd < 0);
    assert(closer == NULL);

    assert(aFd >= 0);
    assert(aCloser != NULL);

    fd = aFd;
    closer = aCloser;
    comm_add_close_handler(fd, closer);
}