void
commResetSelect(int fd)
{
    fde *F = &fd_table[fd];
    if (F->read_handler) {
        kq_update_events(fd, EVFILT_READ, (PF *)1);
    }
    if (F->write_handler) {
        kq_update_events(fd, EVFILT_WRITE, (PF *)1);
    }
}