int
main(int argc, char *argv[])
{
    fd_set R;
    int x;
    int max_fd = 0;

    struct timeval tv;
    const char *debug_args = "ALL,10";
    char *t;
    time_t last_check_time = 0;

    /*
     * cevans - do this first. It grabs a raw socket. After this we can
     * drop privs
     */
    int icmp4_worker = -1;
    int icmp6_worker = -1;
    int squid_link = -1;

    /** start by initializing the pinger debug cache.log-pinger. */
    if ((t = getenv("SQUID_DEBUG")))
        debug_args = xstrdup(t);

    getCurrentTime();

    // determine IPv4 or IPv6 capabilities before using sockets.
    Ip::ProbeTransport();

    _db_init(NULL, debug_args);

    debugs(42, DBG_CRITICAL, "pinger: Initialising ICMP pinger ...");

    icmp4_worker = icmp4.Open();
    if (icmp4_worker < 0) {
        debugs(42, DBG_CRITICAL, "pinger: Unable to start ICMP pinger.");
    }
    max_fd = max(max_fd, icmp4_worker);

#if USE_IPV6
    icmp6_worker = icmp6.Open();
    if (icmp6_worker <0 ) {
        debugs(42, DBG_CRITICAL, "pinger: Unable to start ICMPv6 pinger.");
    }
    max_fd = max(max_fd, icmp6_worker);
#endif

    /** abort if neither worker could open a socket. */
    if (icmp4_worker < 0 && icmp6_worker < 0) {
        debugs(42, DBG_CRITICAL, "FATAL: pinger: Unable to open any ICMP sockets.");
        exit(1);
    }

    if ( (squid_link = control.Open()) < 0) {
        debugs(42, DBG_CRITICAL, "FATAL: pinger: Unable to setup Pinger control sockets.");
        icmp4.Close();
        icmp6.Close();
        exit(1); // fatal error if the control channel fails.
    }
    max_fd = max(max_fd, squid_link);

    if (setgid(getgid()) < 0) {
        int xerrno = errno;
        debugs(42, DBG_CRITICAL, "FATAL: pinger: setgid(" << getgid() << ") failed: " << xstrerr(xerrno));
        icmp4.Close();
        icmp6.Close();
        exit (1);
    }
    if (setuid(getuid()) < 0) {
        int xerrno = errno;
        debugs(42, DBG_CRITICAL, "FATAL: pinger: setuid(" << getuid() << ") failed: " << xstrerr(xerrno));
        icmp4.Close();
        icmp6.Close();
        exit (1);
    }

#if USE_LIBCAP
    // Drop remaining capabilities (if installed as non-setuid setcap cap_net_raw=ep).
    // If pinger binary was installed setuid root, setuid() above already dropped all
    // capabilities, and this is no-op.
    cap_t caps;
    caps = cap_init();
    if (!caps) {
        int xerrno = errno;
        debugs(42, DBG_CRITICAL, "FATAL: pinger: cap_init() failed: " << xstrerr(xerrno));
        icmp4.Close();
        icmp6.Close();
        exit (1);
    } else {
        if (cap_set_proc(caps) != 0) {
            int xerrno = errno;
            // cap_set_proc(cap_init()) is expected to never fail
            debugs(42, DBG_CRITICAL, "FATAL: pinger: cap_set_proc(none) failed: " << xstrerr(xerrno));
            cap_free(caps);
            icmp4.Close();
            icmp6.Close();
            exit (1);
        }
        cap_free(caps);
    }
#endif

    last_check_time = squid_curtime;

    for (;;) {
        tv.tv_sec = PINGER_TIMEOUT;
        tv.tv_usec = 0;
        FD_ZERO(&R);
        if (icmp4_worker >= 0) {
            FD_SET(icmp4_worker, &R);
        }
        if (icmp6_worker >= 0) {
            FD_SET(icmp6_worker, &R);
        }

        FD_SET(squid_link, &R);
        x = select(max_fd+1, &R, NULL, NULL, &tv);
        getCurrentTime();

        if (x < 0) {
            int xerrno = errno;
            debugs(42, DBG_CRITICAL, HERE << " FATAL Shutdown. select()==" << x << ", ERR: " << xstrerr(xerrno));
            control.Close();
            exit(1);
        }

        if (FD_ISSET(squid_link, &R)) {
            control.Recv();
        }

        if (icmp6_worker >= 0 && FD_ISSET(icmp6_worker, &R)) {
            icmp6.Recv();
        }
        if (icmp4_worker >= 0 && FD_ISSET(icmp4_worker, &R)) {
            icmp4.Recv();
        }

        if (PINGER_TIMEOUT + last_check_time < squid_curtime) {
            if (send(LINK_TO_SQUID, &tv, 0, 0) < 0) {
                debugs(42, DBG_CRITICAL, "pinger: Closing. No requests in last " << PINGER_TIMEOUT << " seconds.");
                control.Close();
                exit(1);
            }

            last_check_time = squid_curtime;
        }
    }

    /* NOTREACHED */
    return 0;
}