inline ssize_t
send(int s, const char * b, size_t l, int f)
{
    ssize_t result;
    if ((result = ::send(_get_osfhandle(s), b, l, f)) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return result;
}