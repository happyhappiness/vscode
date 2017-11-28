static Comm::Flag
commBind(int s, struct addrinfo &inaddr)
{
    ++ statCounter.syscalls.sock.binds;

    if (bind(s, inaddr.ai_addr, inaddr.ai_addrlen) == 0) {
        debugs(50, 6, "bind socket FD " << s << " to " << fd_table[s].local_addr);
        return Comm::OK;
    }
    int xerrno = errno;
    debugs(50, DBG_CRITICAL, MYNAME << "Cannot bind socket FD " << s << " to " << fd_table[s].local_addr << ": " << xstrerr(xerrno));

    return Comm::COMM_ERROR;
}