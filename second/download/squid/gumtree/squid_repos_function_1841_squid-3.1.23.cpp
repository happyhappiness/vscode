static int
comm_check_incoming_select_handlers(int nfds, int *fds)
{
    int i;
    int fd;
    int maxfd = 0;
    PF *hdl = NULL;
    fd_set read_mask;
    fd_set write_mask;
    FD_ZERO(&read_mask);
    FD_ZERO(&write_mask);
    incoming_sockets_accepted = 0;

    for (i = 0; i < nfds; i++) {
        fd = fds[i];

        if (fd_table[fd].read_handler) {
            FD_SET(fd, &read_mask);

            if (fd > maxfd)
                maxfd = fd;
        }

        if (fd_table[fd].write_handler) {
            FD_SET(fd, &write_mask);

            if (fd > maxfd)
                maxfd = fd;
        }
    }

    if (maxfd++ == 0)
        return -1;

    getCurrentTime();

    statCounter.syscalls.selects++;

    if (select(maxfd, &read_mask, &write_mask, NULL, &zero_tv) < 1)
        return incoming_sockets_accepted;

    for (i = 0; i < nfds; i++) {
        fd = fds[i];

        if (FD_ISSET(fd, &read_mask)) {
            if ((hdl = fd_table[fd].read_handler) != NULL) {
                fd_table[fd].read_handler = NULL;
                commUpdateReadBits(fd, NULL);
                hdl(fd, fd_table[fd].read_data);
            } else {
                debugs(5, 1, "comm_select_incoming: FD " << fd << " NULL read handler");
            }
        }

        if (FD_ISSET(fd, &write_mask)) {
            if ((hdl = fd_table[fd].write_handler) != NULL) {
                fd_table[fd].write_handler = NULL;
                commUpdateWriteBits(fd, NULL);
                hdl(fd, fd_table[fd].write_data);
            } else {
                debugs(5, 1, "comm_select_incoming: FD " << fd << " NULL write handler");
            }
        }
    }

    return incoming_sockets_accepted;
}