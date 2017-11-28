inline int
ioctl(int s, int c, void * a)
{
    if ((::ioctlsocket(_get_osfhandle(s), c, (u_long FAR *)a)) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return 0;
}