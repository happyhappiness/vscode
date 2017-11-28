static void
clientHttpsConnectionsOpen(void)
{
    https_port_list *s;
    int fd;

    for (s = Config.Sockaddr.https; s; s = (https_port_list *)s->http.next) {
        if (MAXHTTPPORTS == NHttpSockets) {
            debugs(1, 1, "Ignoring 'https_port' lines exceeding the limit.");
            debugs(1, 1, "The limit is " << MAXHTTPPORTS << " HTTPS ports.");
            continue;
        }

        if (!s->staticSslContext) {
            debugs(1, 1, "Ignoring https_port " << s->http.s <<
                   " due to SSL initialization failure.");
            continue;
        }

        enter_suid();
        fd = comm_open_listener(SOCK_STREAM,
                                IPPROTO_TCP,
                                s->http.s,
                                COMM_NONBLOCKING, "HTTPS Socket");
        leave_suid();

        if (fd < 0)
            continue;

        comm_listen(fd);

        comm_accept(fd, httpsAccept, s);

        debugs(1, 1, "Accepting HTTPS connections at " << s->http.s << ", FD " << fd << ".");

        HttpSockets[NHttpSockets++] = fd;
    }
}