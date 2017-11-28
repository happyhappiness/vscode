bool
IpIntercept::ProbeForTproxy(IpAddress &test)
{
    debugs(3, 3, "Detect TPROXY support on port " << test);
#if LINUX_TPROXY2

    if (Ip::EnableIpv6) {
        /* TPROXYv2 is not IPv6 capable. Force wildcard sockets to IPv4. Die on IPv6 IPs */
        debugs(3, DBG_IMPORTANT, "Disabling IPv6 on port " << test << " (TPROXYv2 interception enabled)");
        if ( test.IsIPv6() && !test.SetIPv4() ) {
            debugs(3, DBG_CRITICAL, "IPv6 requires TPROXYv4 support. You only have TPROXYv2 for " << test );
            return false;
        }
    }
    return true;

#else /* not LINUX_TPROXY2 */

#if defined(IP_TRANSPARENT)

    int tos = 1;
    int tmp_sock = -1;

    /* Probe to see if the Kernel TPROXY support is IPv6-enabled */
    if (test.IsIPv6()) {
        debugs(3, 3, "...Probing for IPv6 TPROXY support.");

        struct sockaddr_in6 tmp_ip6;
        IpAddress tmp = "::2";
        tmp.SetPort(0);
        tmp.GetSockAddr(tmp_ip6);

        if ( (tmp_sock = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP)) >= 0 &&
                setsockopt(tmp_sock, SOL_IP, IP_TRANSPARENT, (char *)&tos, sizeof(int)) == 0 &&
                bind(tmp_sock, (struct sockaddr*)&tmp_ip6, sizeof(struct sockaddr_in6)) == 0 ) {

            debugs(3, 3, "IPv6 TPROXY support detected. Using.");
            close(tmp_sock);
            return true;
        }
        if (tmp_sock >= 0) {
            close(tmp_sock);
            tmp_sock = -1;
        }
    }

    if ( test.IsIPv6() && !test.SetIPv4() ) {
        debugs(3, DBG_CRITICAL, "TPROXY lacks IPv6 support for " << test );
        return false;
    }

    /* Probe to see if the Kernel TPROXY support is IPv4-enabled (aka present) */
    if (test.IsIPv4()) {
        debugs(3, 3, "...Probing for IPv4 TPROXY support.");

        struct sockaddr_in tmp_ip4;
        IpAddress tmp = "127.0.0.2";
        tmp.SetPort(0);
        tmp.GetSockAddr(tmp_ip4);

        if ( (tmp_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) >= 0 &&
                setsockopt(tmp_sock, SOL_IP, IP_TRANSPARENT, (char *)&tos, sizeof(int)) == 0 &&
                bind(tmp_sock, (struct sockaddr*)&tmp_ip4, sizeof(struct sockaddr_in)) == 0 ) {

            debugs(3, 3, "IPv4 TPROXY support detected. Using.");
            close(tmp_sock);
            return true;
        }
        if (tmp_sock >= 0) {
            close(tmp_sock);
        }
    }

#else /* undefined IP_TRANSPARENT */
    debugs(3, 3, "setsockopt(IP_TRANSPARENT) not supported on this platform. Disabling TPROXYv4.");
#endif
#endif /* LINUX_TPROXY2 */
    return false;
}