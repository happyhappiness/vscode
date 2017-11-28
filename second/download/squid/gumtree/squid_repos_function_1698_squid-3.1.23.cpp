void
fd_open(int fd, unsigned int type, const char *desc)
{
    fde *F;
    assert(fd >= 0);
    F = &fd_table[fd];

    if (F->flags.open) {
        debugs(51, 1, "WARNING: Closing open FD " << std::setw(4) << fd);
        fd_close(fd);
    }

    assert(!F->flags.open);
    debugs(51, 3, "fd_open() FD " << fd << " " << desc);
    F->type = type;
    F->flags.open = 1;
    F->epoll_state = 0;
#ifdef _SQUID_MSWIN_

    F->win32.handle = _get_osfhandle(fd);

    switch (type) {

    case FD_SOCKET:

    case FD_PIPE:
        F->read_method = &socket_read_method;
        F->write_method = &socket_write_method;
        break;

    case FD_FILE:

    case FD_LOG:
        F->read_method = &file_read_method;
        F->write_method = &file_write_method;
        break;

    default:
        fatalf("fd_open(): unknown FD type - FD#: %i, type: %u, desc %s\n", fd, type, desc);
    }

#else
    F->read_method = &default_read_method;

    F->write_method = &default_write_method;

#endif

    fdUpdateBiggest(fd, 1);

    if (desc)
        xstrncpy(F->desc, desc, FD_DESC_SZ);

    Number_FD++;
}