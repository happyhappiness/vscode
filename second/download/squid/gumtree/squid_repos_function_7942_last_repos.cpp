inline int
close(int fd)
{
    char l_so_type[sizeof(int)];
    int l_so_type_siz = sizeof(l_so_type);
    SOCKET sock = _get_osfhandle(fd);

    if (::getsockopt(sock, SOL_SOCKET, SO_TYPE, l_so_type, &l_so_type_siz) == 0) {
        int result = 0;
        if (closesocket(sock) == SOCKET_ERROR) {
            errno = WSAGetLastError();
            result = 1;
        }
        _free_osfhnd(fd);
        _osfile(fd) = 0;
        return result;
    } else
        return _close(fd);
}