unsigned short
comm_local_port(int fd)
{
    IpAddress temp;
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
        debugs(50, 1, "comm_local_port: Failed to retrieve TCP/UDP port number for socket: FD " << fd << ": " << xstrerror());
        temp.FreeAddrInfo(addr);
        return 0;
    }
    temp = *addr;

    temp.FreeAddrInfo(addr);

    F->local_addr.SetPort(temp.GetPort());

#if 0 // seems to undo comm_open actions on the FD ...
    // grab default socket information for this address
    temp.GetAddrInfo(addr);

    F->sock_family = addr->ai_family;

    temp.FreeAddrInfo(addr);
#endif

    debugs(5, 6, "comm_local_port: FD " << fd << ": port " << F->local_addr.GetPort() << "(family=" << F->sock_family << ")");
    return F->local_addr.GetPort();
}