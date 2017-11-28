void
commUnsetFdTimeout(int fd)
{
    debugs(5, 3, HERE << "Remove timeout for FD " << fd);
    assert(fd >= 0);
    assert(fd < Squid_MaxFD);
    fde *F = &fd_table[fd];
    assert(F->flags.open);

    F->timeoutHandler = NULL;
    F->timeout = 0;
}