inline int
accept(int s, struct sockaddr * a, socklen_t * l)
{
    SOCKET result;
    if ((result = ::accept(_get_osfhandle(s), a, l)) == INVALID_SOCKET) {
        if (WSAEMFILE == (errno = WSAGetLastError()))
            errno = EMFILE;
        return -1;
    } else
        return _open_osfhandle(result, 0);
}