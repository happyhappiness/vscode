bool
Ip::Intercept::ProbeForTproxy(Ip::Address &test)
{
    bool doneSuid = false;

#if _SQUID_LINUX_ && defined(IP_TRANSPARENT) // Linux
# define soLevel SOL_IP
# define soFlag  IP_TRANSPARENT

#elif defined(SO_BINDANY) // OpenBSD 4.7+ and NetBSD with PF
# define soLevel SOL_SOCKET
# define soFlag  SO_BINDANY
    enter_suid();
    doneSuid = true;

#elif defined(IP_BINDANY) // FreeBSD with IPFW
# define soLevel IPPROTO_IP
# define soFlag  IP_BINDANY
    enter_suid();
    doneSuid = true;

#endif

#if defined(soLevel) && defined(soFlag)

    debugs(3, 3, "Detect TPROXY support on port " << test);

    int tos = 1;
    int tmp_sock = -1;

    /* Probe to see if the Kernel TPROXY support is IPv6-enabled */
    if (test.isIPv6()) {
        debugs(3, 3, "...Probing for IPv6 TPROXY support.");

        struct sockaddr_in6 tmp_ip6;
        Ip::Address tmp = "::2";
        tmp.port(0);
        tmp.getSockAddr(tmp_ip6);

        if ( (tmp_sock = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP)) >= 0 &&
                setsockopt(tmp_sock, soLevel, soFlag, (char *)&tos, sizeof(int)) == 0 &&
                bind(tmp_sock, (struct sockaddr*)&tmp_ip6, sizeof(struct sockaddr_in6)) == 0 ) {

            debugs(3, 3, "IPv6 TPROXY support detected. Using.");
            close(tmp_sock);
            if (doneSuid)
                leave_suid();
            return true;
        }
        if (tmp_sock >= 0) {
            close(tmp_sock);
            tmp_sock = -1;
        }
    }

    if ( test.isIPv6() && !test.setIPv4() ) {
        debugs(3, DBG_CRITICAL, "TPROXY lacks IPv6 support for " << test );
        if (doneSuid)
            leave_suid();
        return false;
    }

    /* Probe to see if the Kernel TPROXY support is IPv4-enabled (aka present) */
    if (test.isIPv4()) {
        debugs(3, 3, "...Probing for IPv4 TPROXY support.");

        struct sockaddr_in tmp_ip4;
        Ip::Address tmp = "127.0.0.2";
        tmp.port(0);
        tmp.getSockAddr(tmp_ip4);

        if ( (tmp_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) >= 0 &&
                setsockopt(tmp_sock, soLevel, soFlag, (char *)&tos, sizeof(int)) == 0 &&
                bind(tmp_sock, (struct sockaddr*)&tmp_ip4, sizeof(struct sockaddr_in)) == 0 ) {

            debugs(3, 3, "IPv4 TPROXY support detected. Using.");
            close(tmp_sock);
            if (doneSuid)
                leave_suid();
            return true;
        }
        if (tmp_sock >= 0) {
            close(tmp_sock);
        }
    }

#else
    debugs(3, 3, "TPROXY setsockopt() not supported on this platform. Disabling TPROXY.");

#endif
    if (doneSuid)
        leave_suid();
    return false;
}