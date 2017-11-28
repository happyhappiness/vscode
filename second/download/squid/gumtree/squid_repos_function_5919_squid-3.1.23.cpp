inline
int send(int s, const void * b, size_t l, int f)
{
    int result;
    if ((result = ::send(_get_osfhandle(s), (char *)b, l, f)) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return result;
}