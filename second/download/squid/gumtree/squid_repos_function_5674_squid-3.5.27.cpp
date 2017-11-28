static int
comm_check_incoming_poll_handlers(int nfds, int *fds)
{
    int i;
    int fd;
    PF *hdl = NULL;
    int npfds;

    struct pollfd pfds[3 + MAXTCPLISTENPORTS];
    PROF_start(comm_check_incoming);
    incoming_sockets_accepted = 0;

    for (i = npfds = 0; i < nfds; ++i) {
        int events;
        fd = fds[i];
        events = 0;

        if (fd_table[fd].read_handler)
            events |= POLLRDNORM;

        if (fd_table[fd].write_handler)
            events |= POLLWRNORM;

        if (events) {
            pfds[npfds].fd = fd;
            pfds[npfds].events = events;
            pfds[npfds].revents = 0;
            ++npfds;
        }
    }

    if (!nfds) {
        PROF_stop(comm_check_incoming);
        return -1;
    }

    getCurrentTime();
    ++ statCounter.syscalls.selects;

    if (poll(pfds, npfds, 0) < 1) {
        PROF_stop(comm_check_incoming);
        return incoming_sockets_accepted;
    }

    for (i = 0; i < npfds; ++i) {
        int revents;

        if (((revents = pfds[i].revents) == 0) || ((fd = pfds[i].fd) == -1))
            continue;

        if (revents & (POLLRDNORM | POLLIN | POLLHUP | POLLERR)) {
            if ((hdl = fd_table[fd].read_handler)) {
                fd_table[fd].read_handler = NULL;
                hdl(fd, fd_table[fd].read_data);
            } else if (pfds[i].events & POLLRDNORM)
                debugs(5, DBG_IMPORTANT, "comm_poll_incoming: FD " << fd << " NULL read handler");
        }

        if (revents & (POLLWRNORM | POLLOUT | POLLHUP | POLLERR)) {
            if ((hdl = fd_table[fd].write_handler)) {
                fd_table[fd].write_handler = NULL;
                hdl(fd, fd_table[fd].write_data);
            } else if (pfds[i].events & POLLWRNORM)
                debugs(5, DBG_IMPORTANT, "comm_poll_incoming: FD " << fd << " NULL write_handler");
        }
    }

    PROF_stop(comm_check_incoming);
    return incoming_sockets_accepted;
}