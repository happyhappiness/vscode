inline ssize_t
recvfrom(int s, void * b, size_t l, int f, struct sockaddr * fr, socklen_t * fl)
{
    ssize_t result;
    int ifl=*fl;
    if ((result = ::recvfrom(_get_osfhandle(s), (char *)b, l, f, fr, &ifl)) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return result;
}