void
Comm::ConnOpener::lookupLocalAddress()
{
    struct addrinfo *addr = NULL;
    Ip::Address::InitAddr(addr);

    if (getsockname(conn_->fd, addr->ai_addr, &(addr->ai_addrlen)) != 0) {
        debugs(50, DBG_IMPORTANT, "ERROR: Failed to retrieve TCP/UDP details for socket: " << conn_ << ": " << xstrerror());
        Ip::Address::FreeAddr(addr);
        return;
    }

    conn_->local = *addr;
    Ip::Address::FreeAddr(addr);
    debugs(5, 6, HERE << conn_);
}