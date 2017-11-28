static void
clientHttpConnectionsOpen(void)
{
    http_port_list *s = NULL;
    int fd = -1;
#if USE_SSL
    int bumpCount = 0; // counts http_ports with sslBump option
#endif

    for (s = Config.Sockaddr.http; s; s = s->next) {
        if (MAXHTTPPORTS == NHttpSockets) {
            debugs(1, 1, "WARNING: You have too many 'http_port' lines.");
            debugs(1, 1, "         The limit is " << MAXHTTPPORTS);
            continue;
        }

#if USE_SSL
        if (s->sslBump &&
                !s->staticSslContext && !s->generateHostCertificates) {
            debugs(1, 1, "Will not bump SSL at http_port " <<
                   s->http.s << " due to SSL initialization failure.");
            s->sslBump = 0;
        }
        if (s->sslBump) {
            ++bumpCount;
            // Create ssl_ctx cache for this port.
            Ssl::TheGlobalContextStorage.addLocalStorage(s->s, s->dynamicCertMemCacheSize == std::numeric_limits<size_t>::max() ? 4194304 : s->dynamicCertMemCacheSize);
        }
#endif
#if USE_SSL_CRTD
        Ssl::Helper::GetInstance();
#endif //USE_SSL_CRTD

        enter_suid();

        if (s->spoof_client_ip) {
            fd = comm_open_listener(SOCK_STREAM, IPPROTO_TCP, s->s, (COMM_NONBLOCKING|COMM_TRANSPARENT), "HTTP Socket");
        } else {
            fd = comm_open_listener(SOCK_STREAM, IPPROTO_TCP, s->s, COMM_NONBLOCKING, "HTTP Socket");
        }

        leave_suid();

        if (fd < 0)
            continue;

        comm_listen(fd);

        comm_accept(fd, httpAccept, s);

        debugs(1, 1, "Accepting " <<
               (s->intercepted ? " intercepted" : "") <<
               (s->spoof_client_ip ? " spoofing" : "") <<
               (s->sslBump ? " bumpy" : "") <<
               (s->accel ? " accelerated" : "")
               << " HTTP connections at " << s->s
               << ", FD " << fd << "." );

        HttpSockets[NHttpSockets++] = fd;
    }

#if USE_SSL
    if (bumpCount && !Config.accessList.ssl_bump)
        debugs(33, 1, "WARNING: http_port(s) with SslBump found, but no " <<
               std::endl << "\tssl_bump ACL configured. No requests will be " <<
               "bumped.");
#endif
}