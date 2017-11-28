int
ConnectStateData::commResetFD()
{

// XXX: do we have to check this?
//
//    if (!cbdataReferenceValid(callback.data))
//        return 0;

    statCounter.syscalls.sock.sockets++;

    fde *F = &fd_table[fd];

    struct addrinfo *AI = NULL;
    F->local_addr.GetAddrInfo(AI);
    int new_family = AI->ai_family;

    int fd2 = socket(new_family, AI->ai_socktype, AI->ai_protocol);

    if (fd2 < 0) {
        debugs(5, DBG_CRITICAL, HERE << "WARNING: FD " << fd2 << " socket failed to allocate: " << xstrerror());

        if (ENFILE == errno || EMFILE == errno)
            fdAdjustReserved();

        F->local_addr.FreeAddrInfo(AI);
        return 0;
    }

#ifdef _SQUID_MSWIN_

    /* On Windows dup2() can't work correctly on Sockets, the          */
    /* workaround is to close the destination Socket before call them. */
    close(fd);

#endif

    if (dup2(fd2, fd) < 0) {
        debugs(5, DBG_CRITICAL, HERE << "WARNING: dup2(FD " << fd2 << ", FD " << fd << ") failed: " << xstrerror());

        if (ENFILE == errno || EMFILE == errno)
            fdAdjustReserved();

        close(fd2);

        F->local_addr.FreeAddrInfo(AI);
        return 0;
    }
    commResetSelect(fd);

    close(fd2);

    debugs(50, 3, "commResetFD: Reset socket FD " << fd << "->" << fd2 << " : family=" << new_family );

    debugs(50, 3, "commResetFD: Reset socket FD " << fd << "->" << fd2 << " : family=" << new_family );

    /* INET6: copy the new sockets family type to the FDE table */
    F->sock_family = new_family;

    F->flags.called_connect = 0;

    /*
     * yuck, this has assumptions about comm_open() arguments for
     * the original socket
     */

    /* MUST be done before binding or face OS Error: "(99) Cannot assign requested address"... */
    if ( F->flags.transparent ) {
        comm_set_transparent(fd);
    }

    if (commBind(fd, *AI) != COMM_OK) {
        debugs(5, DBG_CRITICAL, "WARNING: Reset of FD " << fd << " for " << F->local_addr << " failed to bind: " << xstrerror());
        F->local_addr.FreeAddrInfo(AI);
        return 0;
    }
    F->local_addr.FreeAddrInfo(AI);

    if (F->tos)
        comm_set_tos(fd, F->tos);

    if ( Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && F->local_addr.IsIPv6() )
        comm_set_v6only(fd, 1);

    copyFDFlags(fd, F);

    return 1;
}