inline int
ioctlsocket(int s, long c, u_long FAR * a)
{
    if ((::ioctlsocket(_get_osfhandle(s), c, a)) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return 0;
}