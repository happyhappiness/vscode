inline
int connect(int s, const struct sockaddr * n, int l)
{
    if (::connect(_get_osfhandle(s),n,l) == SOCKET_ERROR) {
        if (WSAEMFILE == (errno = WSAGetLastError()))
            errno = EMFILE;
        return -1;
    } else
        return 0;
}