int WIN32_pipe(int handles[2])
{
    int new_socket;
    fde *F = NULL;

    Ip::Address localhost;
    Ip::Address handle0;
    Ip::Address handle1;
    struct addrinfo *AI = NULL;

    localhost.SetLocalhost();

    /* INET6: back-compatible: localhost pipes default to IPv4 unless set otherwise.
     *        it is blocked by untested helpers on many admins configs
     *        if this proves to be wrong it can die easily.
     */
    localhost.SetIPv4();

    handles[0] = handles[1] = -1;

    ++statCounter.syscalls.sock.sockets;

    handle0 = localhost;
    handle0.SetPort(0);
    handle0.GetAddrInfo(AI);

    if ((new_socket = socket(AI->ai_family, AI->ai_socktype, AI->ai_protocol)) < 0)
        return -1;

    if (bind(new_socket, AI->ai_addr, AI->ai_addrlen) < 0 ||
            listen(new_socket, 1) < 0 || getsockname(new_socket, AI->ai_addr, &(AI->ai_addrlen) ) < 0 ||
            (handles[1] = socket(AI->ai_family, AI->ai_socktype, 0)) < 0) {
        closesocket(new_socket);
        return -1;
    }

    handle0 = *AI; // retrieve the new details returned by connect()

    handle1.SetPort(handle1.GetPort());
    handle1.GetAddrInfo(AI);

    if (connect(handles[1], AI->ai_addr, AI->ai_addrlen) < 0 ||
            (handles[0] = accept(new_socket, AI->ai_addr, &(AI->ai_addrlen)) ) < 0) {
        closesocket(handles[1]);
        handles[1] = -1;
        closesocket(new_socket);
        return -1;
    }

    closesocket(new_socket);

    F = &fd_table[handles[0]];
    F->local_addr = handle0;

    F = &fd_table[handles[1]];
    F->local_addr = localhost;
    handle1.NtoA(F->ipaddr, MAX_IPSTRLEN);
    F->remote_port = handle1.GetPort();

    return 0;
}