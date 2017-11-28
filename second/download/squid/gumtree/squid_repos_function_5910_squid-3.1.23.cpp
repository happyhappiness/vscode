inline
int getsockname(int s, struct sockaddr * n, size_t * l)
{
    if ((::getsockname(_get_osfhandle(s), n, (int *)l)) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return 0;
}