void
commUpdateReadBits(int fd, PF * handler)
{
    if (handler && !__WSAFDIsSet(fd_table[fd].win32.handle, &global_readfds)) {
        FD_SET(fd, &global_readfds);
        nreadfds++;
    } else if (!handler && __WSAFDIsSet(fd_table[fd].win32.handle, &global_readfds)) {
        FD_CLR(fd, &global_readfds);
        nreadfds--;
    }
}