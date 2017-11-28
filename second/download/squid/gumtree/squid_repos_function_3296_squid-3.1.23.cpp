void
commUpdateWriteBits(int fd, PF * handler)
{
    if (handler && !__WSAFDIsSet(fd_table[fd].win32.handle, &global_writefds)) {
        FD_SET(fd, &global_writefds);
        nwritefds++;
    } else if (!handler && __WSAFDIsSet(fd_table[fd].win32.handle, &global_writefds)) {
        FD_CLR(fd, &global_writefds);
        nwritefds--;
    }
}