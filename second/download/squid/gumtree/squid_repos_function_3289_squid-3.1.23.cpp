comm_err_t
comm_select(int msec)
{
    fd_set readfds;
    fd_set pendingfds;
    fd_set writefds;

    PF *hdl = NULL;
    int fd;
    int maxfd;
    int num;
    int pending;
    int callicp = 0, callhttp = 0;
    int calldns = 0;
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

        if (commCheckICPIncoming)
            comm_select_icp_incoming();

        if (commCheckDNSIncoming)
            comm_select_dns_incoming();

        if (commCheckHTTPIncoming)
            comm_select_http_incoming();

        callicp = calldns = callhttp = 0;

        maxfd = Biggest_FD + 1;

        xmemcpy(&readfds, &global_readfds, sizeof(global_readfds));

        xmemcpy(&writefds, &global_writefds, sizeof(global_writefds));

        xmemcpy(&errfds, &global_writefds, sizeof(global_writefds));

        /* remove stalled FDs, and deal with pending descriptors */
        pending = 0;

        FD_ZERO(&pendingfds);

        for (j = 0; j < (int) readfds.fd_count; j++) {
            register int readfds_handle = readfds.fd_array[j];
            no_bits = 1;

            for ( fd = Biggest_FD; fd; fd-- ) {
                if ( fd_table[fd].win32.handle == readfds_handle ) {
                    if (fd_table[fd].flags.open) {
                        no_bits = 0;
                        break;
                    }
                }
            }

            if (no_bits)
                continue;

            if (__WSAFDIsSet(fd_table[fd].win32.handle, &readfds) && fd_table[fd].flags.read_pending) {
                FD_SET(fd, &pendingfds);
                pending++;
            }
        }

#if DEBUG_FDBITS
        for (i = 0; i < maxfd; i++) {
            /* Check each open socket for a handler. */

            if (fd_table[i].read_handler) {
                assert(__WSAFDIsSet(fd_table[i].win32.handle, readfds));
            }

            if (fd_table[i].write_handler) {
                assert(__WSAFDIsSet(fd_table[i].win32.handle, writefds));
            }
        }

#endif
        if (nreadfds + nwritefds == 0) {
            assert(shutting_down);
            return COMM_SHUTDOWN;
        }

        if (msec > MAX_POLL_TIME)
            msec = MAX_POLL_TIME;

        if (pending)
            msec = 0;

        for (;;) {
            poll_time.tv_sec = msec / 1000;
            poll_time.tv_usec = (msec % 1000) * 1000;
            ++statCounter.syscalls.selects;
            num = select(maxfd, &readfds, &writefds, &errfds, &poll_time);
            ++statCounter.select_loops;

            if (num >= 0 || pending > 0)
                break;

            if (ignoreErrno(errno))
                break;

            debugs(5, 0, "comm_select: select failure: " << xstrerror());

            examine_select(&readfds, &writefds);

            return COMM_ERROR;

            /* NOTREACHED */
        }

        if (num < 0 && !pending)
            continue;

        getCurrentTime();

        debugs(5, num ? 5 : 8, "comm_select: " << num << "+" << pending << " FDs ready");

        statHistCount(&statCounter.select_fds_hist, num);

        if (num == 0 && pending == 0)
            continue;

        /* Scan return fd masks for ready descriptors */
        assert(readfds.fd_count <= (unsigned int) Biggest_FD);
        assert(pendingfds.fd_count <= (unsigned int) Biggest_FD);

        for (j = 0; j < (int) readfds.fd_count; j++) {
            register int readfds_handle = readfds.fd_array[j];
            register int pendingfds_handle = pendingfds.fd_array[j];
            register int osfhandle;
            no_bits = 1;

            for ( fd = Biggest_FD; fd; fd-- ) {
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

            assert(__WSAFDIsSet(fd_table[fd].win32.handle, readfds));

#endif

            if (fdIsIcp(fd)) {
                callicp = 1;
                continue;
            }

            if (fdIsDns(fd)) {
                calldns = 1;
                continue;
            }

            if (fdIsHttp(fd)) {
                callhttp = 1;
                continue;
            }

            F = &fd_table[fd];
            debugs(5, 6, "comm_select: FD " << fd << " ready for reading");

            if (NULL == (hdl = F->read_handler))
                (void) 0;
            else {
                F->read_handler = NULL;
                F->flags.read_pending = 0;
                commUpdateReadBits(fd, NULL);
                hdl(fd, F->read_data);
                statCounter.select_fds++;

                if (commCheckICPIncoming)
                    comm_select_icp_incoming();

                if (commCheckDNSIncoming)
                    comm_select_dns_incoming();

                if (commCheckHTTPIncoming)
                    comm_select_http_incoming();
            }
        }

        assert(errfds.fd_count <= (unsigned int) Biggest_FD);

        for (j = 0; j < (int) errfds.fd_count; j++) {
            register int errfds_handle = errfds.fd_array[j];

            for ( fd = Biggest_FD; fd; fd-- ) {
                if ( fd_table[fd].win32.handle == errfds_handle )
                    break;
            }

            if (fd_table[fd].flags.open) {
                F = &fd_table[fd];

                if ((hdl = F->write_handler)) {
                    F->write_handler = NULL;
                    commUpdateWriteBits(fd, NULL);
                    hdl(fd, F->write_data);
                    statCounter.select_fds++;
                }
            }
        }

        assert(writefds.fd_count <= (unsigned int) Biggest_FD);

        for (j = 0; j < (int) writefds.fd_count; j++) {
            register int writefds_handle = writefds.fd_array[j];
            no_bits = 1;

            for ( fd = Biggest_FD; fd; fd-- ) {
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

            assert(__WSAFDIsSet(fd_table[fd].win32.handle, writefds));

#endif

            if (fdIsIcp(fd)) {
                callicp = 1;
                continue;
            }

            if (fdIsDns(fd)) {
                calldns = 1;
                continue;
            }

            if (fdIsHttp(fd)) {
                callhttp = 1;
                continue;
            }

            F = &fd_table[fd];
            debugs(5, 5, "comm_select: FD " << fd << " ready for writing");

            if ((hdl = F->write_handler)) {
                F->write_handler = NULL;
                commUpdateWriteBits(fd, NULL);
                hdl(fd, F->write_data);
                statCounter.select_fds++;

                if (commCheckICPIncoming)
                    comm_select_icp_incoming();

                if (commCheckDNSIncoming)
                    comm_select_dns_incoming();

                if (commCheckHTTPIncoming)
                    comm_select_http_incoming();
            }
        }

        if (callicp)
            comm_select_icp_incoming();

        if (calldns)
            comm_select_dns_incoming();

        if (callhttp)
            comm_select_http_incoming();

        getCurrentTime();

        statCounter.select_time += (current_dtime - start);

        return COMM_OK;
    } while (timeout > current_dtime);
    debugs(5, 8, "comm_select: time out: " << squid_curtime);

    return COMM_TIMEOUT;
}