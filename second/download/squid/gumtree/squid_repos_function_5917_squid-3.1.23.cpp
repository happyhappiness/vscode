inline
int recvfrom(int s, void * b, size_t l, int f, struct sockaddr * fr, size_t * fl)
{
    int result;
    if ((result = ::recvfrom(_get_osfhandle(s), (char *)b, l, f, fr, (int *)fl)) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return result;
}