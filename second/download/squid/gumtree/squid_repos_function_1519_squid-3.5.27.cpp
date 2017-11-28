void
icpHandleUdp(int sock, void *data)
{
    int *N = &incoming_sockets_accepted;

    Ip::Address from;
    LOCAL_ARRAY(char, buf, SQUID_UDP_SO_RCVBUF);
    int len;
    int icp_version;
    int max = INCOMING_UDP_MAX;
    Comm::SetSelect(sock, COMM_SELECT_READ, icpHandleUdp, NULL, 0);

    while (max) {
        --max;
        len = comm_udp_recvfrom(sock,
                                buf,
                                SQUID_UDP_SO_RCVBUF - 1,
                                0,
                                from);

        if (len == 0)
            break;

        if (len < 0) {
            if (ignoreErrno(errno))
                break;

#if _SQUID_LINUX_
            /* Some Linux systems seem to set the FD for reading and then
             * return ECONNREFUSED when sendto() fails and generates an ICMP
             * port unreachable message. */
            /* or maybe an EHOSTUNREACH "No route to host" message */
            if (errno != ECONNREFUSED && errno != EHOSTUNREACH)
#endif

                debugs(50, DBG_IMPORTANT, "icpHandleUdp: FD " << sock << " recvfrom: " << xstrerror());

            break;
        }

        ++(*N);
        icpCount(buf, RECV, (size_t) len, 0);
        buf[len] = '\0';
        debugs(12, 4, "icpHandleUdp: FD " << sock << ": received " <<
               (unsigned long int)len << " bytes from " << from);

#ifdef ICP_PACKET_DUMP

        icpPktDump(buf);
#endif

        if ((size_t) len < sizeof(icp_common_t)) {
            debugs(12, 4, "icpHandleUdp: Ignoring too-small UDP packet");
            break;
        }

        icp_version = (int) buf[1]; /* cheat! */

        if (icpOutgoingConn->local == from)
            // ignore ICP packets which loop back (multicast usually)
            debugs(12, 4, "icpHandleUdp: Ignoring UDP packet sent by myself");
        else if (icp_version == ICP_VERSION_2)
            icpHandleIcpV2(sock, from, buf, len);
        else if (icp_version == ICP_VERSION_3)
            icpHandleIcpV3(sock, from, buf, len);
        else
            debugs(12, DBG_IMPORTANT, "WARNING: Unused ICP version " << icp_version <<
                   " received from " << from);
    }
}