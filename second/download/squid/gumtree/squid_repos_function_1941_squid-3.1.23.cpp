comm_err_t
comm_select(int msec)
{
    int num, i;
    fde *F;
    PF *hdl;

    PROF_start(comm_check_incoming);

    if (msec > max_poll_time)
        msec = max_poll_time;

    for (;;) {
        do_poll.dp_timeout = msec;
        do_poll.dp_nfds = dpoll_nfds;

        comm_flush_updates(); /* ensure latest changes are sent to /dev/poll */

        num = ioctl(devpoll_fd, DP_POLL, &do_poll);
        ++statCounter.select_loops;

        if (num >= 0)
            break; /* no error, skip out of loop */

        if (ignoreErrno(errno))
            break; /* error is one we may ignore, skip out of loop */

        /* error during poll */
        getCurrentTime();
        PROF_stop(comm_check_incoming);
        return COMM_ERROR;
    }

    PROF_stop(comm_check_incoming);
    getCurrentTime();

    statHistCount(&statCounter.select_fds_hist, num);

    if (num == 0)
        return COMM_TIMEOUT; /* no error */

    PROF_start(comm_handle_ready_fd);

    for (i = 0; i < num; i++) {
        int fd = (int)do_poll.dp_fds[i].fd;
        F = &fd_table[fd];
        debugs(
            5,
            DEBUG_DEVPOLL ? 0 : 8,
            HERE << "got FD " << fd
            << ",events=" << std::hex << do_poll.dp_fds[i].revents
            << ",monitoring=" << devpoll_state[fd].state
            << ",F->read_handler=" << F->read_handler
            << ",F->write_handler=" << F->write_handler
        );

        /* handle errors */
        if (do_poll.dp_fds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
            debugs(
                5,
                DEBUG_DEVPOLL ? 0 : 8,
                HERE << "devpoll event error: fd " << fd
            );
            continue;
        }

        /* check if file descriptor has data to read */
        if (do_poll.dp_fds[i].revents & POLLIN || F->flags.read_pending) {
            if ( (hdl = F->read_handler) != NULL ) {
                debugs(
                    5,
                    DEBUG_DEVPOLL ? 0 : 8,
                    HERE << "Calling read handler on FD " << fd
                );
                PROF_start(comm_read_handler);
                F->flags.read_pending = 0;
                F->read_handler = NULL;
                hdl(fd, F->read_data);
                PROF_stop(comm_read_handler);
                statCounter.select_fds++;
            } else {
                debugs(
                    5,
                    DEBUG_DEVPOLL ? 0 : 8,
                    HERE << "no read handler for FD " << fd
                );
                // remove interest since no handler exist for this event.
                commSetSelect(fd, COMM_SELECT_READ, NULL, NULL, 0);
            }
        }

        /* check if file descriptor is ready to write */
        if (do_poll.dp_fds[i].revents & POLLOUT) {
            if ((hdl = F->write_handler) != NULL) {
                debugs(
                    5,
                    DEBUG_DEVPOLL ? 0 : 8,
                    HERE << "Calling write handler on FD " << fd
                );
                PROF_start(comm_write_handler);
                F->write_handler = NULL;
                hdl(fd, F->write_data);
                PROF_stop(comm_write_handler);
                statCounter.select_fds++;
            } else {
                debugs(
                    5,
                    DEBUG_DEVPOLL ? 0 : 8,
                    HERE << "no write handler for FD " << fd
                );
                // remove interest since no handler exist for this event.
                commSetSelect(fd, COMM_SELECT_WRITE, NULL, NULL, 0);
            }
        }
    }

    PROF_stop(comm_handle_ready_fd);
    return COMM_OK;
}