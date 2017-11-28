unsigned short
comm_local_port(int fd)
{
    Ip::Address temp;
    struct addrinfo *addr = NULL;
    fde *F = &fd_table[fd];

    /* If the fd is closed already, just return */

    if (!F->flags.open) {
        debugs(5, 0, "comm_local_port: FD " << fd << " has been closed.");
        return 0;
    }

    if (F->local_addr.GetPort())
        return F->local_addr.GetPort();

    if (F->sock_family == AF_INET)
        temp.SetIPv4();

    temp.InitAddrInfo(addr);

    if (getsockname(fd, addr->ai_addr, &(addr->ai_addrlen)) ) {
        debugs(50, DBG_IMPORTANT, "comm_local_port: Failed to retrieve TCP/UDP port number for socket: FD " << fd << ": " << xstrerror());
        temp.FreeAddrInfo(addr);
        return 0;
    }
    temp = *addr;

    temp.FreeAddrInfo(addr);

    if (F->local_addr.IsAnyAddr()) {
        /* save the whole local address, not just the port. */
        F->local_addr = temp;
    } else {
        F->local_addr.SetPort(temp.GetPort());
    }

    debugs(5, 6, "comm_local_port: FD " << fd << ": port " << F->local_addr.GetPort() << "(family=" << F->sock_family << ")");
    return F->local_addr.GetPort();
}