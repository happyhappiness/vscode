comm_err_t
comm_select(int msec)
{
    int num, i,fd;
    fde *F;
    PF *hdl;

    struct epoll_event *cevents;

    PROF_start(comm_check_incoming);

    if (msec > max_poll_time)
        msec = max_poll_time;

    for (;;) {
        num = epoll_wait(kdpfd, pevents, SQUID_MAXFD, msec);
        ++statCounter.select_loops;

        if (num >= 0)
            break;

        if (ignoreErrno(errno))
            break;

        getCurrentTime();

        PROF_stop(comm_check_incoming);

        return COMM_ERROR;
    }

    PROF_stop(comm_check_incoming);
    getCurrentTime();

    statHistCount(&statCounter.select_fds_hist, num);

    if (num == 0)
        return COMM_TIMEOUT;		/* No error.. */

    PROF_start(comm_handle_ready_fd);

    for (i = 0, cevents = pevents; i < num; i++, cevents++) {
        fd = cevents->data.fd;
        F = &fd_table[fd];
        debugs(5, DEBUG_EPOLL ? 0 : 8, "comm_select(): got FD " << fd << " events=" <<
               std::hex << cevents->events << " monitoring=" << F->epoll_state <<
               " F->read_handler=" << F->read_handler << " F->write_handler=" << F->write_handler);

        // TODO: add EPOLLPRI??

        if (cevents->events & (EPOLLIN|EPOLLHUP|EPOLLERR) || F->flags.read_pending) {
            if ((hdl = F->read_handler) != NULL) {
                debugs(5, DEBUG_EPOLL ? 0 : 8, "comm_select(): Calling read handler on FD " << fd);
                PROF_start(comm_write_handler);
                F->flags.read_pending = 0;
                F->read_handler = NULL;
                hdl(fd, F->read_data);
                PROF_stop(comm_write_handler);
                statCounter.select_fds++;
            } else {
                debugs(5, DEBUG_EPOLL ? 0 : 8, "comm_select(): no read handler for FD " << fd);
                // remove interest since no handler exist for this event.
                commSetSelect(fd, COMM_SELECT_READ, NULL, NULL, 0);
            }
        }

        if (cevents->events & (EPOLLOUT|EPOLLHUP|EPOLLERR)) {
            if ((hdl = F->write_handler) != NULL) {
                debugs(5, DEBUG_EPOLL ? 0 : 8, "comm_select(): Calling write handler on FD " << fd);
                PROF_start(comm_read_handler);
                F->write_handler = NULL;
                hdl(fd, F->write_data);
                PROF_stop(comm_read_handler);
                statCounter.select_fds++;
            } else {
                debugs(5, DEBUG_EPOLL ? 0 : 8, "comm_select(): no write handler for FD " << fd);
                // remove interest since no handler exist for this event.
                commSetSelect(fd, COMM_SELECT_WRITE, NULL, NULL, 0);
            }
        }
    }

    PROF_stop(comm_handle_ready_fd);

    return COMM_OK;
}