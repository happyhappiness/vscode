inline
int select(int n, fd_set * r, fd_set * w, fd_set * e, struct timeval * t)
{
    int result;
    if ((result = ::select(n,r,w,e,t)) == SOCKET_ERROR) {
        errno = WSAGetLastError();
        return -1;
    } else
        return result;
}