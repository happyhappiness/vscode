inline
int gethostname(char * n, size_t l)
{
    if ((::gethostname(n, l)) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return 0;
}