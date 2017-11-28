const Comm::ConnectionPointer &
Ipc::ImportFdIntoComm(const Comm::ConnectionPointer &conn, int socktype, int protocol, Ipc::FdNoteId noteId)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    if (getsockname(conn->fd, reinterpret_cast<sockaddr*>(&addr), &len) == 0) {
        conn->remote = addr;
        struct addrinfo* addr_info = NULL;
        conn->remote.getAddrInfo(addr_info);
        addr_info->ai_socktype = socktype;
        addr_info->ai_protocol = protocol;
        comm_import_opened(conn, Ipc::FdNote(noteId), addr_info);
        Ip::Address::FreeAddr(addr_info);
    } else {
        debugs(54, DBG_CRITICAL, "ERROR: Ipc::ImportFdIntoComm: " << conn << ' ' << xstrerror());
        conn->close();
    }
    return conn;
}