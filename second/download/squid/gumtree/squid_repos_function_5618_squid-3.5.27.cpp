Comm::Flag
Comm::DoSelect(int msec)
{
    fd_set readfds;
    fd_set pendingfds;
    fd_set writefds;

    PF *hdl = NULL;
    int fd;
    int maxfd;
    int num;
    int pending;
    int calldns = 0, calludp = 0, calltcp = 0;
    int j;
#if DEBUG_FDBITS

    int i;
#endif
    struct timeval poll_time;
    double timeout = current_dtime + (msec / 1000.0);
    fde *F;

    int no_bits;
    fd_set errfds;
    FD_ZERO(&errfds);

    do {
        double start;
        getCurrentTime();
        start = current_dtime;

        if (commCheckUdpIncoming)
            comm_select_udp_incoming();

        if (commCheckDnsIncoming)
            comm_select_dns_incoming();

        if (commCheckTcpIncoming)
            comm_select_tcp_incoming();

        calldns = calludp = calltcp = 0;

        maxfd = Biggest_FD + 1;

        memcpy(&readfds, &global_readfds, sizeof(global_readfds));

        memcpy(&writefds, &global_writefds, sizeof(global_writefds));

        memcpy(&errfds, &global_writefds, sizeof(global_writefds));

        /* remove stalled FDs, and deal with pending descriptors */
        pending = 0;

        FD_ZERO(&pendingfds);

        for (j = 0; j < (int) readfds.fd_count; ++j) {
            register int readfds_handle = readfds.fd_array[j];
            no_bits = 1;

            for ( fd = Biggest_FD; fd; --fd ) {
                if ( fd_table[fd].win32.handle == readfds_handle ) {
                    if (fd_table[fd].flags.open) {
                        no_bits = 0;
                        break;
                    }
                }
            }

            if (no_bits)
                continue;

            if (FD_ISSET(fd, &readfds) && fd_table[fd].flags.read_pending) {
                FD_SET(fd, &pendingfds);
                ++pending;
            }
        }

#if DEBUG_FDBITS
        for (i = 0; i < maxfd; ++i) {
            /* Check each open socket for a handler. */

            if (fd_table[i].read_handler) {
                assert(FD_ISSET(i, readfds));
            }

            if (fd_table[i].write_handler) {
                assert(FD_ISSET(i, writefds));
            }
        }

#endif
        if (nreadfds + nwritefds == 0) {
            assert(shutting_down);
            return Comm::SHUTDOWN;
        }

        if (msec > MAX_POLL_TIME)
            msec = MAX_POLL_TIME;

        if (pending)
            msec = 0;

        for (;;) {
            poll_time.tv_sec = msec / 1000;
            poll_time.tv_usec = (msec % 1000) * 1000;
            ++ statCounter.syscalls.selects;
            num = select(maxfd, &readfds, &writefds, &errfds, &poll_time);
            ++ statCounter.select_loops;

            if (num >= 0 || pending > 0)
                break;

            if (ignoreErrno(errno))
                break;

            debugs(5, DBG_CRITICAL, "comm_select: select failure: " << xstrerror());

            examine_select(&readfds, &writefds);

            return Comm::COMM_ERROR;

            /* NOTREACHED */
        }

        if (num < 0 && !pending)
            continue;

        getCurrentTime();

        debugs(5, num ? 5 : 8, "comm_select: " << num << "+" << pending << " FDs ready");

        statCounter.select_fds_hist.count(num);

        if (num == 0 && pending == 0)
            continue;

        /* Scan return fd masks for ready descriptors */
        assert(readfds.fd_count <= (unsigned int) Biggest_FD);
        assert(pendingfds.fd_count <= (unsigned int) Biggest_FD);

        for (j = 0; j < (int) readfds.fd_count; ++j) {
            register int readfds_handle = readfds.fd_array[j];
            register int pendingfds_handle = pendingfds.fd_array[j];
            register int osfhandle;
            no_bits = 1;

            for ( fd = Biggest_FD; fd; --fd ) {
                osfhandle = fd_table[fd].win32.handle;

                if (( osfhandle == readfds_handle ) ||
                        ( osfhandle == pendingfds_handle )) {
                    if (fd_table[fd].flags.open) {
                        no_bits = 0;
                        break;
                    }
                }
            }

            if (no_bits)
                continue;

#if DEBUG_FDBITS

            debugs(5, 9, "FD " << fd << " bit set for reading");

            assert(FD_ISSET(fd, readfds));

#endif

            if (fdIsUdpListener(fd)) {
                calludp = 1;
                continue;
            }

            if (fdIsDns(fd)) {
                calldns = 1;
                continue;
            }

            if (fdIsTcpListener(fd)) {
                calltcp = 1;
                continue;
            }

            F = &fd_table[fd];
            debugs(5, 6, "comm_select: FD " << fd << " ready for reading");

            if ((hdl = F->read_handler)) {
                F->read_handler = NULL;
                F->flags.read_pending = 0;
                commUpdateReadBits(fd, NULL);
                hdl(fd, F->read_data);
                ++ statCounter.select_fds;

                if (commCheckUdpIncoming)
                    comm_select_udp_incoming();

                if (commCheckDnsIncoming)
                    comm_select_dns_incoming();

                if (commCheckTcpIncoming)
                    comm_select_tcp_incoming();
            }
        }

        assert(errfds.fd_count <= (unsigned int) Biggest_FD);

        for (j = 0; j < (int) errfds.fd_count; ++j) {
            register int errfds_handle = errfds.fd_array[j];

            for ( fd = Biggest_FD; fd; --fd ) {
                if ( fd_table[fd].win32.handle == errfds_handle )
                    break;
            }

            if (fd_table[fd].flags.open) {
                F = &fd_table[fd];

                if ((hdl = F->write_handler)) {
                    F->write_handler = NULL;
                    commUpdateWriteBits(fd, NULL);
                    hdl(fd, F->write_data);
                    ++ statCounter.select_fds;
                }
            }
        }

        assert(writefds.fd_count <= (unsigned int) Biggest_FD);

        for (j = 0; j < (int) writefds.fd_count; ++j) {
            register int writefds_handle = writefds.fd_array[j];
            no_bits = 1;

            for ( fd = Biggest_FD; fd; --fd ) {
                if ( fd_table[fd].win32.handle == writefds_handle ) {
                    if (fd_table[fd].flags.open) {
                        no_bits = 0;
                        break;
                    }
                }
            }

            if (no_bits)
                continue;

#if DEBUG_FDBITS

            debugs(5, 9, "FD " << fd << " bit set for writing");

            assert(FD_ISSET(fd, writefds));

#endif

            if (fdIsUdpListener(fd)) {
                calludp = 1;
                continue;
            }

            if (fdIsDns(fd)) {
                calldns = 1;
                continue;
            }

            if (fdIsTcpListener(fd)) {
                calltcp = 1;
                continue;
            }

            F = &fd_table[fd];
            debugs(5, 6, "comm_select: FD " << fd << " ready for writing");

            if ((hdl = F->write_handler)) {
                F->write_handler = NULL;
                commUpdateWriteBits(fd, NULL);
                hdl(fd, F->write_data);
                ++ statCounter.select_fds;

                if (commCheckUdpIncoming)
                    comm_select_udp_incoming();

                if (commCheckDnsIncoming)
                    comm_select_dns_incoming();

                if (commCheckTcpIncoming)
                    comm_select_tcp_incoming();
            }
        }

        if (calludp)
            comm_select_udp_incoming();

        if (calldns)
            comm_select_dns_incoming();

        if (calltcp)
            comm_select_tcp_incoming();

        getCurrentTime();

        statCounter.select_time += (current_dtime - start);

        return Comm::OK;
    } while (timeout > current_dtime);
    debugs(5, 8, "comm_select: time out: " << squid_curtime);

    return Comm::TIMEOUT;
}