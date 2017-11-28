inline int
shutdown(int s, int h)
{
    if (::shutdown(_get_osfhandle(s),h) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return 0;
}