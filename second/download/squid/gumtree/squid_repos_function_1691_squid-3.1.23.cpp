void
fd_close(int fd)
{
    fde *F = &fd_table[fd];

    if (F->type == FD_FILE) {
        assert(F->read_handler == NULL);
        assert(F->write_handler == NULL);
    }

    debugs(51, 3, "fd_close FD " << fd << " " << F->desc);
    commSetSelect(fd, COMM_SELECT_READ, NULL, NULL, 0);
    commSetSelect(fd, COMM_SELECT_WRITE, NULL, NULL, 0);
    F->flags.open = 0;
    fdUpdateBiggest(fd, 0);
    Number_FD--;
    *F = fde();
}