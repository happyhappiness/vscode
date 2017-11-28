inline int
getsockopt(int s, int l, int o, void * v, socklen_t * n)
{
    Sleep(1);
    if ((::getsockopt(_get_osfhandle(s), l, o,(char *) v, n)) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return 0;
}