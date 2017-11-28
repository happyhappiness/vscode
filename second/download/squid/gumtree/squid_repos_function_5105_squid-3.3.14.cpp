comm_err_t
Comm::DoSelect(int msec)
{
    struct pollfd pfds[SQUID_MAXFD];

    PF *hdl = NULL;
    int fd;
    int maxfd;
    unsigned long nfds;
    unsigned long npending;
    int num;
    int calldns = 0, calludp = 0, calltcp = 0;
    double timeout = current_dtime + (msec / 1000.0);

    do {
        double start;
        getCurrentTime();
        start = current_dtime;

        if (commCheckUdpIncoming)
            comm_poll_udp_incoming();

        if (commCheckDnsIncoming)
            comm_poll_dns_incoming();

        if (commCheckTcpIncoming)
            comm_poll_tcp_incoming();

        PROF_start(comm_poll_prep_pfds);

        calldns = calludp = calltcp = 0;

        nfds = 0;

        npending = 0;

        maxfd = Biggest_FD + 1;

        for (int i = 0; i < maxfd; ++i) {
            int events;
            events = 0;
            /* Check each open socket for a handler. */

            if (fd_table[i].read_handler)
                events |= POLLRDNORM;

            if (fd_table[i].write_handler)
                events |= POLLWRNORM;

            if (events) {
                pfds[nfds].fd = i;
                pfds[nfds].events = events;
                pfds[nfds].revents = 0;
                ++nfds;

                if ((events & POLLRDNORM) && fd_table[i].flags.read_pending)
                    ++npending;
            }
        }

        PROF_stop(comm_poll_prep_pfds);

        if (npending)
            msec = 0;

        if (msec > MAX_POLL_TIME)
            msec = MAX_POLL_TIME;

        /* nothing to do
         *
         * Note that this will only ever trigger when there are no log files
         * and stdout/err/in are all closed too.
         */
        if (nfds == 0 && npending == 0) {
            if (shutting_down)
                return COMM_SHUTDOWN;
            else
                return COMM_IDLE;
        }

        for (;;) {
            PROF_start(comm_poll_normal);
            ++ statCounter.syscalls.selects;
            num = poll(pfds, nfds, msec);
            ++ statCounter.select_loops;
            PROF_stop(comm_poll_normal);

            if (num >= 0 || npending > 0)
                break;

            if (ignoreErrno(errno))
                continue;

            debugs(5, DBG_CRITICAL, "comm_poll: poll failure: " << xstrerror());

            assert(errno != EINVAL);

            return COMM_ERROR;

            /* NOTREACHED */
        }

        getCurrentTime();

        debugs(5, num ? 5 : 8, "comm_poll: " << num << "+" << npending << " FDs ready");
        statCounter.select_fds_hist.count(num);

        if (num == 0 && npending == 0)
            continue;

        /* scan each socket but the accept socket. Poll this
         * more frequently to minimize losses due to the 5 connect
         * limit in SunOS */
        PROF_start(comm_handle_ready_fd);

        for (size_t loopIndex = 0; loopIndex < nfds; ++loopIndex) {
            fde *F;
            int revents = pfds[loopIndex].revents;
            fd = pfds[loopIndex].fd;

            if (fd == -1)
                continue;

            if (fd_table[fd].flags.read_pending)
                revents |= POLLIN;

            if (revents == 0)
                continue;

            if (fdIsUdpListen(fd)) {
                calludp = 1;
                continue;
            }

            if (fdIsDns(fd)) {
                calldns = 1;
                continue;
            }

            if (fdIsTcpListen(fd)) {
                calltcp = 1;
                continue;
            }

            F = &fd_table[fd];

            if (revents & (POLLRDNORM | POLLIN | POLLHUP | POLLERR)) {
                debugs(5, 6, "comm_poll: FD " << fd << " ready for reading");

                if ((hdl = F->read_handler)) {
                    PROF_start(comm_read_handler);
                    F->read_handler = NULL;
                    F->flags.read_pending = 0;
                    hdl(fd, F->read_data);
                    PROF_stop(comm_read_handler);
                    ++ statCounter.select_fds;

                    if (commCheckUdpIncoming)
                        comm_poll_udp_incoming();

                    if (commCheckDnsIncoming)
                        comm_poll_dns_incoming();

                    if (commCheckTcpIncoming)
                        comm_poll_tcp_incoming();
                }
            }

            if (revents & (POLLWRNORM | POLLOUT | POLLHUP | POLLERR)) {
                debugs(5, 6, "comm_poll: FD " << fd << " ready for writing");

                if ((hdl = F->write_handler)) {
                    PROF_start(comm_write_handler);
                    F->write_handler = NULL;
                    hdl(fd, F->write_data);
                    PROF_stop(comm_write_handler);
                    ++ statCounter.select_fds;

                    if (commCheckUdpIncoming)
                        comm_poll_udp_incoming();

                    if (commCheckDnsIncoming)
                        comm_poll_dns_incoming();

                    if (commCheckTcpIncoming)
                        comm_poll_tcp_incoming();
                }
            }

            if (revents & POLLNVAL) {
                AsyncCall::Pointer ch;
                debugs(5, DBG_CRITICAL, "WARNING: FD " << fd << " has handlers, but it's invalid.");
                debugs(5, DBG_CRITICAL, "FD " << fd << " is a " << fdTypeStr[F->type]);
                debugs(5, DBG_CRITICAL, "--> " << F->desc);
                debugs(5, DBG_CRITICAL, "tmout:" << F->timeoutHandler << "read:" <<
                       F->read_handler << " write:" << F->write_handler);

                for (ch = F->closeHandler; ch != NULL; ch = ch->Next())
                    debugs(5, DBG_CRITICAL, " close handler: " << ch);

                if (F->closeHandler != NULL) {
                    commCallCloseHandlers(fd);
                } else if (F->timeoutHandler != NULL) {
                    debugs(5, DBG_CRITICAL, "comm_poll: Calling Timeout Handler");
                    ScheduleCallHere(F->timeoutHandler);
                }

                F->closeHandler = NULL;
                F->timeoutHandler = NULL;
                F->read_handler = NULL;
                F->write_handler = NULL;

                if (F->flags.open)
                    fd_close(fd);
            }
        }

        PROF_stop(comm_handle_ready_fd);

        if (calludp)
            comm_poll_udp_incoming();

        if (calldns)
            comm_poll_dns_incoming();

        if (calltcp)
            comm_poll_tcp_incoming();

        getCurrentTime();

        statCounter.select_time += (current_dtime - start);

        return COMM_OK;
    } while (timeout > current_dtime);

    debugs(5, 8, "comm_poll: time out: " << squid_curtime << ".");

    return COMM_TIMEOUT;
}