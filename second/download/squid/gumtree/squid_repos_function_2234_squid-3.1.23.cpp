static void
idnsRead(int fd, void *data)
{
    int *N = &incoming_sockets_accepted;
    int len;
    int max = INCOMING_DNS_MAX;
    static char rbuf[SQUID_UDP_SO_RCVBUF];
    int ns;
    IpAddress from;

    debugs(78, 3, "idnsRead: starting with FD " << fd);

    // Always keep reading. This stops (or at least makes harder) several
    // attacks on the DNS client.
    commSetSelect(fd, COMM_SELECT_READ, idnsRead, NULL, 0);

    /* BUG (UNRESOLVED)
     *  two code lines after returning from comm_udprecvfrom()
     *  something overwrites the memory behind the from parameter.
     *  NO matter where in the stack declaration list above it is placed
     *  The cause of this is still unknown, however copying the data appears
     *  to allow it to be passed further without this erasure.
     */
    IpAddress bugbypass;

    while (max--) {
        len = comm_udp_recvfrom(fd, rbuf, SQUID_UDP_SO_RCVBUF, 0, bugbypass);

        from = bugbypass; // BUG BYPASS. see notes above.

        if (len == 0)
            break;

        if (len < 0) {
            if (ignoreErrno(errno))
                break;

#ifdef _SQUID_LINUX_
            /* Some Linux systems seem to set the FD for reading and then
             * return ECONNREFUSED when sendto() fails and generates an ICMP
             * port unreachable message. */
            /* or maybe an EHOSTUNREACH "No route to host" message */
            if (errno != ECONNREFUSED && errno != EHOSTUNREACH)
#endif

                debugs(50, 1, "idnsRead: FD " << fd << " recvfrom: " << xstrerror());

            break;
        }

        fd_bytes(fd, len, FD_READ);

        assert(N);
        (*N)++;

        debugs(78, 3, "idnsRead: FD " << fd << ": received " << len << " bytes from " << from);

        /* BUG: see above. Its here that it becomes apparent that the content of bugbypass is gone. */
        ns = idnsFromKnownNameserver(from);

        if (ns >= 0) {
            nameservers[ns].nreplies++;
        }

        // Before unknown_nameservers check to avoid flooding cache.log on attacks,
        // but after the ++ above to keep statistics right.
        if (!lru_list.head)
            continue; // Don't process replies if there is no pending query.

        if (ns < 0 && Config.onoff.ignore_unknown_nameservers) {
            static time_t last_warning = 0;

            if (squid_curtime - last_warning > 60) {
                debugs(78, 1, "WARNING: Reply from unknown nameserver " << from);
                last_warning = squid_curtime;
            } else {
                debugs(78, 1, "WARNING: Reply from unknown nameserver " << from << " (retrying..." <<  (squid_curtime-last_warning) << "<=60)" );
            }
            continue;
        }

        idnsGrokReply(rbuf, len);
    }
}