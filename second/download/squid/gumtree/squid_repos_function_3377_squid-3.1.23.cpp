int Win32__WSAFDIsSet(int fd, fd_set FAR * set
                     )
{
    fde *F = &fd_table[fd];
    SOCKET s = F->win32.handle;

    return __WSAFDIsSet(s, set);
}