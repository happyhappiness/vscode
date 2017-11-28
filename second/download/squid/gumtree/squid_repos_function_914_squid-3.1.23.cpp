int
comm_listen(int sock)
{
    int x;

    if ((x = listen(sock, Squid_MaxFD >> 2)) < 0) {
        debugs(50, 0, "comm_listen: listen(" << (Squid_MaxFD >> 2) << ", " << sock << "): " << xstrerror());
        return x;
    }

    if (Config.accept_filter && strcmp(Config.accept_filter, "none") != 0) {
#ifdef SO_ACCEPTFILTER
        struct accept_filter_arg afa;
        bzero(&afa, sizeof(afa));
        debugs(5, DBG_CRITICAL, "Installing accept filter '" << Config.accept_filter << "' on FD " << sock);
        xstrncpy(afa.af_name, Config.accept_filter, sizeof(afa.af_name));
        x = setsockopt(sock, SOL_SOCKET, SO_ACCEPTFILTER, &afa, sizeof(afa));
        if (x < 0)
            debugs(5, 0, "SO_ACCEPTFILTER '" << Config.accept_filter << "': '" << xstrerror());
#elif defined(TCP_DEFER_ACCEPT)
        int seconds = 30;
        if (strncmp(Config.accept_filter, "data=", 5) == 0)
            seconds = atoi(Config.accept_filter + 5);
        x = setsockopt(sock, IPPROTO_TCP, TCP_DEFER_ACCEPT, &seconds, sizeof(seconds));
        if (x < 0)
            debugs(5, 0, "TCP_DEFER_ACCEPT '" << Config.accept_filter << "': '" << xstrerror());
#else
        debugs(5, 0, "accept_filter not supported on your OS");
#endif
    }

    return sock;
}