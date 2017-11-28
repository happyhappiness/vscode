inline ssize_t
sendto(int s, const void * b, size_t l, int f, const struct sockaddr * t, socklen_t tl)
{
    ssize_t result;
    if ((result = ::sendto(_get_osfhandle(s), (char *)b, l, f, t, tl)) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return result;
}