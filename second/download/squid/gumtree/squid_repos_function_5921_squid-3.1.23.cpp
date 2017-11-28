inline
int setsockopt(SOCKET s, int l, int o, const char * v, int n)
{
    SOCKET socket;

    socket = ((s == INVALID_SOCKET) ? s : (SOCKET)_get_osfhandle((int)s));

    if (::setsockopt(socket, l, o, v, n) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return 0;
}