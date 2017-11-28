inline int
listen(int s, int b)
{
    if (::listen(_get_osfhandle(s), b) == SOCKET_ERROR) {
        if (WSAEMFILE == (errno = WSAGetLastError()))
            errno = EMFILE;
        return -1;
    } else
        return 0;
}