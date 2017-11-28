int
IcmpPinger::Open(void)
{
#if _SQUID_WINDOWS_

    WSADATA wsaData;
    WSAPROTOCOL_INFO wpi;
    char buf[sizeof(wpi)];
    int x;

    struct sockaddr_in PS;

    WSAStartup(2, &wsaData);
    atexit(Win32SockCleanup);

    getCurrentTime();
    _db_init(NULL, "ALL,1");
    setmode(0, O_BINARY);
    setmode(1, O_BINARY);
    x = read(0, buf, sizeof(wpi));

    if (x < (int)sizeof(wpi)) {
        getCurrentTime();
        debugs(42, DBG_CRITICAL, HERE << "read: FD 0: " << xstrerror());
        write(1, "ERR\n", 4);
        return -1;
    }

    memcpy(&wpi, buf, sizeof(wpi));

    write(1, "OK\n", 3);
    x = read(0, buf, sizeof(PS));

    if (x < (int)sizeof(PS)) {
        getCurrentTime();
        debugs(42, DBG_CRITICAL, HERE << "read: FD 0: " << xstrerror());
        write(1, "ERR\n", 4);
        return -1;
    }

    memcpy(&PS, buf, sizeof(PS));

    icmp_sock = WSASocket(FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO, &wpi, 0, 0);

    if (icmp_sock == -1) {
        getCurrentTime();
        debugs(42, DBG_CRITICAL, HERE << "WSASocket: " << xstrerror());
        write(1, "ERR\n", 4);
        return -1;
    }

    x = connect(icmp_sock, (struct sockaddr *) &PS, sizeof(PS));

    if (SOCKET_ERROR == x) {
        getCurrentTime();
        debugs(42, DBG_CRITICAL, HERE << "connect: " << xstrerror());
        write(1, "ERR\n", 4);
        return -1;
    }

    write(1, "OK\n", 3);
    memset(buf, 0, sizeof(buf));
    x = recv(icmp_sock, (void *) buf, sizeof(buf), 0);

    if (x < 3) {
        debugs(42, DBG_CRITICAL, HERE << "recv: " << xstrerror());
        return -1;
    }

    x = send(icmp_sock, (const void *) buf, strlen(buf), 0);

    if (x < 3 || strncmp("OK\n", buf, 3)) {
        debugs(42, DBG_CRITICAL, HERE << "recv: " << xstrerror());
        return -1;
    }

    getCurrentTime();
    debugs(42, DBG_IMPORTANT, "pinger: Squid socket opened");

    /* windows uses a socket stream as a dual-direction channel */
    socket_to_squid = icmp_sock;
    socket_from_squid = icmp_sock;

    return icmp_sock;

#else /* !_SQUID_WINDOWS_ */

    /* non-windows apps use stdin/out pipes as the squid channel(s) */
    socket_from_squid = 0; // use STDIN macro ??
    socket_to_squid = 1; // use STDOUT macro ??
    return socket_to_squid;
#endif
}