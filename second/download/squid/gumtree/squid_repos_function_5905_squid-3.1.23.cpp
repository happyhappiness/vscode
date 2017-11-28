inline
int bind(int s, struct sockaddr * n, int l)
{
    if (::bind(_get_osfhandle(s),n,l) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return 0;
}