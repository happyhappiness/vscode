inline ssize_t
recv(int s, void * b, size_t l, int f)
{
    ssize_t result;
    if ((result = ::recv(_get_osfhandle(s), (char *)b, l, f)) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return result;
}