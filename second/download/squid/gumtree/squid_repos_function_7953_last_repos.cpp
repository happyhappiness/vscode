inline int
getsockname(int s, struct sockaddr * n, socklen_t * l)
{
    int i=*l;
    if (::getsockname(_get_osfhandle(s), n, &i) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return 0;
}