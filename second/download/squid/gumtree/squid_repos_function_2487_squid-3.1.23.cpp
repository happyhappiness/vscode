void
commSetSelect(int fd, unsigned int type, PF * handler,
              void *client_data, time_t timeout)
{
    fde *F = &fd_table[fd];
    assert(fd >= 0);
    assert(F->flags.open);

    if (type & COMM_SELECT_READ) {
        kq_update_events(fd, EVFILT_READ, handler);
        F->read_handler = handler;
        F->read_data = client_data;
    }

    if (type & COMM_SELECT_WRITE) {
        kq_update_events(fd, EVFILT_WRITE, handler);
        F->write_handler = handler;
        F->write_data = client_data;
    }

    if (timeout)
        F->timeout = squid_curtime + timeout;

}