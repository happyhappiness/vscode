inline int
bind(int s, const struct sockaddr * n, socklen_t l)
{
    if (::bind(_get_osfhandle(s),n,l) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return 0;
}