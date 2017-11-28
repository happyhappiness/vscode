static comm_err_t
commBind(int s, struct addrinfo &inaddr)
{
    statCounter.syscalls.sock.binds++;

    if (bind(s, inaddr.ai_addr, inaddr.ai_addrlen) == 0) {
        debugs(50, 6, "commBind: bind socket FD " << s << " to " << fd_table[s].local_addr);
        return COMM_OK;
    }

    debugs(50, 0, "commBind: Cannot bind socket FD " << s << " to " << fd_table[s].local_addr << ": " << xstrerror());

    return COMM_ERROR;
}